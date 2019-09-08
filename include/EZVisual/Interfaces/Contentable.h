#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_CONTENTABLE_
#define _EZVISUAL_CONTENTABLE_
    class Contentable : virtual public VisualElement{
    public:
        void SetByJSON(rapidjson::Value& json){
            this->VisualElement::SetByJSON(json);
            if(content) delete content;
            rapidjson::Value& con = json["Content"];
            if(!con.IsNull()){
                VisualElementType type;
                Convert(con["Type"].GetString(), type);
                content = GetVisualElementFromType(type);
                content->SetByJSON(con);
            }
        }

        void SetContent(VisualElement* content){
            if(this->content == content) return;
            if(this->content) delete content;
            this->content = content;
            need_redraw = true;
        }
    protected:
        VisualElement* content = NULL;
    };

#endif

}