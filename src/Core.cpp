#include "EZVisual/Core.h"
#include "EZVisual/Border.h"
#include "EZVisual/StackView.h"
#include "EZVisual/PlainText.h"
#include "EZVisual/AutoWrapStack.h"
#include <sstream>

namespace EZVisual{

    VisualElement* GetVisualElementFromType(const VisualElementType& type){
        switch(type){
            case TYPE_BORDER: return new Border;
            case TYPE_STACK_VIEW: return new StackView;
            case TYPE_PLAIN_TEXT: return new PlainText;
            case TYPE_AUTO_WRAP_STACK: return new AutoWrapStack;
        }

        return NULL;
    }

    u_char Color::R() const{ return r; }
    u_char Color::G() const{ return g; }
    u_char Color::B() const{ return b; }

    Color::Color(uchar R, uchar G, uchar B){
        r = R;
        g = G;
        b = B;
    }

    Color::Color(int rgb){
        r = (rgb & 0xff0000) >> 16;
        g = (rgb & 0x00ff00) >> 8;
        b = (rgb & 0x0000ff);
    }

    bool Color::operator ==(const Color& c) const{
        return r == c.r && g == c.g && b == c.b;
    }

    Color::Color(const string& rgb){
        string target;
        switch(rgb.length()){
            case 6: target = "0x" + rgb; break;
            case 7: target = "0x" + rgb.substr(1, 6); break;
            case 8: target = rgb; break;
            default: throw "Illegal color format.";
        }

        stringstream str(target);
        int p;
        str >> hex >> p;
        r = (p & 0xff0000) >> 16;
        g = (p & 0x00ff00) >> 8;
        b = (p & 0x0000ff);
    }

    void Convert(const string& data, VisualElementType& attr){
        if(data == "Border") attr = TYPE_BORDER;
        else if(data == "StackView") attr = TYPE_STACK_VIEW;
        else if(data == "PlainText") attr = TYPE_PLAIN_TEXT;
        else if(data == "AutoWrapStack") attr = TYPE_AUTO_WRAP_STACK;
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