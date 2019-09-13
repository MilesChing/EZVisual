#include "EZVisual/Controls/PlainText.h"

namespace EZVisual{

    PlainText::PlainText(rapidjson::Value& json) :
        Textable(json),
        Marginable(json),
        VisualElement(json){}

    void PlainText::Draw(cv::Mat& target) const{
        if(measured_height == 0 || measured_width == 0) return;

        cv::Point origin;

        int base_height;

        auto size = cv::getTextSize(
            text,
            font_family,
            font_size,
            font_weight,
            &base_height
        );

        origin.x = 0;
        origin.y = size.height;

        cv::Mat tmp_mat = cv::Mat::zeros(size.height + base_height,
            size.width, CV_8UC3);
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
            measured_width - margin[0] - margin[2],
            measured_height - margin[1] - margin[3]));

        for(int i = 0; i < tmp_mat.rows; ++i)
            for(int j = 0; j < tmp_mat.cols; ++j)
                if(tmp_mat.at<cv::Vec3b>(i, j)[0] != 0)
                    font_color.Cover(content_roi.at<cv::Vec3b>(margin[1] + i, margin[0] + j));
    }

    void PlainText::Measure(int desired_width, int desired_height){
        int content_desired_width = desired_width - margin[0] - margin[2];

        int content_desired_height = desired_height - margin[1] - margin[3];

        if(width != WRAP_CONTENT && width != FILL_PARENT)
            content_desired_width = min(content_desired_width, width);

        if(height != WRAP_CONTENT && height != FILL_PARENT)
            content_desired_height = min(content_desired_height, height);

        content_desired_width = max(content_desired_width, 0);
        content_desired_height = max(content_desired_height, 0);


        auto size = cv::getTextSize(
            text,
            font_family,
            font_size,
            font_weight,
            &base_line_height
        );

        if(content_desired_width == 0)
            measured_width = desired_width;
        else if(width == WRAP_CONTENT)
            measured_width = min(content_desired_width, size.width)
                + margin[0] + margin[2];
        else if(width == FILL_PARENT)
            measured_width = content_desired_width;
        else measured_width = width + margin[0] + margin[2];

        if(content_desired_height == 0)
            measured_height = desired_height;
        else if(height == WRAP_CONTENT)
            measured_height = min(content_desired_height, size.height + base_line_height)
                + margin[1] + margin[3];
        else if(height == FILL_PARENT)
            measured_height = content_desired_height;
        else measured_height = height + margin[1] + margin[3];
    }

    VisualElementType PlainText::getType() const{
        return TYPE_PLAIN_TEXT;
    }

}