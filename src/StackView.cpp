#include "EZVisual/Controls/StackView.h"

namespace EZVisual{

    StackView::StackView(rapidjson::Value& json) :
        Backgroundable(json),
        MinWidthable(json),
        MinHeightable(json),
        Marginable(json),
        Paddingable(json),
        Childrenable(json),
        Orientationable(json),
        VisualElement(json){}

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

    StackView::~StackView(){
    }


}