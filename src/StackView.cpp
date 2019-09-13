#include "EZVisual/Controls/StackView.h"

namespace EZVisual{

    StackView::StackView(rapidjson::Value& json) :
        Backgroundable(json),
        Marginable(json),
        Paddingable(json),
        Childrenable(json),
        Orientationable(json),
        VisualElement(json){}

    void StackView::Draw(cv::Mat& target) const{
        if(measured_height == 0 || measured_width == 0) return;

        if(target.rows < measured_height || target.cols < measured_width)
            throw "StackView::Draw() need more space.";
        int this_width = measured_width - margin[0] - margin[2];
        int this_height = measured_height - margin[1] - margin[3];

        if(this_width > 0 && this_height > 0){
            Mat roi_border(target,
                Rect(margin[0], margin[1],
                    this_width, this_height));
            background.Cover(roi_border);

            if(this_width <= padding[0] + padding[2] ||
                this_height <= padding[1] + padding[3])
                return;

            if(orientation == Vertical){
                int content_y = margin[1] + padding[1];
                for(auto child : children){
                    int content_x = 0;
                    if(child->GetHorizontalAlignment() == Left)
                        content_x = margin[0] + padding[0];
                    else if(child->GetHorizontalAlignment() == Right)
                        content_x = margin[0] + this_width -
                            padding[2] - child->GetMeasuredWidth();
                    else content_x = margin[0] + padding[0] +
                            (this_width - padding[0] - padding[2] -
                            child->GetMeasuredWidth())/2;
                    Mat roi_content(roi_border,
                            Rect(content_x, content_y,
                            child->GetMeasuredWidth(), child->GetMeasuredHeight()));
                    child->Draw(roi_content);
                    content_y += child->GetMeasuredHeight();
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
                            padding[3] - child->GetMeasuredHeight();
                    else content_y = margin[1] + padding[1] +
                            (this_height - padding[1] -
                            padding[3] - child->GetMeasuredHeight())/2;
                    Mat roi_content(roi_border,
                            Rect(content_x, content_y,
                            child->GetMeasuredWidth(), child->GetMeasuredHeight()));
                    child->Draw(roi_content);
                    content_x += child->GetMeasuredWidth();
                }
            }
        }
    }

    void StackView::Measure(int desired_width, int desired_height){
        bool no_space = false;

        int content_desired_width = desired_width - margin[0]
                - margin[2] - padding[0] - padding[2];

        int content_desired_height = desired_height - margin[1]
            - margin[3] - padding[1] - padding[3];

        if(width != WRAP_CONTENT && width != FILL_PARENT)
            content_desired_width = min(content_desired_width,
                width - padding[0] - padding[2]);

        if(height != WRAP_CONTENT && height != FILL_PARENT)
            content_desired_height = min(content_desired_height,
                height - padding[1] - padding[3]);

        if(content_desired_width <= 0 || content_desired_height <= 0)
            no_space = true;
        if(no_space) content_desired_width = content_desired_height = 0;

        int children_width = 0, children_height = 0;
        for(auto child : children){
            if(orientation == Horizontal){
                if(children_width < content_desired_width)
                    child->Measure(content_desired_width - children_width,
                        content_desired_height);
                else child->Measure(0, 0);
                children_height = max(children_height, child->GetMeasuredHeight());
                children_width += child->GetMeasuredWidth();
            }
            else{
                if(children_height < content_desired_height)
                    child->Measure(content_desired_width,
                        content_desired_height - children_height);
                else child->Measure(0, 0);

                children_width = max(children_width, child->GetMeasuredWidth());
                children_height += child->GetMeasuredHeight();
            }
        }

        if(no_space)
            measured_width = desired_width;
        else if(width == WRAP_CONTENT)
            measured_width = children_width + margin[0] +
                margin[2] + padding[0] + padding[2];
        else if(width == FILL_PARENT)
            measured_width = desired_width;
        else measured_width = content_desired_width + padding[0] + padding[2];

        if(no_space)
            measured_height = desired_height;
        else if(height == WRAP_CONTENT)
            measured_height = children_height + margin[1] + margin[3] + padding[1] + padding[3];
        else if(height == FILL_PARENT)
            measured_height = desired_height;
        else measured_height = content_desired_height + padding[1] + padding[3];

    }

    VisualElementType StackView::getType() const{
        return VisualElementType::TYPE_STACK_VIEW;
    }

    StackView::~StackView(){
    }


}