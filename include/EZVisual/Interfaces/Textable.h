#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_TEXTABLE_
#define _EZVISUAL_TEXTABLE_
    class Textable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            if(json["FontColor"].IsString())
                font_color = Color(json["FontColor"].GetString());
            if(json["FontWeight"].IsInt())
                font_weight = json["FontWeight"].GetInt();
            if(json["Text"].IsString())
                text = json["Text"].GetString();
            if(json["FontSize"].IsNumber())
                font_size = json["FontSize"].GetDouble();
            if(json["FontFamily"].IsInt())
                font_family = json["FontFamily"].GetInt();
        }

        void SetText(const char* text){
            this->text = string(text);
            need_redraw = true;
        }

        void SetFontSize(double font_size){
            if(font_size == this->font_size) return;
            this->font_size = font_size;
            need_redraw = true;
        }

        void SetFontColor(const Color& color){
            if(color == this->font_color) return;
            this->font_color = color;
            need_redraw = true;
        }

        void SetFontWeight(int font_weight){
            if(font_weight == this->font_weight) return;
            this->font_weight = font_weight;
            need_redraw = true;
        }

        void SetFontFamily(int font_family){
            if(font_family == this->font_family) return;
            this->font_family = font_family;
            need_redraw = true;
        }

    protected:
        Color font_color = Color(0);
        int font_weight = 1;
        string text = "";
        double font_size = 1;
        int font_family = 0;
    };

#endif

}
