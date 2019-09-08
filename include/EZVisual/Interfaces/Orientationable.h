#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_ORIENTATIONABLE_
#define _EZVISUAL_ORIENTATIONABLE_
    class Orientationable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            rapidjson::Value& o = json["Orientation"];
            if(!o.IsNull()){
                Convert(o.GetString(), orientation);
            }
        }

        void SetOrientation(const Orientation& orientation){
            if(this->orientation != orientation){
                this->orientation = orientation;
                need_redraw = true;
            }
        }
    protected:
        Orientation orientation = Vertical;
    };

#endif

}