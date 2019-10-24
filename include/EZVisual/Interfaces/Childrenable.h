#include "EZVisual/Interfaces/VisualElement.h"
#include "EZVisual/Tools.h"
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
                for(int i = 0; i < array.Size(); ++i)
                    children.push_back(
                        VisualElement::CreateInstance(array[i])
                    );
            }
        }

        /**Get the count of children.
         *
         * @ret Count of children.
         */
        int GetChildrenCount() const{
            return children.size();
        }

        /**@brief Get a child of this element by index.
         *
         * Get a child of this element by index. Ensure the desired type is exactly correct when calling this, or you may get a std::bad_cast exception.
         *
         * @param index Index of the child. Must fall in [0, ChildrenCount).
         * @param T Desired type of the child.
         * @ret Pointer to the child whose index is i.
         */
        template<typename T> T* GetChild(int index) const{
            return dynamic_cast<T*>(children[index]);
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