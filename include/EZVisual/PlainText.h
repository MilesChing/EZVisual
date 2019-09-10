#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "EZVisual/Interfaces.h"
#include <string>

using namespace std;
using namespace cv;


namespace EZVisual{
#ifndef _EZVISUAL_PLAIN_TEXT_
#define _EZVISUAL_PLAIN_TEXT_
    class PlainText : virtual public Textable
                    , virtual public Marginable{
    public:
        PlainText(rapidjson::Value& json);
        ~PlainText(){};

        void Draw(cv::Mat& target);
        void Measure();

        VisualElementType getType() const;

    protected:
        int base_line_height;

    };
#endif
}
