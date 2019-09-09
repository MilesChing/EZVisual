#include "EZVisual/Visualization.h"
#include <unistd.h>
using namespace cv;
namespace EZVisual{

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
            visual_tree_root = GetVisualElementFromType(type);
            visual_tree_root->SetByJSON(layout);
        }

        visual_tree_root->RegistId(controls);
    }

    Visualization::~Visualization(){
        if(visual_tree_root) delete visual_tree_root;
    }

    void Visualization::LaunchWindow(){
        cv::namedWindow(title);
        int interval_ms = 1000 / fps;
        while(1){
            if(visual_tree_root->NeedRedraw()){
                std::unique_lock<std::mutex> lck_measure_and_draw(measure_and_draw_mtx);
                visual_tree_root->Measure();
                std::unique_lock<std::mutex> lck_view(view_mtx);
                if(view.rows != visual_tree_root->GetHeight() ||
                    view.cols != visual_tree_root->GetWidth()){
                    view = Mat::zeros(visual_tree_root->GetHeight(),
                            visual_tree_root->GetWidth(), CV_8UC3);
                }
                background.Cover(view);
                visual_tree_root->Draw(view);
                cv::resize(view, view, Size(0, 0), scale_x, scale_y);
            }
            cv::imshow(title, view);
            if(cv::waitKey(interval_ms) == 27) break;
        }
        cv::destroyWindow(title);
    }

    void Visualization::Invoke(int target_id, std::function<void(VisualElement*)> operation){
        std::unique_lock<std::mutex> lck_measure_and_draw(measure_and_draw_mtx);
        auto p = controls.find(target_id);
        if(p == controls.end()) throw "Id not found.";
        else operation(p->second);
    }

}