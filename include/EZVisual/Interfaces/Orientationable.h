#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_ORIENTATIONABLE_
#define _EZVISUAL_ORIENTATIONABLE_
    class Orientationable : virtual public VisualElement{
    public:
        Orientationable(rapidjson::Value& json) : VisualElement(json){
            rapidjson::Value& o = json["Orientation"];
            if(!o.IsNull()){
                Convert(o.GetString(), orientation);
            }
        }

        /**@brief Set the orientation for a container.
         *
         * Set the orientation for a container. Orientation usually decides the way that containers arrange children.
         *
         * @param orientation New orientation to be set for.
         */
        void SetOrientation(const Orientation& orientation){
            if(this->orientation != orientation)
                this->orientation = orientation;
        }

        /**@brief Get the orientation of a container.
         *
         * Get the orientation of a container. Orientation usually decides the way that containers arrange children.
         *
         * @ret orientation Orientation of this visual element.
         */
        Orientation GetOrientation() const{
            return orientation;
        }
    protected:
        Orientation orientation = Vertical;
    };

#endif

}