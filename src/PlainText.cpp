#include "EZVisual/PlainText.h"

namespace EZVisual{

    PlainText::PlainText(rapidjson::Value& json) :
        Textable(json),
        Marginable(json),
        VisualElement(json){}

    void PlainText::Draw(cv::Mat& target){
        cv::Point origin;
        origin.x = margin[0];
        origin.y = height - base_line_height + margin[1];

        cv::putText(
            target,
            text,
            origin,
            font_family,
            font_size,
            cv::Scalar(font_color.b,
                font_color.g,
                font_color.r),
            font_weight
        );
    }

    void PlainText::Measure(){
        auto size = cv::getTextSize(
            text,
            font_family,
            font_size,
            font_weight,
            &base_line_height
        );

        width = size.width;
        height = size.height + 2*base_line_height;

        width += margin[0] + margin[2];
        height += margin[1] + margin[3];
    }

    VisualElementType PlainText::getType() const{
        return TYPE_PLAIN_TEXT;
    }

}