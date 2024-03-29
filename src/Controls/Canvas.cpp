#include "EZVisual/Controls/Canvas.h"
#include <cmath>

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
        if(measured_height == 0 || measured_width == 0) return;
        if(target.rows < measured_height || target.cols < measured_width)
            throw "Canvas::Draw() need more space.";

        if(control_border_width > 0 && control_border_height > 0){
            cv::Mat content_roi(target, cv::Rect(margin[0], margin[1],
                control_border_width, control_border_height));
            UpdateGlobalXY(content_roi);
            background->Draw(content_roi);
            for(int i = 0; i < layer_count; ++i)
                for(int x = 0; x < min(layer_width, control_border_width); ++x)
                    for(int y = 0; y < min(layer_height, control_border_height); ++y)
                        pixels[i][GetIndex(x, y)].Cover(content_roi.at<cv::Vec3b>(y, x));
        }
    }

    void Canvas::Measure(int desired_width, int desired_height){
        this->Marginable::GetFreeSpace(desired_width, desired_height);

        if(control_border_width == 0 || control_border_height == 0){
            measured_width = desired_width;
            measured_height = desired_height;
            return;
        }

        if(width == FILL_PARENT) measured_width = desired_width;
        else{
            control_border_width = min(layer_width, control_border_width);
            measured_width = control_border_width + margin[0] + margin[2];
        }

        if(height == FILL_PARENT) measured_height = desired_height;
        else{
            control_border_height = min(layer_height, control_border_height);
            measured_height = control_border_height + margin[1] + margin[3];
        }
    }

    VisualElementType Canvas::getType() const{
        return VisualElementType::Canvas;
    }

    void Canvas::PaintColor(const Color& color, int layer_index){
        for(int i = 0; i < pixels[layer_index].size(); ++i)
            color.Cover(pixels[layer_index][i]);
    }

    void Canvas::PaintImage(const cv::Mat& mat, int layer_index, const std::pair<int, int>& origin_point){
        if(origin_point.first + mat.cols < 0 || origin_point.first + mat.cols > layer_width
            || origin_point.second + mat.rows < 0 || origin_point.second + mat.rows > layer_height){
            throw "Image exceeds the layer.";
        }
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
        else{
            throw "Illegal channel count: must be 1 or 3.";
        }
    }

    void Canvas::ClearLayer(int layer_index){
        pixels[layer_index] = vector<Color>(layer_height * layer_width, 0);
    }

    void Canvas::SetLayerCount(int count){
        if(count <= 0){
            throw "Layer count not legal.";
        }
        layer_count = count;
        pixels.resize(count);
    }

    void Canvas::SetLayerSize(const pair<int,int>& size){
        if(size.first <= 0 || size.second <= 0){
            throw "Layer size not legal.";
        }
        layer_width = size.first;
        layer_height = size.second;
        for(int i = 0; i < pixels.size(); ++i) pixels[i].resize(layer_width * layer_height, 0);
    }

    int Canvas::GetIndex(int x, int y) const{
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
            PaintCircle(make_pair((float)p.first, (float)p.second), point_size, color, 0, layer_index, 0);
    }

    void Canvas::PaintRect(const pair<int, int>& origin_point, int width, int height, const Color& fill_color, const Color& border_color, int layer_index, float border_thickness){
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

    void Canvas::PaintCircle(const pair<float, float>& center_point, float r, const Color& fill_color, const Color& border_color, int layer_index, float border_thickness){
        if(r < 0){
            throw "Radius not legal.";
        }
        if(r == 0){
            PaintPixel(make_pair((int)round(center_point.first), (int)round(center_point.second)), fill_color, layer_index);
            return;
        }
        const double fake_r = r + border_thickness;
        const int txb = (center_point.first - fake_r);
        const int txe = (center_point.first + fake_r);
        for(int tx = txb; tx <= txe; ++tx){
            double dy = sqrt(fake_r * fake_r - (tx - center_point.first) * (tx - center_point.first));
            const int tyb = round(center_point.second - dy);
            const int tye = round(center_point.second + dy);
            for(int ty = tyb; ty <= tye; ++ty){
                const double dis = sqrt(((double)center_point.first - tx)*
                                        ((double)center_point.first - tx) +
                                        ((double)center_point.second - ty)*
                                        ((double)center_point.second - ty));
                if(fabs(dis - r) < border_thickness) PaintPixel(make_pair(tx, ty), border_color, layer_index);
                else if(dis < r) PaintPixel(make_pair(tx, ty), fill_color, layer_index);
            }
        }
    }

    void Canvas::PaintPixel(const pair<int, int>& point, const Color& point_color, int layer_index){
        if(point.first < 0 || point.second < 0 ||
            point.first >= layer_width || point.second >= layer_height
            || !point_color.a){
            return;
        }
        point_color.Cover(pixels[layer_index][GetIndex(point.first, point.second)]);
    }

    void Canvas::PaintLine(const pair<int, int>& a, const pair<int, int>& b, const Color& line_color, int layer_index, float line_thickness){
        const int dx = a.first - b.first;
        const int dy = a.second - b.second;
        if(!dy && !dx){
            PaintCircle(a, line_thickness, line_color, 0, layer_index, 0);
            return;
        }
        if(abs(dy) > abs(dx)){
            const double k = ((double)dx) / dy;
            const double t = b.first - k * b.second;
            const int d = dy > 0 ? -1 : 1;
            for(int y = a.second; y != b.second; y += d)
                PaintCircle(make_pair((int)round(k*y+t), y),
                    line_thickness, line_color, 0, layer_index, 0);
        }
        else{
            const double k = ((double)dy) / dx;
            const double t = b.second - k * b.first;
            const int d = dx > 0 ? -1 : 1;
            for(int x = a.first; x != b.first; x += d)
                PaintCircle(make_pair(x, (int)round(k*x+t)),
                    line_thickness, line_color, 0, layer_index, 0);
        }
    }

}