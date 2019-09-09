#include "EZVisual/Canvas.h"


namespace EZVisual{

    void Canvas::Draw(cv::Mat& target){

    }

    void Canvas::Measure(){

    }

    VisualElementType Canvas::getType() const{
        return TYPE_CANVAS;
    }

    void Canvas::SetByJSON(rapidjson::Value& json_value){
        this->Backgroundable::SetByJSON(json_value);
        this->Marginable::SetByJSON(json_value);

        if(json_value["LayerWidth"].IsInt())
            layer_width = json_value["LayerWidth"].GetInt();
        else throw "LayerWidth must be set for Canvas."

        if(json_value["LayerHeight"].IsInt())
            layer_height = json_value["LayerHeight"].GetInt();
        else throw "LayerHeight must be set for Canvas."

        if(layer_height <= 0) throw "LayerHeight must be positive."
        if(layer_width <= 0) throw "LayerWidth must be positive."

        if(json_value["LayerCount"].IsInt())
            layer_count = json_value["LayerCount"].GetInt();

        pixels.clear();
        pixels.resize(layer_count);
        for(auto layer : pixels) layer.resize(layer_height * layer_width, 0x00ffffff);
        need_redraw = true;
    }

    bool Canvas::NeedRedraw() const{
        return need_redraw;
    }

    void Canvas::RegistId(map<int, VisualElement*>& controls){
        controls.insert(make_pair(id, this));
    }

    int Canvas::GetPos(int r, int c){
        if(r < 0 || r >= layer_height || c < 0 || c >= layer_width)
            throw "Canvas index out of range."
        else return r * layer_width + c;
    }

}