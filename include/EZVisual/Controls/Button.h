#pragma once
#include "EZVisual/Interfaces.h"
#include "opencv2/opencv.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "EZVisual/Core.h"
#include "EZVisual/Controls/Border.h"

using namespace cv;

namespace EZVisual{

    /**@brief Border is a visual frame with an optional content.
     *
     * Border is a visual frame with an optional content. Border without a content is just a rectangle with background color filled on the screen. Otherwise it will wrap the content and provide border and background for it due to its margins and paddings.
     */
    class Button : virtual public Border{
    public:
        EZEvent::Event<Button*> Clicked;

        Button(rapidjson::Value& json);
        virtual ~Button();
        virtual VisualElementType getType() const;
    protected:
        virtual void OnDrawBackground(cv::Mat& border_roi);

        EZEvent::EventTrigger<Button*> ClickedTrigger;

        //Brushes
        Brush* MouseOverBackground = NULL;
        Brush* MousePressedBackground = NULL;
        Brush* ChangeBackground = NULL;
    };

}