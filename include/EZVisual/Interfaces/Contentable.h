#include "EZVisual/Interfaces/VisualElement.h"
#include "EZVisual/Tools.h"

namespace EZVisual{

#ifndef _EZVISUAL_CONTENTABLE_
#define _EZVISUAL_CONTENTABLE_
    class Contentable : virtual public VisualElement{
    public:
        Contentable(rapidjson::Value& json) : VisualElement(json){
            if(content) delete content;
            rapidjson::Value& con = json["Content"];
            if(!con.IsNull()) content = VisualElement::CreateInstance(con);
        }

        ~Contentable(){
            if(content){
                delete content;
                content = NULL;
            }
        }

        VisualElement* SearchElementById(int id){
            if(id == this->id) return this;
            if(content) return content->SearchElementById(id);
            return NULL;
        }

        /**@brief Set content for a visual element.
         *
         * Set content for a visual element. An element may only have one content, so the old content will be freed immediately if a new one is set.
         */
        void SetContent(VisualElement* content){
            if(this->content == content) return;
            if(this->content) delete content;
            this->content = content;
        }

        /**@brief Get content of a visual element.
         *
         * Get content of a visual element. Return NULL if this element doesn't have a content. Ensure the desired type is exactly correct when calling this, or you may get a std::bad_cast exception.
         *
         * @param T Desired type of the content.
         * @ret Pointer to the content.
         */
        template<typename T> T* GetContent() const{
            if(content) return dynamic_cast<T*>(content);
            else return NULL;
        }

    protected:
        VisualElement* content = NULL;
    };

#endif

}