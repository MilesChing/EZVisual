#include "EZVisual/Interfaces.h"
#include "opencv2/opencv.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "EZVisual/Core.h"

using namespace cv;

#ifndef _EZVISUAL_BORDER_
#define _EZVISUAL_BORDER_
namespace EZVisual{

    /**@brief Border is a visual frame with an optional content.
     *
     * Border is a visual frame with an optional content. Border without a content is just a rectangle with background color filled on the screen. Otherwise it will wrap the content and provide border and background for it due to its margins and paddings.
     */
    class Border : virtual public Backgroundable
                 , virtual public Marginable
                 , virtual public Paddingable
                 , virtual public Contentable{
    public:
        Border(rapidjson::Value& json);

        void Draw(cv::Mat& target);
        void Measure(int desired_width, int desired_height);

        bool CheckMouseEvent(const MouseEventParameter& params);

        VisualElementType getType() const;
    };

}
#endif