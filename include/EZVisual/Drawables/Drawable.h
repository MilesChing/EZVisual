#include "opencv2/opencv.hpp"

namespace EZVisual{
#ifndef _EZVISUAL_DRAWABLE_
#define _EZVISUAL_DRAWABLE_

    class Drawable{
    public:
        virtual void Draw(cv::Mat& mat) = 0;
    };

#endif
}