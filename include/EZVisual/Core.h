#include <string>
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

        u_char R() const;
        u_char G() const;
        u_char B() const;

        Color(u_char R, u_char G, u_char B);

        Color(int rgb);

        Color(const string& rgb);

        bool operator ==(const Color& c) const;

    protected:
        u_char r = 0xff, g = 0xff, b = 0xff;
    };

    void Convert(const string& data, HorizontalAlignment& attr);
    void Convert(const string& data, VerticalAlignment& attr);
    void Convert(const string& data, VisualElementType& attr);
    void Convert(const string& data, Orientation& attr);

    VisualElement* GetVisualElementFromType(const VisualElementType& type);
}

#endif