#include "EZVisual/Controls/PlainText.h"

namespace EZVisual{

    PlainText::PlainText(rapidjson::Value& json) :
        Textable(json),
        Marginable(json),
        VisualElement(json){}

    void PlainText::Draw(cv::Mat& target){
        if(!measured_height || !measured_width ||
            !control_border_width || !control_border_height) return;

        static cv::Point origin;
        origin.x = 0;
        origin.y = text_height;

        static cv::Mat tmp_mat;
        if(tmp_mat.rows != text_height + text_base_line || tmp_mat.cols != text_width)
            tmp_mat = cv::Mat::zeros(text_height + text_base_line, text_width, CV_8UC3);
        tmp_mat = cv::Scalar(0, 0, 0);

        cv::putText(
            tmp_mat,
            text,
            origin,
            font_family,
            font_size,
            cv::Scalar(255, 255, 255),
            font_weight
        );

        cv::Mat content_roi(target, Rect(margin[0], margin[1],
            control_border_width, control_border_height));
        UpdateGlobalXY(content_roi);
        for(int i = 0; i < tmp_mat.rows; ++i)
            for(int j = 0; j < tmp_mat.cols; ++j)
                if(tmp_mat.at<cv::Vec3b>(i, j)[0] != 0)
                    font_color.Cover(content_roi.at<cv::Vec3b>(i, j));
    }

    void PlainText::Measure(int desired_width, int desired_height){
        this->Marginable::GetFreeSpace(desired_width, desired_height);
        if(width != FILL_PARENT && width != WRAP_CONTENT)
            control_border_width = min(control_border_width, width);
        if(height != FILL_PARENT && height != WRAP_CONTENT)
            control_border_height = min(control_border_height, height);
        if(!control_border_width || !control_border_height){  //no space
            measured_width = desired_width;
            measured_height = desired_height;
            return;
        }

        MeasureText();

        if(width == FILL_PARENT) measured_width = desired_width;
        else if(width == WRAP_CONTENT){
            control_border_width = min(control_border_width, text_width);
            measured_width = control_border_width + margin[0] + margin[2];
        }
        else measured_width = control_border_width + margin[0] + margin[2];

        if(height == FILL_PARENT) measured_height = desired_height;
        else if(height == WRAP_CONTENT){
            control_border_height = min(
                control_border_height,
                text_height + text_base_line
            );
            measured_height = control_border_height + margin[1] + margin[3];
        }
        else measured_height = control_border_height + margin[1] + margin[3];
    }

    VisualElementType PlainText::getType() const{
        return VisualElementType::PlainText;
    }

}