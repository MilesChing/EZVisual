#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
using namespace std;
using namespace rapidjson;

#ifndef _EZVISUAL_VISUAL_ELEMENT_
#define _EZVISUAL_VISUAL_ELEMENT_
namespace EZVisual{

    class Visualization;

    class VisualElement{
    public:
        virtual void Draw(cv::Mat& target) const = 0;
        virtual void Measure(int desired_width, int desired_height) = 0;
        virtual VisualElementType getType() const = 0;

        VisualElement(rapidjson::Value& json);
        virtual ~VisualElement(){};

        int GetMeasuredWidth() const;
        int GetMeasuredHeight() const;
        int GetId() const;

        HorizontalAlignment GetHorizontalAlignment() const;
        VerticalAlignment GetVerticalAlignment() const;

        virtual VisualElement* SearchElementById(int id);

    protected:
        int id = -1, width = WRAP_CONTENT, height = WRAP_CONTENT, measured_width = -1, measured_height = -1;
        HorizontalAlignment horizontal_alignment = Left;
        VerticalAlignment vertical_alignment = Top;
    };


}
#endif