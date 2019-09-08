#include "EZVisual/Border.h"

namespace EZVisual{

    void Border::Draw(cv::Mat& target){
        if(target.rows < height || target.cols < width)
            throw "Draw() need more space.";
        int border_width = width - margin[0] - margin[2];
        int border_height = height - margin[1] - margin[3];
        Mat roi_border(target,
            Rect(margin[0], margin[1],
                border_width, border_height));
        roi_border = Scalar(background.B(), background.G(), background.R());

        if(content){
            int content_x = 0, content_y = 0;
            if(content->GetHorizontalAlignment() == Left)
                content_x = margin[0] + padding[0];
            else if(content->GetHorizontalAlignment() == Right)
                content_x = margin[0] + border_width - padding[2] - content->GetWidth();
            else content_x = margin[0] + padding[0] +
                (border_width - padding[0] - padding[2] - content->GetWidth())/2;

            if(content->GetVerticalAlignment() == Top)
                content_y = margin[1] + padding[1];
            else if(content->GetVerticalAlignment() == Bottom)
                content_y = margin[1] + border_height - padding[3] - content->GetHeight();
            else content_y = margin[1] + padding[1] +
                (border_height - padding[1] - padding[3] - content->GetHeight())/2;

            Mat roi_content(target,
                Rect(content_x, content_y,
                    content->GetWidth(), content->GetHeight()));
            content->Draw(roi_content);
        }

        need_redraw = false;
    }

    void Border::Measure(){
        if(content){
            content->Measure();
            width = content->GetWidth();
            height = content->GetHeight();
        }
        else width = height = 0;

        width += padding[0] + padding[2];
        height += padding[1] + padding[3];

        width = max(min_width, width);
        height = max(min_height, height);

        width += margin[0] + margin[2];
        height += margin[1] + margin[3];
    }

    VisualElementType Border::getType() const{
       return VisualElementType::TYPE_BORDER;
    }

    void Border::SetByJSON(rapidjson::Value& json_value){
        this->Backgroundable::SetByJSON(json_value);
        this->MinWidthable::SetByJSON(json_value);
        this->MinHeightable::SetByJSON(json_value);
        this->Marginable::SetByJSON(json_value);
        this->Paddingable::SetByJSON(json_value);
        this->Contentable::SetByJSON(json_value);
    }

    bool Border::NeedRedraw() const{
        return need_redraw || (content && content->NeedRedraw());
    }

    void Border::RegistId(map<int, VisualElement*>& controls){
        controls.insert(make_pair(id, this));
        if(content) content->RegistId(controls);
    }

    Border::~Border(){
        if(content) delete content;
    }

}