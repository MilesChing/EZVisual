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


    class MouseState{
    public:
        int global_x = -1;
        int global_y = -1;
        enum class ButtonState : std::uint8_t{
            Released = 0,
            Pressed = 1
        };

        ButtonState left_button = ButtonState::Released;
        ButtonState right_button = ButtonState::Released;
    };

    class MouseEventParameter{
    public:
        VisualElement* sender;
        MouseState mouse_state;
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
        Canvas = 4,
        Button = 5
    };

    enum class Orientation : std::uint8_t{
        Null = 0,
        Horizontal = 1,
        Vertical = 2
    };

}