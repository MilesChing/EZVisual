#include "EZVisual/Brushes/LinearGradientBrush.h"
#include <algorithm>
#include <cmath>

namespace EZVisual{

    Color Interpolate(const Color& c1, const Color& c2, double rate){
        double a = (c2.a - c1.a) * rate + c1.a;
        double r = (c2.r - c1.r) * rate + c1.r;
        double g = (c2.g - c1.g) * rate + c1.g;
        double b = (c2.b - c1.b) * rate + c1.b;
        return Color((u_char)a, (u_char)r, (u_char)g, (u_char)b);
    }

    LinearGradientBrush* LinearGradientBrush::CreateInstance(const vector<Color>& colors, double angle){
        return new LinearGradientBrush(colors, angle);
    }

    LinearGradientBrush* LinearGradientBrush::CreateInstance(const vector<pair<double, Color>>& of_co, double angle){
        return new LinearGradientBrush(of_co, angle);
    }

    LinearGradientBrush::LinearGradientBrush(rapidjson::Value& json){
        rapidjson::Value& colors = json["ColorFrames"];
        rapidjson::Value& offsets = json["OffsetFrames"];
        rapidjson::Value& angle_json = json["Angle"];
        double angle = 0.0;
        if(angle_json.IsNumber()) angle = angle_json.GetDouble();
        if(!colors.IsArray()) throw "\'ColorFrames\' not found.";
        auto color_array = colors.GetArray();
        if(color_array.Size() < 2)
            throw "\'ColorFrames\' must have at least two elements.";
        if(offsets.IsArray()){
            auto offset_array = offsets.GetArray();
            if(offset_array.Size() != color_array.Size())
                throw "\'OffsetFrames\' and \'ColorFrames\' must have the same size.";
            vector<pair<double, Color>> source;
            source.reserve(color_array.Size());
            for(int i = 0; i < color_array.Size(); ++i){
                if(!color_array[i].IsString())
                    throw "Color in \'ColorFrames\' must be string.";
                if(!offset_array[i].IsDouble() && !offset_array[i].IsNumber())
                    throw "Offset in \'OffsetFrames\' must be float.";
                source.emplace_back(offset_array[i].GetDouble(),
                    Color(color_array[i].GetString()));
            }
            new (this) LinearGradientBrush(source, angle);
        }
        else{
            vector<Color> source;
            source.reserve(color_array.Size());
            for(int i = 0; i < color_array.Size(); ++i){
                if(!color_array[i].IsString())
                    throw "Color in \'ColorFrames\' must be string.";
                source.emplace_back(color_array[i].GetString());
            }
            new (this) LinearGradientBrush(source, angle);
        }
    }

    void LinearGradientBrush::Draw(cv::Mat& view){
        double cols = view.cols;
        double rows = view.rows;
        for(int i = 0; i < view.rows; ++i)
            for(int j = 0; j < view.cols; ++j)
                GetColor(j / cols, i / rows).Cover(
                    view.at<cv::Vec3b>(i, j)
                );
    }

    EZVisual::Color LinearGradientBrush::GetColor(double std_x, double std_y) const{
        if(!y_reverse) std_y = 1.0 - std_y;
        if(x_reverse) std_x = 1.0 - std_x;
        double lc_y = fact_x * std_x + fact_y * std_y;
        double offset = lc_y / std_l;
        if(offset <= offset_color_pairs[0].first)
            return offset_color_pairs[0].second;
        else if(offset >= offset_color_pairs.back().first)
            return offset_color_pairs.back().second;
        else for(int i = 0; i < offset_color_pairs.size() - 1; ++i)
            if(offset <= offset_color_pairs[i + 1].first){
                if(offset_color_pairs[i+1].first == offset_color_pairs[i].first)
                    return offset_color_pairs[i+1].second;
                else if(offset_color_pairs[i].second == offset_color_pairs[i+1].second)
                    return offset_color_pairs[i].second;
                double rate = offset - offset_color_pairs[i].first;
                rate /= offset_color_pairs[i+1].first
                    - offset_color_pairs[i].first;
                return Interpolate(offset_color_pairs[i].second,
                    offset_color_pairs[i+1].second, rate);
            }
        return Color();
    }

    LinearGradientBrush::LinearGradientBrush(const vector<pair<double, Color>>& of_co, double ang)
        : offset_color_pairs(of_co), angle(ang){
        if(of_co.size() < 2) throw "LinearGradientBrush should have at least two frames.";
        sort(offset_color_pairs.begin(), offset_color_pairs.end());
        ComputeAngle();
    }

    LinearGradientBrush::LinearGradientBrush(const vector<Color>& colors, double ang)
        : offset_color_pairs(colors.size()), angle(ang){
        if(colors.size() < 2) throw "LinearGradientBrush should have at least two frames.";
        double d_offset = 1.0 / (colors.size() - 1);
        double current_offset = 0.0;
        for(int i = 0; i < colors.size(); ++i){
            offset_color_pairs[i].first = current_offset;
            offset_color_pairs[i].second = colors[i];
            current_offset += d_offset;
        }
        sort(offset_color_pairs.begin(), offset_color_pairs.end());
        ComputeAngle();
    }

    void LinearGradientBrush::ComputeAngle(){
        angle = angle * M_PI / 180.0;
        constexpr double PI_2 = M_PI * 2;
        double cosa = cos(angle);
        double sina = sin(angle);
        if(cosa < 0){
            angle = M_PI - angle;
            cosa = fabs(cosa);
            x_reverse = true;
        }
        if(sina < 0){
            angle = -angle;
            sina = fabs(sina);
            y_reverse = true;
        }
        while(angle < 0) angle += PI_2;
        while(angle >= PI_2) angle -= PI_2;
        fact_x = sina;
        fact_y = cosa;
        std_l = M_SQRT2 * sin(M_PI_2 + M_PI_4 - angle);
    }

    BrushType LinearGradientBrush::GetType() const{
        return BrushType::LinearGradientBrush;
    }


}