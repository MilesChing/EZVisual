#pragma once
#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "EZVisual/Tools/SharedMutex.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "EZEvent/Event.h"
#include <map>
using namespace std;
using namespace rapidjson;
using namespace cv;
using namespace EZEvent;

namespace EZVisual{

    class Visualization;

    typedef function<void(const MouseEventParameter& parameter)> MouseListener;

    class VisualElement{
    private:
        EventTrigger<MouseEventParameter> MouseEnteredTrigger;
        EventTrigger<MouseEventParameter> MouseExitedTrigger;
        EventTrigger<MouseEventParameter> MouseMovingTrigger;
        EventTrigger<MouseEventParameter> MouseLeftPressedTrigger;
        EventTrigger<MouseEventParameter> MouseRightPressedTrigger;
        EventTrigger<MouseEventParameter> MouseLeftReleasedTrigger;
        EventTrigger<MouseEventParameter> MouseRightReleasedTrigger;

        void BindEventTriggers();

    public:
        static VisualElement* CreateInstance(rapidjson::Value& json);
        void Measure(int desired_width, int desired_height);
        void Draw(cv::Mat& target);
        virtual VisualElementType getType() const = 0;

        Event<MouseEventParameter> MouseEntered;
        Event<MouseEventParameter> MouseExited;
        Event<MouseEventParameter> MouseMoving;
        Event<MouseEventParameter> MouseLeftPressed;
        Event<MouseEventParameter> MouseRightPressed;
        Event<MouseEventParameter> MouseLeftReleased;
        Event<MouseEventParameter> MouseRightReleased;

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
        virtual void OnDraw(cv::Mat& target) = 0;
        virtual void OnMeasure(int desired_width, int desired_height) = 0;

        EZVisual::shared_mutex measure_and_draw_mtx;

        int id = -1, width = WRAP_CONTENT, height = WRAP_CONTENT;
        int measured_width = -1, measured_height = -1;
        int x = 0, y = 0;

        HorizontalAlignment horizontal_alignment = HorizontalAlignment::Left;
        VerticalAlignment vertical_alignment = VerticalAlignment::Top;

        bool is_mouse_in = false;

        void CallMouseEvent(const MouseEventType& type, MouseEventParameter& param);

        void UpdateGlobalXY(const cv::Mat& target);
    };

}