#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "EZVisual/Interfaces.h"
#include <string>

using namespace std;
using namespace cv;


namespace EZVisual{
#ifndef _EZVISUAL_PLAIN_TEXT_
#define _EZVISUAL_PLAIN_TEXT_

    /**@brief PlainText is just a single line of text with optional margin.
     *
     * PlainText is just a single line of text with optional margin. The text will not be wrapped but be clipped directly when the width of it is limited.
     */
    class PlainText : virtual public Textable
                    , virtual public Marginable{
    public:
        PlainText(rapidjson::Value& json);

        void Draw(cv::Mat& target);
        void Measure(int desired_width, int desired_height);

        VisualElementType getType() const;

    protected:
        int base_line_height;

    };
#endif
}
