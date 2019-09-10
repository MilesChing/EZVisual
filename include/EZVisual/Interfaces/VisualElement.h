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

        VisualElement(rapidjson::Value& json);
        virtual ~VisualElement(){};

        int GetWidth();
        int GetHeight();
        int GetId();

        HorizontalAlignment GetHorizontalAlignment();
        VerticalAlignment GetVerticalAlignment();

        virtual VisualElement* SearchElementById(int id);

    protected:
        int id = -1, width = -1, height = -1;
        HorizontalAlignment horizontal_alignment = Left;
        VerticalAlignment vertical_alignment = Top;

    };


}
#endif