#pragma once
#include "EZVisual/Brushes/Brush.h"
#include "EZVisual/Brushes/Color.hpp"
#include <vector>
#include <map>

namespace EZVisual{

    class LinearGradientBrush : public Brush{
    public:
        static LinearGradientBrush* CreateInstance(const vector<Color>& colors, double angle = 0);
        static LinearGradientBrush* CreateInstance(const vector<pair<double, Color>>& offset_color_pairs, double angle = 0);
        BrushType GetType() const;
        void Draw(cv::Mat& mat);
        Brush* GetCopy() const;
    protected:
        friend class Brush;
        vector<pair<double, Color>> offset_color_pairs;
        double angle = 0;
        //pre-compute values
        double fact_x, fact_y, std_l;
        bool x_reverse = false;
        bool y_reverse = false;
        LinearGradientBrush(const vector<Color>& colors, double angle = 0);
        LinearGradientBrush(const vector<pair<double, Color>>& offset_color_pairs, double angle = 0);
        LinearGradientBrush(rapidjson::Value& json);
        void ComputeAngle();
        EZVisual::Color GetColor(double std_x, double std_y) const;
    };

}