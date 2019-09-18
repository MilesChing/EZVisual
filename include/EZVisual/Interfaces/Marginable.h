#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_MARGINABLE_
#define _EZVISUAL_MARGINABLE_
    class Marginable : virtual public VisualElement{
    public:
        Marginable(rapidjson::Value& json) : VisualElement(json){
            if(json["Margin"].IsArray()){
                auto mg = json["Margin"].GetArray();
                margin[0] = mg[0].GetInt();
                margin[1] = mg[1].GetInt();
                margin[2] = mg[2].GetInt();
                margin[3] = mg[3].GetInt();
            }
            else if(json["Margin"].IsInt()){
                margin[0] = margin[1] = margin[2] = margin[3]
                    = json["Margin"].GetInt();
            }
        }

        /**@brief Set the margin for a visual element.
         *
         * Set margin for a visual element. Margin create space around an element, outside of any defined borders.
         *
         * Margin will be firstly considered when we are measuring the size of an element. Which means that margin will always occupy the space provided to the element at its full size until there is no room for the element to display.
         *
         * @param left Size of the Left margin.
         * @param right Size of the right margin.
         * @param top Size of the top margin.
         * @param bottom Size of the bottom margin.
         */
        void SetMargin(int left, int top, int right, int bottom){
            margin[0] = left;
            margin[1] = top;
            margin[2] = right;
            margin[3] = bottom;
        }

        /**@brief Get the margin of a visual element.
         *
         * Get the margin of a visual element. Margin create space around an element, outside of any defined borders.
         *
         * Margin will be firstly considered when we are measuring the size of an element. Which means that margin will always occupy the space provided to the element at its full size until there is no room for the element to display.
         *
         * @param left Size of the Left margin.
         * @param right Size of the right margin.
         * @param top Size of the top margin.
         * @param bottom Size of the bottom margin.
         */
        void GetMargin(int& left, int& top, int& right, int& bottom) const{
            left = margin[0];
            top = margin[1];
            right = margin[2];
            bottom = margin[3];
        }

        void GetFreeSpace(int desired_width, int desired_height){
            content_width = max(desired_width - margin[0] - margin[2], 0);
            content_height = max(desired_height - margin[1] - margin[3], 0);
        }

    protected:
        int margin[4] = {0};
        int content_width, content_height;
    };

#endif

}

