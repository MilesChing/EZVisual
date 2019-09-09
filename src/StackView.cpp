#include "EZVisual/StackView.h"

namespace EZVisual{

    void StackView::Draw(cv::Mat& target){
        if(target.rows < height || target.cols < width)
            throw "Draw() need more space.";
        int this_width = width - margin[0] - margin[2];
        int this_height = height - margin[1] - margin[3];
        Mat roi_border(target,
            Rect(margin[0], margin[1],
                this_width, this_height));
        background.Cover(roi_border);

        if(orientation == Vertical){
            int content_y = margin[1] + padding[1];
            for(auto child : children){
                int content_x = 0;
                if(child->GetHorizontalAlignment() == Left)
                    content_x = margin[0] + padding[0];
                else if(child->GetHorizontalAlignment() == Right)
                    content_x = margin[0] + this_width -
                        padding[2] - child->GetWidth();
                else content_x = margin[0] + padding[0] +
                        (this_width - padding[0] - padding[2] -
                        child->GetWidth())/2;
                Mat roi_content(roi_border,
                        Rect(content_x, content_y,
                        child->GetWidth(), child->GetHeight()));
                child->Draw(roi_content);
                content_y += child->GetHeight();
            }
        }
        else{
            int content_x = margin[0] + padding[0];
            for(auto child : children){
                int content_y = 0;
                if(child->GetVerticalAlignment() == Top)
                    content_y = margin[1] + padding[1];
                else if(child->GetVerticalAlignment() == Bottom)
                    content_y = margin[1] + this_height -
                        padding[3] - child->GetHeight();
                else content_y = margin[1] + padding[1] +
                        (this_height - padding[1] -
                        padding[3] - child->GetHeight())/2;
                Mat roi_content(roi_border,
                        Rect(content_x, content_y,
                        child->GetWidth(), child->GetHeight()));
                child->Draw(roi_content);
                content_x += child->GetWidth();
            }
        }

        need_redraw = false;
    }

    void StackView::Measure(){
        width = height = 0;
        for(auto child : children){
            child->Measure();
            if(orientation == Horizontal){
                height = max(height, child->GetHeight());
                width += child->GetWidth();
            }
            else{
                width = max(width, child->GetWidth());
                height += child->GetHeight();
            }
        }

        width += padding[0] + padding[2];
        height += padding[1] + padding[3];

        width = max(min_width, width);
        height = max(min_height, height);

        width += margin[0] + margin[2];
        height += margin[1] + margin[3];
    }

    VisualElementType StackView::getType() const{
        return VisualElementType::TYPE_STACK_VIEW;
    }

    void StackView::SetByJSON(rapidjson::Value& json_value){
        this->Backgroundable::SetByJSON(json_value);
        this->MinWidthable::SetByJSON(json_value);
        this->MinHeightable::SetByJSON(json_value);
        this->Marginable::SetByJSON(json_value);
        this->Paddingable::SetByJSON(json_value);
        this->Childrenable::SetByJSON(json_value);
        this->Orientationable::SetByJSON(json_value);
    }

    bool StackView::NeedRedraw() const{
        if(need_redraw) return true;
        for(auto child : children) if(child->NeedRedraw()) return true;
        return false;
    }

    StackView::~StackView(){
    }

    void StackView::RegistId(map<int, VisualElement*>& controls){
        controls.insert(make_pair(id, this));
        for(auto child : children) child->RegistId(controls);
    }

}