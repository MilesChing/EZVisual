#pragma once
#include "EZVisual/Brushes/Brush.h"
#include "EZVisual/Brushes/Color.hpp"

using namespace rapidjson;

namespace EZVisual{

    class SolidColorBrush : public Brush{
    public:
        static SolidColorBrush* CreateInstance(EZVisual::Color color = 0x0);
        BrushType GetType() const;
        void Draw(cv::Mat& mat);
        EZVisual::Color GetColor() const;
        Brush* GetCopy() const;
    protected:
        friend class Brush;
        EZVisual::Color color = 0x0;
        SolidColorBrush(EZVisual::Color color = 0x0);
        SolidColorBrush(rapidjson::Value& json);
    };

}