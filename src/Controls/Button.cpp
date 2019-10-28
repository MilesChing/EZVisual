#include "EZVisual/Controls/Button.h"

namespace EZVisual{

    Button::Button(rapidjson::Value& json) :
        Border(json),
        Backgroundable(json),
        Marginable(json),
        Paddingable(json),
        Contentable(json),
        VisualElement(json){
        Clicked.BindTrigger(&ClickedTrigger);
        if(json["MouseOverBackground"].IsNull())
            MouseOverBackground = NULL;
        else MouseOverBackground =
            Brush::CreateInstance(json["MouseOverBackground"]);
        if(json["MousePressedBackground"].IsNull())
            MousePressedBackground = NULL;
        else MousePressedBackground =
            Brush::CreateInstance(json["MousePressedBackground"]);

        MouseEntered += [this](const MouseEventParameter& param){
            ChangeBackground = MouseOverBackground;
        };

        MouseExited += [this](const MouseEventParameter& param){
            ChangeBackground = NULL;
            ClickedTrigger.Invoke(this);
        };

        MousePressed += [this](const MouseEventParameter& param){
            ChangeBackground = MousePressedBackground;
        };

        MouseReleased += [this](const MouseEventParameter& param){
            ChangeBackground = NULL;
        };
    }

    VisualElementType Button::getType() const{
        return VisualElementType::Button;
    }

    void Button::OnDrawBackground(cv::Mat& border_roi){
        if(ChangeBackground) ChangeBackground->Draw(border_roi);
        else background->Draw(border_roi);
    }

    Button::~Button(){
        if(MouseOverBackground) delete MouseOverBackground;
        if(MousePressedBackground) delete MousePressedBackground;
    }

}