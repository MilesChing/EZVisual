#include "EZVisual/Canvas.h"

namespace EZVisual{

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

    void Canvas::Paint(const Color& color, int layer_index){
        for(int i = 0; i < pixels[layer_index].size(); ++i)
            color.Cover(pixels[layer_index][i]);
    }

    void Canvas::Paint(const cv::Mat& mat, int layer_index, const std::pair<int, int>& origin_point){
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

    void Canvas::Paint(const std::vector<std::pair<int,int>>& points, const Color& color, int layer_index){
        for(auto p : points){
            if(p.first < 0 || p.first >= layer_width
                || p.second < 0 || p.second >= layer_height) throw "Point position not legal.";
            color.Cover(pixels[layer_index][GetIndex(p.first, p.second)]);
        }
    }

    void Canvas::Paint(const std::vector<std::tuple<int,int,Color>>& points, int layer_index){
        for(auto p : points){
            if(get<0>(p) < 0 || get<0>(p) >= layer_width
                || get<1>(p) < 0 || get<1>(p) >= layer_height) throw "Point position not legal.";
            get<2>(p).Cover(pixels[layer_index][GetIndex(get<0>(p), get<1>(p))]);
        }
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

}