#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_PADDINGABLE_
#define _EZVISUAL_PADDINGABLE_
    class Paddingable : virtual public VisualElement{
    public:

        Paddingable(rapidjson::Value& json) : VisualElement(json){
            if(json["Padding"].IsArray()){
                auto mg = json["Padding"].GetArray();
                padding[0] = mg[0].GetInt();
                padding[1] = mg[1].GetInt();
                padding[2] = mg[2].GetInt();
                padding[3] = mg[3].GetInt();
            }
            else if(json["Padding"].IsInt()){
                padding[0] = padding[1] = padding[2] = padding[3]
                    = json["Padding"].GetInt();
            }
        }

        /**@brief Set the margin for a visual element.
         *
         * Set the margin for a visual element. Padding create space inside a container, it defines the space between the container and its content or child.
         *
         * Padding will be firstly considered when we are measuring the size of a content or child of a container. Which means that padding will always occupy the space provided by a container at its full size until there is no room for the content to display.
         *
         * @param left Size of the Left padding.
         * @param right Size of the right padding.
         * @param top Size of the top padding.
         * @param bottom Size of the bottom padding.
         */
        void SetPadding(int left, int top, int right, int bottom){
            padding[0] = left;
            padding[1] = top;
            padding[2] = right;
            padding[3] = bottom;
        }

        /**@brief Get the margin of a visual element.
         *
         * Get the margin of a visual element. Padding create space inside a container, it defines the space between the container and its content or child.
         *
         * Padding will be firstly considered when we are measuring the size of a content or child of a container. Which means that padding will always occupy the space provided by a container at its full size until there is no room for the content to display.
         *
         * @param left Size of the Left padding.
         * @param right Size of the right padding.
         * @param top Size of the top padding.
         * @param bottom Size of the bottom padding.
         */
        void GetPadding(int& left, int& top, int& right, int& bottom) const{
            left = padding[0];
            top = padding[1];
            right = padding[2];
            bottom = padding[3];
        }

    protected:
        void GetFreeSpace(int desired_width, int desired_height){
            border_width = max(desired_width - padding[0] - padding[2], 0);
            border_height = max(desired_height - padding[1] - padding[3], 0);
        }

        int padding[4] = {0};
        int border_width, border_height;
    };

#endif

}

