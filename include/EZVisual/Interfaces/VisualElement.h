#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <map>
using namespace std;
using namespace rapidjson;
using namespace cv;

#ifndef _EZVISUAL_VISUAL_ELEMENT_
#define _EZVISUAL_VISUAL_ELEMENT_
namespace EZVisual{

    class Visualization;
    typedef function<void(const MouseEventParameter& parameter)> MouseListener;

    class VisualElement{
    public:
        virtual void Draw(cv::Mat& target) = 0;
        virtual void Measure(int desired_width, int desired_height) = 0;
        virtual VisualElementType getType() const = 0;

        int AddMouseListener(const MouseEventType& type, const MouseListener& listener);
        bool RemoveMouseListener(int listener_id);

        VisualElement(rapidjson::Value& json);
        virtual ~VisualElement(){};

        int GetMeasuredWidth() const;
        int GetMeasuredHeight() const;
        int GetId() const;

        HorizontalAlignment GetHorizontalAlignment() const;
        VerticalAlignment GetVerticalAlignment() const;

        virtual VisualElement* SearchElementById(int id);

        virtual bool CheckMouseEvent(const MouseEventParameter& params);

    protected:
        friend class Visualization;

        int id = -1, width = WRAP_CONTENT, height = WRAP_CONTENT;
        int measured_width = -1, measured_height = -1;
        int x = 0, y = 0;

        HorizontalAlignment horizontal_alignment = Left;
        VerticalAlignment vertical_alignment = Top;

        map<int, pair<MouseEventType, MouseListener>> listeners;

        bool is_mouse_in = false;

        void CallMouseEvent(const MouseEventType& type, const MouseEventParameter& param);

        void UpdateGlobalXY(const cv::Mat& target);
    };

}
#endif