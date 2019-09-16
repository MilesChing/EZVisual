#include "EZVisual/Visualization.h"
#include <unistd.h>
using namespace cv;
namespace EZVisual{

    const int VERY_BIG_INT = 1000;

    Visualization::Visualization(string visual_config){
        fstream input(visual_config, ios::in);
        if(!input.is_open()) throw "Open visual config failed: file not exist.";
        stringstream buffer;
        Document doc;
        buffer << input.rdbuf();
        doc.Parse(buffer.str().c_str());

        if(!doc["Title"].IsNull())
            title = doc["Title"].GetString();

        if(!doc["FPS"].IsNull())
            fps = doc["FPS"].GetInt();

        if(!doc["ScaleX"].IsNull())
            scale_x = doc["ScaleX"].GetDouble();

        if(!doc["ScaleY"].IsNull())
            scale_y = doc["ScaleY"].GetDouble();

        if(doc["Background"].IsString()){
            background = EZVisual::Color(doc["Background"].GetString());
        }

        Value& layout = doc["Layout"];
        if(layout.IsNull()) throw "No layout found.";
        else{
            VisualElementType type;
            Convert(layout["Type"].GetString(), type);
            visual_tree_root = GetVisualElementFromType(type, layout);
        }
    }

    Visualization::~Visualization(){
        if(visual_tree_root) delete visual_tree_root;
    }

    void Visualization::OnMouse(int event,int x,int y,int flags,void *ustc){
        Visualization* tis = (Visualization*)ustc;
        MouseEventParameter param;
        param.relative_x = x;
        param.relative_y = y;
        switch (event){
            case CV_EVENT_MOUSEMOVE: param.current_event_type = MouseMoving; break;
            case CV_EVENT_LBUTTONDOWN: param.current_event_type = MouseLeftDown; break;
            case CV_EVENT_LBUTTONUP: param.current_event_type = MouseLeftUp; break;
            case CV_EVENT_RBUTTONDOWN: param.current_event_type = MouseRightDown; break;
            case CV_EVENT_RBUTTONUP: param.current_event_type = MouseRightUp; break;
            default: return;
        }
        tis->visual_tree_root->CheckMouseEvent(param);
    }

    void Visualization::LaunchWindow(){
        cv::namedWindow(title, CV_WINDOW_AUTOSIZE);
        int interval_ms = 1000 / fps;
        cv::setMouseCallback(title, OnMouse, this);
        while(true){
            {
                std::unique_lock<std::mutex> lck_measure_and_draw(measure_and_draw_mtx);
                visual_tree_root->Measure(VERY_BIG_INT, VERY_BIG_INT);
                std::unique_lock<std::mutex> lck_view(view_mtx);
                if(view.rows != visual_tree_root->GetMeasuredHeight() ||
                    view.cols != visual_tree_root->GetMeasuredWidth()){
                    view = Mat::zeros(visual_tree_root->GetMeasuredHeight(),
                            visual_tree_root->GetMeasuredWidth(), CV_8UC3);
                }
                background.Cover(view);
                visual_tree_root->Draw(view);
                cv::resize(view, view, cv::Size(0, 0), scale_x, scale_y, CV_INTER_LANCZOS4);
            }
            cv::imshow(title, view);
            if(cv::waitKey(interval_ms) == 27) break;
        }
        cv::destroyWindow(title);
    }

}