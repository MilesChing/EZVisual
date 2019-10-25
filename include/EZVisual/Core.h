#pragma once
#include <string>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace rapidjson;

namespace EZVisual{

    class VisualElement;

    const int WRAP_CONTENT = 0;
    const int FILL_PARENT = -1;

    enum class MouseEventType : std::uint8_t{
        Null = 0,
        MouseEntered = 1,
        MouseExited = 2,
        MouseMoving = 3,
        MouseLeftPressed = 4,
        MouseRightPressed = 5,
        MouseLeftReleased = 6,
        MouseRightReleased = 7
    };

    struct MouseEventParameter{
        int relative_x;
        int relative_y;
        //Left, Right, Middle
        MouseEventType current_event_type;
        VisualElement* sender;
    };

    enum class HorizontalAlignment : std::uint8_t{
        Null = 0,
        Left = 1,
        Right = 2,
        Center = 3
    };

    enum class VerticalAlignment : std::uint8_t{
        Null = 0,
        Top = 1,
        Bottom = 2,
        Center = 3
    };

    enum class VisualElementType : std::uint8_t{
        Null = 0,
        Border = 1,
        StackView = 2,
        PlainText = 3,
        Canvas = 4
    };

    enum class Orientation : std::uint8_t{
        Null = 0,
        Horizontal = 1,
        Vertical = 2
    };

}