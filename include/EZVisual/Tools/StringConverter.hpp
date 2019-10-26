#pragma once
#include "EZVisual/Core.h"
#include "EZVisual/Brushes/Brush.h"

namespace EZVisual{

    class StringConverter{
    public:
        static VisualElementType ToVisualElementType(const string& str){
            if(str == "Border") return VisualElementType::Border;
            else if(str == "StackView") return VisualElementType::StackView;
            else if(str == "PlainText") return VisualElementType::PlainText;
            else if(str == "Canvas") return VisualElementType::Canvas;
            else return VisualElementType::Null;
        }

        static HorizontalAlignment ToHorizontalAlignment(const string& str){
            if(str == "Left") return HorizontalAlignment::Left;
            else if(str == "Right") return HorizontalAlignment::Right;
            else if(str == "Center") return HorizontalAlignment::Center;
            else return HorizontalAlignment::Null;
        }

        static VerticalAlignment ToVerticalAlignment(const string& str){
            if(str == "Top") return VerticalAlignment::Top;
            else if(str == "Bottom") return VerticalAlignment::Bottom;
            else if(str == "Center") return VerticalAlignment::Center;
            else return VerticalAlignment::Null;
        }

        static Orientation ToOrientation(const string& str){
            if(str == "Horizontal") return Orientation::Horizontal;
            else if(str == "Vertical") return Orientation::Vertical;
            else return Orientation::Null;
        }

        static BrushType ToBrushType(const string& str){
            if(str == "SolidColorBrush") return BrushType::SolidColorBrush;
            else if(str == "LinearGradientBrush") return BrushType::LinearGradientBrush;
            else return BrushType::Null;
        }
    };
}