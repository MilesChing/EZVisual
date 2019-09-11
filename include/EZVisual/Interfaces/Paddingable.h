#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_PADDINGABLE_
#define _EZVISUAL_PADDINGABLE_
    class Paddingable : virtual public VisualElement{
    public:
        Paddingable(rapidjson::Value& json) : VisualElement(json){
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

        void GetPadding(int& left, int& top, int& right, int& bottom) const{
            left = padding[0];
            top = padding[1];
            right = padding[2];
            bottom = padding[3];
        }
    protected:
        int padding[4] = {0};
    };

#endif

}

