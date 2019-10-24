#include "opencv2/opencv.hpp"

namespace EZVisual{
#ifndef _EZVISUAL_COLOR_
#define _EZVISUAL_COLOR_

    class Color{
    public:
        Color(){}

        Color(u_char A, u_char R, u_char G, u_char B){
            a = A;
            r = R;
            g = G;
            b = B;
        }

        Color(u_char R, u_char G, u_char B){
            r = R;
            g = G;
            b = B;
        }

        Color(unsigned int argb){
            a = (argb & 0xff000000) >> 24;
            r = (argb & 0x00ff0000) >> 16;
            g = (argb & 0x0000ff00) >> 8;
            b = (argb & 0x000000ff);
        }

        Color(const std::string& argb){
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

        void Cover(cv::Mat& mat) const{
            for(int i = 0; i < mat.rows; ++i){
                for(int j = 0; j < mat.cols; ++j){
                    cv::Vec3b& v3 = mat.at<cv::Vec3b>(i, j);
                    this->Cover(v3);
                }
            }
        }

        void Cover(cv::Vec3b& v3) const{
            double alpha = ((int)a) / 255.0;
            v3[0] = (int)(alpha * b + (1 - alpha) * v3[0]);
            v3[1] = (int)(alpha * g + (1 - alpha) * v3[1]);
            v3[2] = (int)(alpha * r + (1 - alpha) * v3[2]);
        }

        void Cover(Color& color) const{
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

        bool operator == (const Color& c) const{
            return r == c.r && g == c.g && b == c.b && a == c.a;
        }

        bool operator != (const Color& c) const{
            return ! this->operator==(c);
        }

        operator unsigned int() const{
            unsigned int ai = a;
            unsigned int ri = r;
            unsigned int gi = g;
            unsigned int bi = b;
            return ai << 24 + ri << 16 + gi << 8 + bi;
        }

        u_char a = 0xff, r = 0xff, g = 0xff, b = 0xff;
    };

#endif
}