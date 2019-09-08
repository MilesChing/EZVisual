#include "EZVisual/Interfaces/VisualElement.h"
#include <vector>

namespace EZVisual{

#ifndef _EZVISUAL_CHILDRENABLE_
#define _EZVISUAL_CHILDRENABLE_
    class Childrenable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            for(auto child : children) delete child;
            children.clear();
            rapidjson::Value& ch = json["Children"];
            if(!ch.IsNull()){
                auto array = ch.GetArray();
                for(int i = 0; i < array.Size(); ++i){
                    Value& child = array[i];
                    VisualElementType type;
                    Convert(child["Type"].GetString(), type);
                    children.push_back(GetVisualElementFromType(type));
                    children.back()->SetByJSON(child);
                }
            }
        }



    protected:
        vector<VisualElement*> children;
    };

#endif

}