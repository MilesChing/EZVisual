#pragma once
#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "EZVisual/Interfaces.h"
#include <string>

using namespace std;
using namespace cv;


namespace EZVisual{
    /**@brief PlainText is just a single line of text with optional margin.
     *
     * PlainText is just a single line of text with optional margin. The text will not be wrapped but be clipped directly when the width of it is limited.
     */
    class PlainText : virtual public Textable
                    , virtual public Marginable{
    public:
        PlainText(rapidjson::Value& json);
        VisualElementType getType() const;

    protected:
        int base_line_height;

        void OnDraw(cv::Mat& target);
        void OnMeasure(int desired_width, int desired_height);
    };
}
