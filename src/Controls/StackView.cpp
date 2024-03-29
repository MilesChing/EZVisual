#include "EZVisual/Controls/StackView.h"

namespace EZVisual{

    StackView::StackView(rapidjson::Value& json) :
        Backgroundable(json),
        Marginable(json),
        Paddingable(json),
        Childrenable(json),
        Orientationable(json),
        VisualElement(json){}

    void StackView::Draw(cv::Mat& target){
        if(measured_height == 0 || measured_width == 0) return;

        if(target.rows < measured_height || target.cols < measured_width)
            throw "StackView::Draw() need more space.";

        if(control_border_width > 0 && control_border_height > 0){
            Mat border_roi(target, Rect(margin[0], margin[1],
                control_border_width, control_border_height));
            background->Draw(border_roi);
            UpdateGlobalXY(border_roi);

            if(content_space_height == 0 || content_space_width == 0) return;

            Mat content_roi(border_roi, Rect(padding[0], padding[1],
                content_space_width, content_space_height));
            int child_x = 0, child_y = 0;

            if(orientation == Orientation::Vertical){
                for(auto child : children){
                    if(child->GetHorizontalAlignment() == HorizontalAlignment::Left) child_x = 0;
                    else if(child->GetHorizontalAlignment() == HorizontalAlignment::Right)
                        child_x = content_space_width - child->GetMeasuredWidth();
                    else child_x = (content_space_width - child->GetMeasuredWidth()) / 2;
                    Mat child_roi(content_roi, Rect(child_x, child_y,
                            child->GetMeasuredWidth(), child->GetMeasuredHeight()));
                    child->Draw(child_roi);
                    child_y += child->GetMeasuredHeight();
                }
            }
            else{
                for(auto child : children){
                    if(child->GetVerticalAlignment() == VerticalAlignment::Top) child_y = 0;
                    else if(child->GetVerticalAlignment() == VerticalAlignment::Bottom)
                        child_y = content_space_height - child->GetMeasuredHeight();
                    else child_y = (content_space_height - child->GetMeasuredHeight()) / 2;
                    Mat child_roi(content_roi, Rect(child_x, child_y,
                            child->GetMeasuredWidth(), child->GetMeasuredHeight()));
                    child->Draw(child_roi);
                    child_x += child->GetMeasuredWidth();
                }
            }
        }
    }

    void StackView::Measure(int desired_width, int desired_height){
        this->Marginable::GetFreeSpace(desired_width, desired_height);
        if(width != WRAP_CONTENT && width != FILL_PARENT)
            control_border_width = min(control_border_width, width);
        if(height != WRAP_CONTENT && height != FILL_PARENT)
            control_border_height = min(control_border_height, height);
        this->Paddingable::GetFreeSpace(control_border_width, control_border_height);
        if(!content_space_width || !content_space_height){  //no space
            measured_width = desired_width;
            measured_height = desired_height;
            for(auto& child : children)
                if(child) child->Measure(0, 0);
            return;
        }

        int children_width = 0, children_height = 0;
        for(auto child : children){
            if(orientation == Orientation::Horizontal){
                if(children_width < content_space_width)
                    child->Measure(content_space_width - children_width, content_space_height);
                else child->Measure(0, 0);
                children_height = max(children_height, child->GetMeasuredHeight());
                children_width += child->GetMeasuredWidth();
            }
            else{
                if(children_height < content_space_height)
                    child->Measure(content_space_width, content_space_height - children_height);
                else child->Measure(0, 0);
                children_width = max(children_width, child->GetMeasuredWidth());
                children_height += child->GetMeasuredHeight();
            }
        }

        if(width == FILL_PARENT)
            measured_width = desired_width;
        else if(width == WRAP_CONTENT){
            content_space_width = children_width;
            control_border_width = content_space_width + padding[0] + padding[2];
            measured_width = control_border_width + margin[0] + margin[2];
        }
        else measured_width = control_border_width + margin[0] + margin[2];

        if(height == FILL_PARENT)
            measured_height = desired_height;
        else if(height == WRAP_CONTENT){
            content_space_height = children_height;
            control_border_height = content_space_height + padding[1] + padding[3];
            measured_height = control_border_height + margin[1] + margin[3];
        }
        else measured_height = control_border_height + margin[1] + margin[3];
    }

    void StackView::OnMouse(const MouseState& new_state, const MouseState& old_state){
        for(auto& child : children)
            if(child) child->OnMouse(new_state, old_state);
        this->VisualElement::OnMouse(new_state, old_state);
    }

    VisualElementType StackView::getType() const{
        return VisualElementType::StackView;
    }

}