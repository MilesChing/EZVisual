#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_MIN_HEIGHTABLE_
#define _EZVISUAL_MIN_HEIGHTABLE_
    class MinHeightable : virtual public VisualElement{
    public:
        MinHeightable(rapidjson::Value& json) : VisualElement(json){
            if(json["MinHeight"].IsInt())
                min_height = json["MinHeight"].GetInt();
        }

        void SetMinHeight(int min_height){
            if(this->min_height != min_height)
                this->min_height = min_height;
        }

    protected:
        int min_height = 0;
    };

#endif

}

