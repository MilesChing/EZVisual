#include "EZVisual/Controls/Canvas.h"

namespace EZVisual{

    const int dx[] = {-1, 0, 1};
    const int dy[] = {-1, 0, 1};
    const int dxnum = sizeof(dx) / sizeof(dx[0]);
    const int dynum = sizeof(dy) / sizeof(dy[0]);

    Canvas::Canvas(rapidjson::Value& json) :
            Marginable(json),
            Backgroundable(json),
            VisualElement(json){
        if(json["LayerCount"].IsInt())
            SetLayerCount(json["LayerCount"].GetInt());
        else SetLayerCount(1);
        if(json["LayerWidth"].IsInt() && json["LayerHeight"].IsInt()){
            SetLayerSize(make_pair(json["LayerWidth"].GetInt(), json["LayerHeight"].GetInt()));
        }
        else throw "LayerSize must be set for Canvas.";
    }

    void Canvas::Draw(cv::Mat& target){
        for(int i = 0; i < layer_count; ++i)
            for(int x = 0; x < layer_width; ++x)
                for(int y = 0; y < layer_height; ++y)
                    pixels[i][GetIndex(x, y)]
                        .Cover(target.at<cv::Vec3b>
                        (y + margin[1], x + margin[0]));
    }

    void Canvas::Measure(){
        width = layer_width + margin[0] + margin[2];
        height = layer_height + margin[1] + margin[3];
    }

    VisualElementType Canvas::getType() const{
        return TYPE_CANVAS;
    }

    void Canvas::PaintColor(const Color& color, int layer_index){
        for(int i = 0; i < pixels[layer_index].size(); ++i)
            color.Cover(pixels[layer_index][i]);
    }

    void Canvas::PaintImage(const cv::Mat& mat, int layer_index, const std::pair<int, int>& origin_point){
        if(origin_point.first + mat.cols < 0 || origin_point.first + mat.cols > layer_width
            || origin_point.second + mat.rows < 0 || origin_point.second + mat.rows > layer_height)
            throw "Image exceeds the layer.";
        if(mat.channels() == 1){
            for(int x = 0; x < mat.cols; ++x)
                for(int y = 0; y < mat.rows; ++y){
                    u_char v3 = mat.at<u_char>(y, x);
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].a = 255;
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].r = v3;
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].g = v3;
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].b = v3;
                }
        }
        else if(mat.channels() == 3){
            for(int x = 0; x < mat.cols; ++x)
                for(int y = 0; y < mat.rows; ++y){
                    cv::Vec3b v3 = mat.at<cv::Vec3b>(y, x);
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].a = 255;
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].b = v3[0];
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].g = v3[1];
                    pixels[layer_index][GetIndex(origin_point.first + x,
                        origin_point.second + y)].r = v3[2];
                }
        }
        else throw "Illegal channel count: must be 1 or 3.";
    }

    void Canvas::ClearLayer(int layer_index){
        pixels[layer_index] = vector<Color>(layer_height * layer_width, 0);
    }

    void Canvas::SetLayerCount(int count){
        if(count <= 0) throw "Layer count not legal.";
        layer_count = count;
        pixels.resize(count);
    }

    void Canvas::SetLayerSize(const pair<int,int>& size){
        if(size.first <= 0 || size.second <= 0) throw "Layer size not legal.";
        layer_width = size.first;
        layer_height = size.second;
        for(int i = 0; i < pixels.size(); ++i) pixels[i].resize(layer_width * layer_height);
    }

    int Canvas::GetIndex(int x, int y){
        return x * layer_height + y;
    }

    int Canvas::GetLayerCount() const{
        return layer_count;
    }

    int Canvas::GetLayerWidth() const{
        return layer_width;
    }

    int Canvas::GetLayerHeight() const{
        return layer_height;
    }




    void Canvas::PaintCurve(const std::vector<std::pair<int,int>>& points, const Color& color, int layer_index, float point_size){
        if(point_size == 0) for(auto p : points) PaintPixel(p, color, layer_index);
        else for(auto p : points) for(auto p : points)
            PaintCircle(make_pair((float)p.first, (float)p.second), point_size, layer_index, color, 0, 0);
    }

    void Canvas::PaintRect(const pair<int, int>& origin_point, int width, int height, int layer_index, const Color& fill_color, const Color& border_color, float border_thickness){
        const int inner_left = origin_point.first + border_thickness;
        const int inner_right = origin_point.first + width - border_thickness;
        const int inner_top = origin_point.second + border_thickness;
        const int inner_bottom = origin_point.second + height - border_thickness;


        for(int i = origin_point.first - border_thickness;
            i <= origin_point.first + width + border_thickness; ++i){

            for(int j = origin_point.second - border_thickness;
                j <= origin_point.second + height + border_thickness; ++j){

                if((i >= inner_left && i <= inner_right
                    && j >= inner_top && j <= inner_bottom) || border_thickness == 0)
                    PaintPixel(make_pair(i, j), fill_color, layer_index);
                else PaintPixel(make_pair(i, j), border_color, layer_index);
            }
        }

    }

    void Canvas::PaintCircle(const pair<float, float>& center_point, float r, int layer_index, const Color& fill_color, const Color& border_color, float border_thickness){
        std::unique_lock<std::mutex> lck(inner_q_mtx);
        while(!inner_q.empty()) inner_q.pop();
        inner_set.clear();
        inner_q.push(make_pair((int)center_point.first, (int)center_point.second));
        inner_set.insert(make_pair((int)center_point.first, (int)center_point.second));
        while(!inner_q.empty()){
            const int cx = inner_q.front().first, cy = inner_q.front().second;
            inner_q.pop();
            for(int x = 0; x < dxnum; ++x)
                for(int y = 0; y < dynum; ++y){
                    const int tx = cx + dx[x], ty = cy + dy[y];
                    const double dis = sqrt(((double)center_point.first - tx)*
                        ((double)center_point.first - tx) +
                        ((double)center_point.second - ty)*
                        ((double)center_point.second - ty));
                    if(fabs(dis - r) < border_thickness)
                        PaintPixel(make_pair(tx, ty), border_color, layer_index);
                    else if(dis < r)
                        PaintPixel(make_pair(tx, ty), fill_color, layer_index);
                    else continue;
                    if(inner_set.find(make_pair(tx, ty)) == inner_set.end()){
                        inner_q.push(make_pair(tx, ty));
                        inner_set.insert(make_pair(tx, ty));
                    }
                }
        }
    }

    void Canvas::PaintPixel(const pair<int, int>& point, const Color& point_color, int layer_index){
        if(point.first < 0 || point.second < 0 ||
            point.first >= layer_width || point.second >= layer_height
            || !point_color.a)
            return;
        point_color.Cover(pixels[layer_index][GetIndex(point.first, point.second)]);
    }

    void Canvas::PaintLine(const pair<int, int>& a, const pair<int, int>& b, const Color& line_color, int layer_index, float line_thickness){
        if(b.first == a.first){
            int fr = min(a.second, b.second);
            int to = max(a.second, b.second);
            for(int i = fr; i <= to; ++i)
                if(line_thickness == 0) PaintPixel(make_pair(a.first, i), line_color, layer_index);
                else PaintCircle(make_pair(a.first, i), line_thickness, layer_index, line_color, 0, 0);

            return;
        }
        else if(b.second == a.second){
            int fr = min(a.first, b.first);
            int to = max(a.first, b.first);
            for(int i = fr; i <= to; ++i)
                if(line_thickness == 0) PaintPixel(make_pair(a.second, i), line_color, layer_index);
                else PaintCircle(make_pair(a.second, i), line_thickness, layer_index, line_color, 0, 0);

            return;
        }

        double step_x, step_y;
        const double max_step = 0.5;

        if(abs(b.second - a.second) > abs(b.first - a.first)){
            step_x = max_step * (b.first - a.first) / (b.second - a.second);
            step_y = max_step;
        }
        else{
            step_y = max_step * (b.second - a.second) / (b.first - a.first);
            step_x = max_step;
        }

        double tx = a.first, ty = a.second;
        int kx = -1, ky = -1;
        while(fabs(tx - a.first) <= abs(b.first - a.first)){
            if(round(tx) != kx || round(ty) != ky){
                kx = round(tx);
                ky = round(ty);
                if(line_thickness == 0) PaintPixel(make_pair(kx, ky), line_color, layer_index);
                else PaintCircle(make_pair(kx, ky), line_thickness, layer_index, line_color, 0, 0);
            }
            tx += step_x;
            ty += step_y;
        }
    }

}