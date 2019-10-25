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

        if(border_width > 0 && border_height > 0){
            Mat border_roi(target,
                Rect(margin[0], margin[1],
                    border_width, border_height));
            background.Cover(border_roi);
            UpdateGlobalXY(border_roi);

            if(content_width > 0 && content_height > 0 && content){
                int content_x = 0, content_y = 0;
                switch (content->GetHorizontalAlignment()){
                    case HorizontalAlignment::Left: content_x = padding[0]; break;
                    case HorizontalAlignment::Right: content_x = border_width - padding[2];
                    case HorizontalAlignment::Center: content_x = (border_width - content_width) / 2;
                }

                switch (content->GetVerticalAlignment()){
                    case VerticalAlignment::Top: content_y = padding[1]; break;
                    case VerticalAlignment::Bottom: content_y = border_height - padding[3];
                    case VerticalAlignment::Center: content_y = (border_height - content_height) / 2;
                }

                Mat content_roi(border_roi, Rect(content_x, content_y, content_width, content_height));
                content->Draw(content_roi);
            }
        }
    }

    void Border::Measure(int desired_width, int desired_height){
        this->Marginable::GetFreeSpace(desired_width, desired_height);
        if(width != WRAP_CONTENT && width != FILL_PARENT) content_width = min(content_width, width);
        if(height != WRAP_CONTENT && height != FILL_PARENT) content_height = min(content_height, height);
        this->Paddingable::GetFreeSpace(content_width, content_height);
        if(content_width == 0 || content_height == 0){
            measured_width = desired_width;
            measured_height = desired_height;
            return;
        }

        if(content){
            content->Measure(content_width, content_height);
            content_width = content->GetMeasuredWidth();
            content_height = content->GetMeasuredHeight();
        }

        if(width == FILL_PARENT) measured_width = desired_width;
        else{
            border_width = content_width + padding[0] + padding[2];
            measured_width = border_width + margin[0] + margin[2];
        }

        if(height == FILL_PARENT) measured_height = desired_height;
        else{
            border_height = content_height + padding[1] + padding[3];
            measured_height = border_height + margin[1] + margin[3];
        }
    }

    bool Border::CheckMouseEvent(const MouseEventParameter& params){
        if(content && content->CheckMouseEvent(params)) return true;
        else return this->VisualElement::CheckMouseEvent(params);
    }

    VisualElementType Border::getType() const{
        return VisualElementType::Border;
    }

}