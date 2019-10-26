#include "EZVisual/Brushes/SolidColorBrush.h"

namespace EZVisual{

    SolidColorBrush* SolidColorBrush::CreateInstance(Color color){
        return new SolidColorBrush(color);
    }

    SolidColorBrush::SolidColorBrush(Color _color) : color(_color){}

    void SolidColorBrush::Draw(cv::Mat& mat){
        color.Cover(mat);
    }

    BrushType SolidColorBrush::GetType() const{
        return BrushType::SolidColorBrush;
    }

    Color SolidColorBrush::GetColor() const{
        return color;
    }

    SolidColorBrush::SolidColorBrush(rapidjson::Value& json){
        if(json.IsString()) color = Color(json.GetString());
        else{
            rapidjson::Value& color_json = json["Color"];
            if(!color_json.IsString()) throw "'Color' not found.";
            color = Color(color_json.GetString());
        }
    }

}