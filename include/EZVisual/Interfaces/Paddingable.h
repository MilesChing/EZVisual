#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_PADDINGABLE_
#define _EZVISUAL_PADDINGABLE_
    class Paddingable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            if(json["Padding"].IsArray()){
                auto mg = json["Padding"].GetArray();
                padding[0] = mg[0].GetInt();
                padding[1] = mg[1].GetInt();
                padding[2] = mg[2].GetInt();
                padding[3] = mg[3].GetInt();
            }
            else if(json["Padding"].IsInt()){
                padding[0] = padding[1] = padding[2] = padding[3]
                    = json["Padding"].GetInt();
            }
        }

        void SetPadding(int left, int top, int right, int bottom){
            padding[0] = left;
            padding[1] = top;
            padding[2] = right;
            padding[3] = bottom;
        }
    protected:
        int padding[4] = {0};
    };

#endif

}

