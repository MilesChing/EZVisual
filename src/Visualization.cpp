#include "EZVisual/Visualization.h"
#include "EZVisual/Tools/StringConverter.hpp"
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
            if(doc["Background"].IsNull())
                background = SolidColorBrush::CreateInstance(0xffffffff);
            else background = Brush::CreateInstance(doc["Background"]);
        }

        Value& layout = doc["Layout"];
        if(layout.IsNull()) throw "No layout found.";
        else visual_tree_root = VisualElement::CreateInstance(layout);
    }

    Visualization::~Visualization(){
        if(visual_tree_root) delete visual_tree_root;
        if(background) delete background;
    }

    void Visualization::OnMouse(int event,int x,int y,int flags,void *ustc){
        Visualization* tis = (Visualization*)ustc;
        tis->user_input = 200;
        tis->mouse_event_param.relative_x = x;
        tis->mouse_event_param.relative_y = y;
        switch (event){
            case CV_EVENT_MOUSEMOVE:
                tis->mouse_event_param.current_event_type =
                    MouseEventType::MouseMoving; break;
            case CV_EVENT_LBUTTONDOWN:
                tis->mouse_event_param.current_event_type =
                    MouseEventType::MouseLeftPressed; break;
            case CV_EVENT_LBUTTONUP:
                tis->mouse_event_param.current_event_type =
                    MouseEventType::MouseLeftReleased; break;
            case CV_EVENT_RBUTTONDOWN:
                tis->mouse_event_param.current_event_type =
                    MouseEventType::MouseRightPressed; break;
            case CV_EVENT_RBUTTONUP:
                tis->mouse_event_param.current_event_type =
                    MouseEventType::MouseRightReleased; break;
            default: return;
        }
        tis->visual_tree_root->CheckMouseEvent(tis->mouse_event_param);
    }

    void Visualization::LaunchWindow(){
        try{
            cv::namedWindow(title, CV_WINDOW_AUTOSIZE);
            int interval_ms_big = 1000 / fps;
            int interval_ms_small = 5;
            cv::setMouseCallback(title, OnMouse, this);
            while(true){
                visual_tree_root->Measure(VERY_BIG_INT, VERY_BIG_INT);
                if(view.rows != visual_tree_root->GetMeasuredHeight() ||
                    view.cols != visual_tree_root->GetMeasuredWidth()){
                    view = Mat::zeros(visual_tree_root->GetMeasuredHeight(),
                            visual_tree_root->GetMeasuredWidth(), CV_8UC3);
                }
                background->Draw(view);
                visual_tree_root->Draw(view);
                if(scale_x != 1.0 || scale_y != 1.0)
                    cv::resize(view, view, cv::Size(0, 0),
                        scale_x, scale_y, CV_INTER_LANCZOS4);
                cv::imshow(title, view);
                if(!user_input){
                    if(cv::waitKey(interval_ms_big) == 27) break;
                }
                else{
                    if(cv::waitKey(interval_ms_small) == 27) break;
                    --user_input;
                }
            }
            cv::destroyWindow(title);
        }
        catch(const char* s){
            cerr << s << endl;
        }
        catch(string s){
            cerr << s << endl;
        }
    }

}