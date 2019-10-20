#include <string>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "opencv2/opencv.hpp"
#include <chrono>
#include <ctime>
using namespace std;
using namespace rapidjson;

#ifndef _EZVISUAL_CORE_
#define _EZVISUAL_CORE_

#define nameof(x) (#x)

namespace EZVisual{

    const int WRAP_CONTENT = 0;
    const int FILL_PARENT = -1;

    class VisualElement;


    enum MouseEventType{
        MouseEntered,
        MouseLeaved,
        MouseMoving,
        MouseLeftPressed,
        MouseRightPressed,
        MouseLeftReleased,
        MouseRightReleased
    };

    struct MouseEventParameter{
        int relative_x;
        int relative_y;
        //Left, Right, Middle
        MouseEventType current_event_type;
        VisualElement* sender;
    };

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
        TYPE_CANVAS
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

        void Cover(Color& color) const;

        bool operator == (const Color& c) const;

        bool operator != (const Color& c) const;

        operator unsigned int() const;

        u_char a = 0xff, r = 0xff, g = 0xff, b = 0xff;
    };

    void Convert(const string& data, HorizontalAlignment& attr);
    void Convert(const string& data, VerticalAlignment& attr);
    void Convert(const string& data, VisualElementType& attr);
    void Convert(const string& data, Orientation& attr);

    VisualElement* GetVisualElementFromType(const VisualElementType& type, rapidjson::Value& json);

    std::time_t GetTimeMs();

}

#endif