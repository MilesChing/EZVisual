#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <vector>
#include <map>
#include <mutex>
using namespace std;
using namespace rapidjson;

#ifndef _EZVISUAL_VISUAL_ELEMENT_
#define _EZVISUAL_VISUAL_ELEMENT_
namespace EZVisual{

    class Visualization;

    class VisualElement{
    public:
        virtual void Draw(cv::Mat& target) = 0;
        virtual void Measure() = 0;
        virtual VisualElementType getType() const = 0;

        virtual ~VisualElement(){};

        int GetWidth();
        int GetHeight();
        int GetId();
        HorizontalAlignment GetHorizontalAlignment();
        VerticalAlignment GetVerticalAlignment();

        virtual bool NeedRedraw() const = 0;

        virtual void SetByJSON(rapidjson::Value& json);
        virtual void RegistId(map<int, VisualElement*>& controls) = 0;

        virtual void SetBackground(const Color& color){ throw "Unsupported attribute."; }
        virtual void SetContent(VisualElement* content){ throw "Unsupported attribute."; }
        virtual void SetMargin(int left, int top, int right, int bottom){ throw "Unsupported attribute."; }
        virtual void SetMinHeight(int min_height){ throw "Unsupported attribute."; }
        virtual void SetMinWidth(int min_width){ throw "Unsupported attribute."; }
        virtual void SetOrientation(const Orientation& orientation){ throw "Unsupported attribute."; }
        virtual void SetPadding(int left, int top, int right, int bottom){ throw "Unsupported attribute."; }
        virtual void SetText(const char* text){ throw "Unsupported attribute."; }
        virtual void SetFontSize(double font_size){ throw "Unsupported attribute."; }
        virtual void SetFontColor(const Color& color){ throw "Unsupported attribute."; }
        virtual void SetFontWeight(int font_weight){ throw "Unsupported attribute."; }
        virtual void SetFontFamily(int font_family){ throw "Unsupported attribute."; }
        virtual void SetLayer(int layer_index, const vector<tuple<int, int>>& layer, const Color& layer_color){ throw "Unsupported attribute."; }
        virtual void SetLayer(int layer_index, const vector<int>& layer){ throw "Unsupported attribute."; }
        virtual void SetWrapLength(int length){ throw "Unsupported attribute."; }

    protected:
        int id = -1, width = -1, height = -1;
        bool need_redraw = false;
        HorizontalAlignment horizontal_alignment = Left;
        VerticalAlignment vertical_alignment = Top;
    };


}
#endif