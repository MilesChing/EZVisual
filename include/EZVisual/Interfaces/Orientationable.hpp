#pragma once
#include "EZVisual/Interfaces/VisualElement.h"
#include "EZVisual/Tools/StringConverter.hpp"

namespace EZVisual{

    class Orientationable : virtual public VisualElement{
    public:
        Orientationable(rapidjson::Value& json) : VisualElement(json){
            rapidjson::Value& o = json["Orientation"];
            if(!o.IsNull()) orientation = StringConverter::ToOrientation(
                o.GetString()
            );
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
        Orientation orientation = Orientation::Vertical;
    };

}