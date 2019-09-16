#include "EZVisual/Interfaces/VisualElement.h"
#include <vector>

namespace EZVisual{

#ifndef _EZVISUAL_CHILDRENABLE_
#define _EZVISUAL_CHILDRENABLE_
    class Childrenable : virtual public VisualElement{
    public:

        Childrenable(rapidjson::Value& json) : VisualElement(json){
            for(auto child : children) delete child;
            children.clear();
            rapidjson::Value& ch = json["Children"];
            if(!ch.IsNull()){
                auto array = ch.GetArray();
                for(int i = 0; i < array.Size(); ++i){
                    Value& child = array[i];
                    VisualElementType type;
                    Convert(child["Type"].GetString(), type);
                    children.push_back(GetVisualElementFromType(type, child));
                }
            }
        }

        VisualElement* SearchElementById(int id){
            if(id == this->id) return this;

            for(auto child : children){
                auto res = child->SearchElementById(id);
                if(res) return res;
            }

            return NULL;
        }

    protected:
        vector<VisualElement*> children;

        void DeleteChildren(){
            for(auto child : children) delete child;
        }
    };

#endif

}