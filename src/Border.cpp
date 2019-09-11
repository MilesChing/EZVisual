#include "EZVisual/Controls/Border.h"

namespace EZVisual{

    Border::Border(rapidjson::Value& json) :
        Backgroundable(json),
        MinWidthable(json),
        MinHeightable(json),
        Marginable(json),
        Paddingable(json),
        Contentable(json),
        VisualElement(json){}

    void Border::Draw(cv::Mat& target){
        if(target.rows < height || target.cols < width)
            throw "Draw() need more space.";
        int border_width = width - margin[0] - margin[2];
        int border_height = height - margin[1] - margin[3];
        Mat roi_border(target,
            Rect(margin[0], margin[1],
                border_width, border_height));
        background.Cover(roi_border);

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

    Border::~Border(){
        if(content) delete content;
    }

}