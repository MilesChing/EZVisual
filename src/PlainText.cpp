#include "EZVisual/PlainText.h"

namespace EZVisual{

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
            cv::Scalar(font_color.B(),
                font_color.G(),
                font_color.R()),
            font_weight
        );

        need_redraw = false;
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

    void PlainText::SetByJSON(rapidjson::Value& json_value){
        this->Textable::SetByJSON(json_value);
        this->Marginable::SetByJSON(json_value);
    }

    bool PlainText::NeedRedraw() const{
        return need_redraw;
    }

    void PlainText::RegistId(map<int, VisualElement*>& controls){
        controls.insert(make_pair(id, this));
    }

}