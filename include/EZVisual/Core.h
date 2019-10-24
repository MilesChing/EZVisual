#include <string>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace rapidjson;

#ifndef _EZVISUAL_CORE_
#define _EZVISUAL_CORE_

#define _def_enum(e) \
    private: \
        int inner_int = 0;  \
    public: \
        e(){}   \
        e operator =(int i){ inner_int = i; }    \
        bool operator ==(const e& o) const{ return o.inner_int == inner_int; } \
        bool operator ==(int o) const{ return o == inner_int; } \
        operator int() const{ return inner_int; }   \
        e(int i){ inner_int = i; }  \
        static const int Null = 0
#define _def_item(e, val) \
    static const int e = val


namespace EZVisual{

    class VisualElement;

    const int WRAP_CONTENT = 0;
    const int FILL_PARENT = -1;

    class MouseEventType{
        _def_enum(MouseEventType);
        _def_item(MouseEntered, 1);
        _def_item(MouseExited, 2);
        _def_item(MouseMoving, 3);
        _def_item(MouseLeftPressed, 4);
        _def_item(MouseRightPressed, 5);
        _def_item(MouseLeftReleased, 6);
        _def_item(MouseRightReleased, 7);
    };

    struct MouseEventParameter{
        int relative_x;
        int relative_y;
        //Left, Right, Middle
        MouseEventType current_event_type;
        VisualElement* sender;
    };

    class HorizontalAlignment{
        _def_enum(HorizontalAlignment);
        _def_item(Left, 1);
        _def_item(Right, 2);
        _def_item(Center, 3);
    };

    class VerticalAlignment{
        _def_enum(VerticalAlignment);
        _def_item(Top, 1);
        _def_item(Bottom, 2);
        _def_item(Center, 3);
    };

    class VisualElementType{
        _def_enum(VisualElementType);
        _def_item(Border, 1);
        _def_item(StackView, 2);
        _def_item(PlainText, 3);
        _def_item(Canvas, 4);
    };

    class Orientation{
        _def_enum(Orientation);
        _def_item(Horizontal, 1);
        _def_item(Vertical, 2);
    };

}

#endif