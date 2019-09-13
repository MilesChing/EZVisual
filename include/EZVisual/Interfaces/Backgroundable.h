#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_BACKGROUNDABLE_
#define _EZVISUAL_BACKGROUNDABLE_
    class Backgroundable : virtual public VisualElement{
    public:
        Backgroundable(rapidjson::Value& json) : VisualElement(json){
            if(json["Background"].IsString()){
                background = Color(json["Background"].GetString());
            }
        }

        void SetBackground(const Color& color){
            if(background != color)
                background = color;
        }

        Color GetBackground() const{
            return background;
        }

    protected:
        Color background = Color(0);
    };

#endif

}

