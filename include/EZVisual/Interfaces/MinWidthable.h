#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_MIN_WIDTHABLE_
#define _EZVISUAL_MIN_WIDTHABLE_
    class MinWidthable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            if(json["MinWidth"].IsInt())
                min_width = json["MinWidth"].GetInt();
        }

        void SetMinWidth(int min_width){
            if(min_width != this->min_width){
                this->min_width = min_width;
                need_redraw = true;
            }
        }
    protected:
        int min_width = 0;
    };

#endif

}
