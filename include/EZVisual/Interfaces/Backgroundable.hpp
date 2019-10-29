#pragma once
#include "EZVisual/Interfaces/VisualElement.h"
#include "EZVisual/Brushes.h"

namespace EZVisual{

    class Backgroundable : virtual public VisualElement{
    public:
        Backgroundable(rapidjson::Value& json) : VisualElement(json){
            rapidjson::Value& back_json = json["Background"];
            if(back_json.IsNull()) background = SolidColorBrush::CreateInstance();
            else background = Brush::CreateInstance(back_json);
        }

        ~Backgroundable(){
            delete background;
        }

        /**@brief Set background color for a visual element.
         *
         * Set background color for a visual element.
         *
         * @param color Color to be set for.
         */
        void SetBackground(Brush* brush){
            delete background;
            background = brush;
        }

        /**@brief Get the background color of a visual element.
         *
         * Get the background color of a visual element.
         *
         * @ret The background color of this element.
         */
        Brush* GetBackground() const{
            return background;
        }

    protected:
        Brush* background = NULL;
    };

}

