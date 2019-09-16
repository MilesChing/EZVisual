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

        int border_width = measured_width - margin[0] - margin[2];
        int border_height = measured_height - margin[1] - margin[3];

        if(border_width > 0 && border_height > 0){
            Mat roi_border(target,
                Rect(margin[0], margin[1],
                    border_width, border_height));

            cv::Point xy;
            cv::Size sz;
            roi_border.locateROI(sz, xy);
            x = xy.x;
            y = xy.y;

            background.Cover(roi_border);

            if(border_width <= padding[0] + padding[2] ||
                border_height <= padding[1] + padding[3])
                return;

            if(content){
                int content_x = 0, content_y = 0;
                if(content->GetHorizontalAlignment() == Left)
                    content_x = margin[0] + padding[0];
                else if(content->GetHorizontalAlignment() == Right)
                    content_x = margin[0] + border_width - padding[2] - content->GetMeasuredWidth();
                else content_x = margin[0] + padding[0] +
                    (border_width - padding[0] - padding[2] - content->GetMeasuredWidth())/2;

                if(content->GetVerticalAlignment() == Top)
                    content_y = margin[1] + padding[1];
                else if(content->GetVerticalAlignment() == Bottom)
                    content_y = margin[1] + border_height - padding[3] - content->GetMeasuredHeight();
                else content_y = margin[1] + padding[1] +
                    (border_height - padding[1] - padding[3] - content->GetMeasuredHeight())/2;

                Mat roi_content(target, Rect(content_x, content_y,
                    content->GetMeasuredWidth(), content->GetMeasuredHeight()));
                content->Draw(roi_content);
            }
        }
    }

    void Border::Measure(int desired_width, int desired_height){

        if(desired_width == 0 || desired_height == 0){
            measured_height = measured_width = 0;
            return;
        }

        int content_width = desired_width - margin[0]
                - margin[2] - padding[0] - padding[2];
        int content_height = desired_height - margin[1]
                - margin[3] - padding[1] - padding[3];
        int real_content_width = 0, real_content_height = 0;
        bool no_space = false;

        if(width != WRAP_CONTENT && width != FILL_PARENT)
            content_width = min(content_width,
                width - padding[0] - padding[2]);

        if(height != WRAP_CONTENT && height != FILL_PARENT)
            content_height = min(content_height,
                height - padding[1] - padding[3]);

        no_space = (content_width <= 0 || content_height <= 0);
        if(no_space) content_height = content_width = 0;

        if(content){
            content->Measure(content_width, content_height);
            real_content_width = content->GetMeasuredWidth();
            real_content_height = content->GetMeasuredHeight();
        }

        if(no_space)
            measured_width = desired_width;
        else if(width == WRAP_CONTENT)
            measured_width = real_content_width + margin[0] + margin[2] +
                padding[0] + padding[2];
        else if(width == FILL_PARENT)
            measured_width = desired_width;
        else measured_width = content_width + padding[0] + padding[2];

        if(no_space)
            measured_height = desired_height;
        else if(height == WRAP_CONTENT)
            measured_height = real_content_height + margin[1] + margin[3] +
                padding[1] + padding[3];
        else if(height == FILL_PARENT)
            measured_height = desired_height;
        else measured_height = content_height + padding[1] + padding[3];
    }

    bool Border::CheckMouseEvent(const MouseEventParameter& params){
        if(content && content->CheckMouseEvent(params)) return true;
        else return this->VisualElement::CheckMouseEvent(params);
    }

    VisualElementType Border::getType() const{
        return VisualElementType::TYPE_BORDER;
    }

    Border::~Border(){
        this->Contentable::DeleteContent();
    }

}