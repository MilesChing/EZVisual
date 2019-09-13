#include "EZVisual/Interfaces.h"
#include <string>

using namespace std;

namespace EZVisual{

    int VisualElement::GetMeasuredWidth() const{
        return measured_width;
    }

    int VisualElement::GetMeasuredHeight() const{
        return measured_height;
    }

    int VisualElement::GetId() const{
        return id;
    }

    HorizontalAlignment VisualElement::GetHorizontalAlignment() const{
        return horizontal_alignment;
    }

    VerticalAlignment VisualElement::GetVerticalAlignment() const{
        return vertical_alignment;
    }

    VisualElement::VisualElement(rapidjson::Value& json){
        //get id
        if(json["Id"].IsInt()) id = json["Id"].GetInt();
        //get Height
        if(json["Height"].IsInt()) height = json["Height"].GetInt();
        else if(json["Height"].IsString()){
            string tmp = json["Height"].GetString();
            if(tmp == "WrapContent") height = WRAP_CONTENT;
            else if(tmp == "FillParent") height = FILL_PARENT;
            else throw "Illegal Height value.";
        }
        //get Width
        if(json["Width"].IsInt()) width = json["Width"].GetInt();
        else if(json["Width"].IsString()){
            string tmp = json["Width"].GetString();
            if(tmp == "WrapContent") width = WRAP_CONTENT;
            else if(tmp == "FillParent") width = FILL_PARENT;
            else throw "Illegal Width value.";
        }
        //get Alignment
        if(!json["HorizontalAlignment"].IsNull())
            Convert(json["HorizontalAlignment"].GetString(), horizontal_alignment);
        if(!json["VerticalAlignment"].IsNull())
            Convert(json["VerticalAlignment"].GetString(), vertical_alignment);
    }

    VisualElement* VisualElement::SearchElementById(int id){
        if(this->id == id) return this;
        else return NULL;
    }

}