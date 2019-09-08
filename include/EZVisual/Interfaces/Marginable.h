#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_MARGINABLE_
#define _EZVISUAL_MARGINABLE_
    class Marginable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            if(json["Margin"].IsArray()){
                auto mg = json["Margin"].GetArray();
                margin[0] = mg[0].GetInt();
                margin[1] = mg[1].GetInt();
                margin[2] = mg[2].GetInt();
                margin[3] = mg[3].GetInt();
            }
            else if(json["Margin"].IsInt()){
                margin[0] = margin[1] = margin[2] = margin[3]
                    = json["Margin"].GetInt();
            }
        }

        void SetMargin(int left, int top, int right, int bottom){
            margin[0] = left;
            margin[1] = top;
            margin[2] = right;
            margin[3] = bottom;
            need_redraw = true;
        }
    protected:
        int margin[4] = {0};
    };

#endif

}
