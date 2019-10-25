#pragma once
#include "opencv2/opencv.hpp"

using namespace std;

namespace EZVisual{

    enum class BrushType : std::uint8_t{
        Null = 0,
        SolidColorBrush = 1
    };

    class Brush{
    public:
        static Brush* CreateInstance(BrushType);
        virtual void Draw(cv::Mat& mat) = 0;
    private:
        Brush(){};
    };

}