#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_BACKGROUNDABLE_
#define _EZVISUAL_BACKGROUNDABLE_
    class Backgroundable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            if(json["Background"].IsString()){
                background = Color(json["Background"].GetString());
            }
        }

        void SetBackground(const Color& color){
            if(background != color){
                background = color;
                need_redraw = true;
            }
        }
    protected:
        Color background;
    };

#endif

}

