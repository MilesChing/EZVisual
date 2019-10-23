#include "EZVisual/Interfaces.h"
#include <string>

using namespace std;
using namespace cv;

namespace EZVisual{

    int VisualElement::GetMeasuredWidth() const{
        return measured_width;
    }

    int VisualElement::GetMeasuredHeight() const{
        return measured_height;
    }

    int VisualElement::GetId() const{
        return id;
    }

    HorizontalAlignment VisualElement::GetHorizontalAlignment() const{
        return horizontal_alignment;
    }

    VerticalAlignment VisualElement::GetVerticalAlignment() const{
        return vertical_alignment;
    }

    void VisualElement::BindEventTriggers(){
        MouseEntered.BindTrigger(&MouseEnteredTrigger);
        MouseExited.BindTrigger(&MouseExitedTrigger);
        MouseMoving.BindTrigger(&MouseMovingTrigger);
        MouseLeftPressed.BindTrigger(&MouseLeftPressedTrigger);
        MouseRightPressed.BindTrigger(&MouseRightPressedTrigger);
        MouseLeftReleased.BindTrigger(&MouseLeftReleasedTrigger);
        MouseRightReleased.BindTrigger(&MouseRightReleasedTrigger);
    }

    VisualElement::VisualElement(rapidjson::Value& json){
        BindEventTriggers();
        //get id
        if(json["Id"].IsInt()) id = json["Id"].GetInt();
        //get Height
        if(json["Height"].IsInt()) height = json["Height"].GetInt();
        else if(json["Height"].IsString()){
            string tmp = json["Height"].GetString();
            if(tmp == "WrapContent") height = WRAP_CONTENT;
            else if(tmp == "FillParent") height = FILL_PARENT;
            else throw "Illegal Height value.";
        }
        //get Width
        if(json["Width"].IsInt()) width = json["Width"].GetInt();
        else if(json["Width"].IsString()){
            string tmp = json["Width"].GetString();
            if(tmp == "WrapContent") width = WRAP_CONTENT;
            else if(tmp == "FillParent") width = FILL_PARENT;
            else throw "Illegal Width value.";
        }
        //get Alignment
        if(!json["HorizontalAlignment"].IsNull())
            Convert(json["HorizontalAlignment"].GetString(), horizontal_alignment);
        if(!json["VerticalAlignment"].IsNull())
            Convert(json["VerticalAlignment"].GetString(), vertical_alignment);
    }

    VisualElement* VisualElement::SearchElementById(int id){
        if(this->id == id) return this;
        else return NULL;
    }

    bool VisualElement::CheckMouseEvent(const MouseEventParameter& params){
        bool in_this = params.relative_x >= x && params.relative_x < x + measured_width
            && params.relative_y >= y && params.relative_y < y + measured_height;
        MouseEventParameter rel_tmp(params);
        rel_tmp.relative_x = params.relative_x - x;
        rel_tmp.relative_y = params.relative_y - y;
        if(params.current_event_type == MouseEventType::MouseMoving){
            if(in_this ^ is_mouse_in){
                if(in_this) CallMouseEvent(MouseEventType::MouseEntered, rel_tmp);
                else CallMouseEvent(MouseEventType::MouseExited, rel_tmp);
                is_mouse_in = in_this;
                return true;
            }
            else if(in_this) CallMouseEvent(MouseEventType::MouseMoving, rel_tmp);
            else return false;
        }
        else if(in_this){
            CallMouseEvent(params.current_event_type, rel_tmp);
            return true;
        }
        else return false;
    }

    void VisualElement::CallMouseEvent(const MouseEventType& type, MouseEventParameter& param){
        param.sender = this;
        param.current_event_type = type;
        switch(param.current_event_type){
            case MouseEventType::MouseEntered: MouseEnteredTrigger.Invoke(param); break;
            case MouseEventType::MouseExited: MouseExitedTrigger.Invoke(param); break;
            case MouseEventType::MouseMoving: MouseMovingTrigger.Invoke(param); break;
            case MouseEventType::MouseLeftPressed: MouseLeftPressedTrigger.Invoke(param); break;
            case MouseEventType::MouseRightPressed: MouseRightPressedTrigger.Invoke(param); break;
            case MouseEventType::MouseLeftReleased: MouseLeftReleasedTrigger.Invoke(param); break;
            case MouseEventType::MouseRightReleased: MouseRightReleasedTrigger.Invoke(param); break;
            default: break;
        }
    }

    void VisualElement::UpdateGlobalXY(const cv::Mat& target){
        static cv::Point xy;
        static cv::Size sz;
        target.locateROI(sz, xy);
        x = xy.x;
        y = xy.y;
    }

}