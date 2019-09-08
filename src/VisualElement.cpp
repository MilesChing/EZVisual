#include "EZVisual/Interfaces/Interfaces.h"
#include <string>

using namespace std;

namespace EZVisual{

    int VisualElement::GetWidth(){
        return width;
    }

    int VisualElement::GetHeight(){
        return height;
    }

    int VisualElement::GetId(){
        return id;
    }

    void VisualElement::SetByJSON(rapidjson::Value& json){
        if(json["Id"].IsInt()) id = json["Id"].GetInt();
        if(!json["HorizontalAlignment"].IsNull())
            Convert(json["HorizontalAlignment"].GetString(), horizontal_alignment);
        if(!json["VerticalAlignment"].IsNull())
            Convert(json["VerticalAlignment"].GetString(), vertical_alignment);
        need_redraw |= true;
    }

    HorizontalAlignment VisualElement::GetHorizontalAlignment(){
        return horizontal_alignment;
    }

    VerticalAlignment VisualElement::GetVerticalAlignment(){
        return vertical_alignment;
    }

}