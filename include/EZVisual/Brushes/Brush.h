#pragma once
#include "opencv2/opencv.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace EZVisual{

    enum class BrushType : std::uint8_t{
        Null = 0,
        SolidColorBrush = 1,
        LinearGradientBrush = 2
    };

    class Brush{
    public:
        static Brush* CreateInstance(rapidjson::Value& json);
        virtual void Draw(cv::Mat& mat) = 0;
        virtual BrushType GetType() const;
        virtual ~Brush(){}
    protected:
        Brush(){}
    };

}