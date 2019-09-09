#include "EZVisual/AutoWrapStack.h"

namespace EZVisual{

    void AutoWrapStack::Draw(cv::Mat& target){
        cv::Mat roi_this(target, Rect(
            margin[0], margin[1],
            width - margin[0] - margin[2],
            height - margin[1] - margin[3]
        ));

        background.Cover(roi_this);

        for(int i = 0; i < children.size(); ++i){
            cv::Mat t(target, Rect(
                children_origins[i].first,
                children_origins[i].second,
                children[i]->GetWidth(),
                children[i]->GetHeight()
            ));

            children[i]->Draw(t);
        }

        need_redraw = false;
    }

    void AutoWrapStack::Measure(){
        if(orientation == Horizontal){
            int current_row_top = margin[1] + padding[1];
            int current_row_bottom = current_row_top;
            int current_x_start = margin[0] + padding[0];
            for(int i = 0; i < children.size(); ++i){
                children[i]->Measure();
                if(current_x_start + padding[2] - margin[0] > wrap_length){
                    current_row_top = current_row_bottom;
                    width = max(width, current_x_start + padding[2] + margin[2]);
                    current_x_start = margin[0] + padding[0] + children[i]->GetWidth();
                    current_row_bottom = current_row_top + children[i]->GetHeight();
                }
                else{
                    current_row_bottom = max(current_row_bottom,
                        current_row_top + children[i]->GetHeight());
                    current_x_start += children[i]->GetWidth();
                }
                children_origins.push_back(make_pair(
                    current_x_start - children[i]->GetWidth(),
                    current_row_top
                ));
            }

            width = max(width, current_x_start + padding[2] + margin[2]);
            height = current_row_bottom + margin[3] + padding[3];
        }
        else{
            int current_row_left = margin[0] + padding[0];
            int current_row_right = current_row_left;
            int current_y_start = margin[1] + padding[1];
            for(int i = 0; i < children.size(); ++i){
                children[i]->Measure();
                if(current_y_start + padding[3] - margin[1] > wrap_length){
                    current_row_left = current_row_right;
                    height = max(height, current_y_start + padding[3] + margin[3]);
                    current_y_start = margin[1] + padding[1] + children[i]->GetHeight();
                    current_row_right = current_row_left + children[i]->GetWidth();
                }
                else{
                    current_row_right = max(current_row_right,
                        current_row_left + children[i]->GetWidth());
                    current_y_start += children[i]->GetHeight();
                }
                children_origins.push_back(make_pair(
                    current_row_left,
                    current_y_start - children[i]->GetHeight()
                ));
            }

            height = max(height, current_y_start + padding[3] + margin[3]);
            width = current_row_right + margin[2] + padding[2];
        }
    }

    VisualElementType AutoWrapStack::getType() const{
        return TYPE_AUTO_WRAP_STACK;
    }

    bool AutoWrapStack::NeedRedraw() const{
        if(need_redraw) return true;
        for(auto child : children)
            if(child->NeedRedraw())
                return true;
        return false;
    }

    void AutoWrapStack::SetByJSON(rapidjson::Value& json_value){
        this->Backgroundable::SetByJSON(json_value);
        this->MinWidthable::SetByJSON(json_value);
        this->MinHeightable::SetByJSON(json_value);
        this->Marginable::SetByJSON(json_value);
        this->Paddingable::SetByJSON(json_value);
        this->Childrenable::SetByJSON(json_value);
        this->Orientationable::SetByJSON(json_value);

        if(json_value["WrapLength"].IsInt())
            wrap_length = json_value["WrapLength"].GetInt();
    }

    void AutoWrapStack::RegistId(map<int, VisualElement*>& controls){
        controls.insert(make_pair(id, this));
        for(auto child : children) child->RegistId(controls);
    }

    void AutoWrapStack::SetWrapLength(int length){
        wrap_length = length;
        need_redraw = true;
    }

}