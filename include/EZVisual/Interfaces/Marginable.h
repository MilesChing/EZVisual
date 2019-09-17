#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_MARGINABLE_
#define _EZVISUAL_MARGINABLE_
    class Marginable : virtual public VisualElement{
    public:
        Marginable(rapidjson::Value& json) : VisualElement(json){
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
        }

        void GetMargin(int& left, int& top, int& right, int& bottom) const{
            left = margin[0];
            top = margin[1];
            right = margin[2];
            bottom = margin[3];
        }

        void GetFreeSpace(int desired_width, int desired_height){
            content_width = max(desired_width - margin[0] - margin[2], 0);
            content_height = max(desired_height - margin[1] - margin[3], 0);
        }

    protected:
        int margin[4] = {0};
        int content_width, content_height;
    };

#endif

}

