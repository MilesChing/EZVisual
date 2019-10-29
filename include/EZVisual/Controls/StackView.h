#pragma once
#include "EZVisual/Interfaces.h"
#include "EZVisual/Core.h"

using namespace cv;

namespace EZVisual{
    /**@StackView is a container which always place its children in order like a stack.
     *
     * The behavior of each StackView element due to its orientation:
     *
     * Horizontal: Children of the element will be placed from left to right. Attribute "HorizontalAlignment" of children is ignored.
     * Vertical: Children of the element will be placed from top to bottom. Attribute "VerticalAlignment" of children is ignored.
     */
    class StackView : virtual public Backgroundable
                    , virtual public Marginable
                    , virtual public Paddingable
                    , virtual public Childrenable
                    , virtual public Orientationable{
    public:
        StackView(rapidjson::Value& json);
        VisualElementType getType() const;
        virtual void OnMouse(const MouseState& new_state, const MouseState& old_state);
        virtual void Draw(cv::Mat& target);
        virtual void Measure(int desired_width, int desired_height);

    protected:

    };

}