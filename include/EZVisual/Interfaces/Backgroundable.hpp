#pragma once
#include "EZVisual/Interfaces/VisualElement.h"
#include "EZVisual/Brushes.h"

namespace EZVisual{

    class Backgroundable : virtual public VisualElement{
    public:
        Backgroundable(rapidjson::Value& json) : VisualElement(json){
            if(json["Background"].IsString()){
                background = Color(json["Background"].GetString());
            }
        }

        /**@brief Set background color for a visual element.
         *
         * Set background color for a visual element.
         *
         * @param color Color to be set for.
         */
        void SetBackground(const Color& color){
            if(background != color)
                background = color;
        }

        /**@brief Get the background color of a visual element.
         *
         * Get the background color of a visual element.
         *
         * @ret The background color of this element.
         */
        Color GetBackground() const{
            return background;
        }

    protected:
        Color background = Color(0);
    };

}

