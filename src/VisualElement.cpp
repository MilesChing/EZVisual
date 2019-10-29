#include "EZVisual/Interfaces.h"
#include "EZVisual/Controls.h"
#include "EZVisual/Tools/StringConverter.hpp"
#include <string>

using namespace std;
using namespace cv;

namespace EZVisual{

    VisualElement* VisualElement::CreateInstance(rapidjson::Value& json){
        if(json["Type"].IsNull()){
            cerr << "Error: \'Type\' not found." << endl;
            return NULL;
        }
        VisualElementType type = StringConverter::ToVisualElementType(
            json["Type"].GetString()
        );
        switch(type){
            case VisualElementType::Border: return new Border(json);
            case VisualElementType::StackView: return new StackView(json);
            case VisualElementType::PlainText: return new PlainText(json);
            case VisualElementType::Canvas: return new Canvas(json);
            case VisualElementType::Button: return new Button(json);
            default: return NULL;
        }
    }

    int VisualElement::GetMeasuredWidth() const{
        return measured_width;
    }

    int VisualElement::GetMeasuredHeight() const{
        return measured_height;
    }

    int VisualElement::GetId() const{
        return id;
    }

    int VisualElement::GetX() const{
        return x;
    }

    int VisualElement::GetY() const{
        return y;
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
        MousePressed.BindTrigger(&MousePressedTrigger);
        MouseRightPressed.BindTrigger(&MouseRightPressedTrigger);
        MouseReleased.BindTrigger(&MouseReleasedTrigger);
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
            horizontal_alignment = StringConverter::ToHorizontalAlignment(
                json["HorizontalAlignment"].GetString()
            );
        if(!json["VerticalAlignment"].IsNull())
            vertical_alignment = StringConverter::ToVerticalAlignment(
                json["VerticalAlignment"].GetString()
            );
    }

    VisualElement* VisualElement::SearchElementById(int id){
        if(this->id == id) return this;
        else return NULL;
    }

    void VisualElement::UpdateGlobalXY(const cv::Mat& target){
        static cv::Point xy;
        static cv::Size sz;
        target.locateROI(sz, xy);
        x = xy.x;
        y = xy.y;
    }

    void VisualElement::HandleBasicMouseEvents(const MouseState& new_state, const MouseState& old_state) const{
        const bool new_is_mouse_in = IsMouseIn(new_state);
        const bool old_is_mouse_in = IsMouseIn(old_state);
        MouseEventParameter param;
        param.sender = (VisualElement*)(void*)this;
        param.mouse_state = new_state;

        //MouseEntered & MouseExited
        if(old_is_mouse_in ^ new_is_mouse_in){
            if(old_is_mouse_in) MouseExitedTrigger.Invoke(param);
            else MouseEnteredTrigger.Invoke(param);
        }

        //MouseMoving
        if(new_state.global_x != old_state.global_x &&
            new_state.global_y != old_state.global_y && new_is_mouse_in)
            MouseMovingTrigger.Invoke(param);

        //MousePressed & MouseReleased
        if(new_is_mouse_in && new_state.left_button != old_state.left_button){
            if(new_state.left_button == MouseState::ButtonState::Pressed)
                MousePressedTrigger.Invoke(param);
            else MouseReleasedTrigger.Invoke(param);
        }

        //MouseRightPressed & MouseRightReleased
        if(new_is_mouse_in && new_state.right_button != old_state.right_button){
            if(new_state.right_button == MouseState::ButtonState::Pressed)
                MousePressedTrigger.Invoke(param);
            else MouseReleasedTrigger.Invoke(param);
        }
    }

    void VisualElement::OnMouse(const MouseState& new_state, const MouseState& old_state){
        HandleBasicMouseEvents(new_state, old_state);
    }

    bool VisualElement::IsMouseIn(const MouseState& state) const{
        return (
            state.global_x >= x &&
            state.global_y >= y &&
            state.global_x <= x + measured_width &&
            state.global_y <= y + measured_height
        );
    }
}