#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_CONTENTABLE_
#define _EZVISUAL_CONTENTABLE_
    class Contentable : virtual public VisualElement{
    public:
        Contentable(rapidjson::Value& json) : VisualElement(json){
            if(content) delete content;
            rapidjson::Value& con = json["Content"];
            if(!con.IsNull()){
                VisualElementType type;
                Convert(con["Type"].GetString(), type);
                content = GetVisualElementFromType(type, con);
            }
        }

        VisualElement* SearchElementById(int id){
            if(id == this->id) return this;
            if(content) return content->SearchElementById(id);
            return NULL;
        }

        void SetContent(VisualElement* content){
            if(this->content == content) return;
            if(this->content) delete content;
            this->content = content;
        }

    protected:
        VisualElement* content = NULL;

        void DeleteContent(){
            if(content) delete content;
        }
    };

#endif

}