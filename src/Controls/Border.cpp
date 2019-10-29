#include "EZVisual/Controls/Border.h"

namespace EZVisual{

    Border::Border(rapidjson::Value& json) :
        Backgroundable(json),
        Marginable(json),
        Paddingable(json),
        Contentable(json),
        VisualElement(json){}

    void Border::Draw(cv::Mat& target){
        if(measured_height == 0 || measured_width == 0) return;
        if(target.rows < measured_height || target.cols < measured_width)
            throw "Border::Draw() need more space.";

        if(control_border_width > 0 && control_border_height > 0){
            Mat border_roi(target, Rect(margin[0], margin[1],
                    control_border_width, control_border_height));
            UpdateGlobalXY(border_roi);
            DrawBackground(border_roi);

            if(content_space_width > 0 && content_space_height > 0 && content){
                int content_x = 0, content_y = 0;
                switch (content->GetHorizontalAlignment()){
                    case HorizontalAlignment::Left:
                        content_x = padding[0];
                        break;
                    case HorizontalAlignment::Right:
                        content_x = control_border_width - padding[2]
                            - content->GetMeasuredWidth();
                        break;
                    case HorizontalAlignment::Center:
                        content_x = (control_border_width
                            - content->GetMeasuredWidth()) / 2;
                        break;
                }

                switch (content->GetVerticalAlignment()){
                    case VerticalAlignment::Top:
                        content_y = padding[1];
                        break;
                    case VerticalAlignment::Bottom:
                        content_y = control_border_height - padding[3]
                            - content->GetMeasuredHeight();
                        break;
                    case VerticalAlignment::Center:
                        content_y = (control_border_height
                            - content->GetMeasuredHeight()) / 2;
                        break;
                }

                Mat content_roi(border_roi, Rect(content_x, content_y,
                    content->GetMeasuredWidth(), content->GetMeasuredHeight()));
                DrawContent(content_roi);
            }
        }
    }

    void Border::DrawBackground(cv::Mat& border_roi){
        background->Draw(border_roi);
    }

    void Border::DrawContent(cv::Mat& content_roi){
        content->Draw(content_roi);
    }

    void Border::Measure(int desired_width, int desired_height){
        this->Marginable::GetFreeSpace(desired_width, desired_height);
        if(width != WRAP_CONTENT && width != FILL_PARENT)
            control_border_width = min(control_border_width, width);
        if(height != WRAP_CONTENT && height != FILL_PARENT)
            control_border_height = min(control_border_height, height);
        this->Paddingable::GetFreeSpace(control_border_width, control_border_height);
        if(!content_space_width || !content_space_height){  //no space
            measured_width = desired_width;
            measured_height = desired_height;
            if(content) content->Measure(0, 0);
            return;
        }

        int content_width = 0, content_height = 0;
        if(content){
            content->Measure(content_space_width, content_space_height);
            content_width = content->GetMeasuredWidth();
            content_height = content->GetMeasuredHeight();
        }

        if(width == FILL_PARENT)
            measured_width = desired_width;
        else if(width == WRAP_CONTENT){
            content_space_width = content_width;
            control_border_width = content_space_width + padding[0] + padding[2];
            measured_width = control_border_width + margin[0] + margin[2];
        }
        else measured_width = control_border_width + margin[0] + margin[2];

        if(height == FILL_PARENT)
            measured_height = desired_height;
        else if(height == WRAP_CONTENT){
            content_space_height = content_height;
            control_border_height = content_space_height + padding[1] + padding[3];
            measured_height = control_border_height + margin[1] + margin[3];
        }
        else measured_height = control_border_height + margin[1] + margin[3];
    }

    void Border::OnMouse(const MouseState& new_state, const MouseState& old_state){
        if(content) content->OnMouse(new_state, old_state);
        this->VisualElement::OnMouse(new_state, old_state);
    }

    VisualElementType Border::getType() const{
        return VisualElementType::Border;
    }

}