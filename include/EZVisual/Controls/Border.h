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

    class Border : virtual public Backgroundable
                 , virtual public Marginable
                 , virtual public Paddingable
                 , virtual public Contentable{
    public:
        Border(rapidjson::Value& json);
        ~Border();

        void Draw(cv::Mat& target) const;
        void Measure(int desired_width, int desired_height);

        VisualElementType getType() const;
    };

}
#endif