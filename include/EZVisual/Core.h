#include <string>
#include "opencv2/opencv.hpp"
using namespace std;

#ifndef _EZVISUAL_CORE_
#define _EZVISUAL_CORE_

#define nameof(x) (#x)

namespace EZVisual{

    class VisualElement;

    enum HorizontalAlignment{
        Left,
        Right,
        HorizontalCenter
    };

    enum VerticalAlignment{
        Top,
        Bottom,
        VerticalCenter
    };

    enum VisualElementType{
        TYPE_BORDER,
        TYPE_STACK_VIEW,
        TYPE_PLAIN_TEXT,
        TYPE_IMAGE_VIEW,
        TYPE_AUTO_WRAP_STACK
    };

    enum Orientation{
        Horizontal,
        Vertical
    };

    class Color{
    public:
        Color(){}

        Color(u_char A, u_char R, u_char G, u_char B);

        Color(u_char R, u_char G, u_char B);

        Color(unsigned int argb);

        Color(const std::string& argb);

        void Cover(cv::Mat& mat) const;

        void Cover(cv::Vec3b& v3) const;

        bool operator == (const Color& c) const;

        bool operator != (const Color& c) const;

        operator unsigned int() const;

        u_char a = 0x00, r = 0xff, g = 0xff, b = 0xff;
    };

    void Convert(const string& data, HorizontalAlignment& attr);
    void Convert(const string& data, VerticalAlignment& attr);
    void Convert(const string& data, VisualElementType& attr);
    void Convert(const string& data, Orientation& attr);

    VisualElement* GetVisualElementFromType(const VisualElementType& type);
}

#endif