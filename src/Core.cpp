#include "EZVisual/Controls.h"
#include <sstream>
#include <string>

using namespace std;

namespace EZVisual{

    VisualElement* GetVisualElementFromType(const VisualElementType& type, rapidjson::Value& json){
        switch(type){
            case TYPE_BORDER: return new Border(json);
            case TYPE_STACK_VIEW: return new StackView(json);
            case TYPE_PLAIN_TEXT: return new PlainText(json);
            case TYPE_AUTO_WRAP_STACK: return new AutoWrapStack(json);
            case TYPE_CANVAS: return new Canvas(json);
        }

        return NULL;
    }

    Color::Color(u_char A, u_char R, u_char G, u_char B){
        a = A;
        r = R;
        g = G;
        b = B;
    }

    Color::Color(uchar R, uchar G, uchar B){
        r = R;
        g = G;
        b = B;
    }

    Color::Color(unsigned int color_int){
        a = (color_int & 0xff000000) >> 24;
        r = (color_int & 0x00ff0000) >> 16;
        g = (color_int & 0x0000ff00) >> 8;
        b = (color_int & 0x000000ff);
    }

    bool Color::operator ==(const Color& c) const{
        return r == c.r && g == c.g && b == c.b && a == c.a;
    }

    bool Color::operator !=(const Color& c) const{
        return ! this->operator==(c);
    }

    void Color::Cover(cv::Vec3b& v3) const{
        double alpha = ((int)a) / 255.0;
        v3[0] = (int)(alpha * b + (1 - alpha) * v3[0]);
        v3[1] = (int)(alpha * g + (1 - alpha) * v3[1]);
        v3[2] = (int)(alpha * r + (1 - alpha) * v3[2]);
    }

    void Color::Cover(cv::Mat& mat) const{
        for(int i = 0; i < mat.rows; ++i){
            for(int j = 0; j < mat.cols; ++j){
                cv::Vec3b& v3 = mat.at<cv::Vec3b>(i, j);
                this->Cover(v3);
            }
        }
    }

    void Color::Cover(Color& color) const{
        if(a == 255){
            color.a = 255;
            color.r = r;
            color.g = g;
            color.b = b;
            return;
        }

        double alpha_a = a * 1.0 / 255;
        double alpha_b = color.a * 1.0 / 255;

        if(alpha_a == 0) return;
        if(alpha_b == 0){
            color.a = a;
            color.r = r;
            color.g = g;
            color.b = b;
            return;
        }

        double new_a = 1 - (1 - alpha_a) * (1 - alpha_b);
        double new_r = (((alpha_a) * r + (1 - alpha_a) * alpha_b * color.r)) / new_a;
        double new_g = (((alpha_a) * g + (1 - alpha_a) * alpha_b * color.g)) / new_a;
        double new_b = (((alpha_a) * b + (1 - alpha_a) * alpha_b * color.b)) / new_a;
        color.a = round(new_a * 255);
        color.r = round(new_r * 255);
        color.g = round(new_g * 255);
        color.b = round(new_b * 255);
    }

    Color::operator unsigned int() const{
        unsigned int ai = a;
        unsigned int ri = r;
        unsigned int gi = g;
        unsigned int bi = b;
        return ai << 24 + ri << 16 + gi << 8 + bi;
    }

    Color::Color(const std::string& argb){
        stringstream str;
        if(argb[0] != '#') throw "Illegal color format: " + argb;
        else if(argb.length() == 7)
            str = stringstream("0xff" + argb.substr(1,6));
        else if(argb.length() == 9)
            str = stringstream("0x" + argb.substr(1,8));
        else throw "Illegal color format: " + argb;
        unsigned int color_int;
        if(str >> hex >> color_int){
            a = (color_int & 0xff000000) >> 24;
            r = (color_int & 0x00ff0000) >> 16;
            g = (color_int & 0x0000ff00) >> 8;
            b = (color_int & 0x000000ff);
        }
        else throw "Illegal color format: " + argb;
    }

    void Convert(const string& data, VisualElementType& attr){
        if(data == "Border") attr = TYPE_BORDER;
        else if(data == "StackView") attr = TYPE_STACK_VIEW;
        else if(data == "PlainText") attr = TYPE_PLAIN_TEXT;
        else if(data == "AutoWrapStack") attr = TYPE_AUTO_WRAP_STACK;
        else if(data == "Canvas") attr = TYPE_CANVAS;
    }

    void Convert(const string& data, HorizontalAlignment& attr){
        if(data == nameof(Left)) attr = Left;
        else if(data == nameof(Right)) attr = Right;
        else if(data == nameof(HorizontalCenter)) attr = HorizontalCenter;
    }

    void Convert(const string& data, VerticalAlignment& attr){
        if(data == nameof(Top)) attr = Top;
        else if(data == nameof(Bottom)) attr = Bottom;
        else if(data == nameof(VerticalCenter)) attr = VerticalCenter;
    }

    void Convert(const string& data, Orientation& attr){
        if(data == nameof(Horizontal)) attr = Horizontal;
        else if(data == nameof(Vertical)) attr = Vertical;
    }

}