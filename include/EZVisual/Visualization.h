#include "EZVisual/Interfaces/VisualElement.h"
#include "EZVisual/Core.h"
#include <string>
#include <map>
#include <thread>
#include <mutex>

using namespace std;
using namespace cv;
namespace EZVisual{

#ifndef _EZVISUAL_VISUALIZATION_
#define _EZVISUAL_VISUALIZATION_

    class Visualization{
    public:
        Visualization(string visual_config);
        ~Visualization();
        void LaunchWindow();

        template<typename T> void Invoke(int target_id, std::function<void(T*)> operation){
            std::unique_lock<std::mutex> lck_measure_and_draw(measure_and_draw_mtx);
            auto p = visual_tree_root->SearchElementById(target_id);
            if(!p) throw "Id not found.";
            else operation(dynamic_cast<T*>(p));
        }
    private:
        std::mutex view_mtx, measure_and_draw_mtx;

        EZVisual::Color background;

        map<int, VisualElement*> controls;
        string title = "EZVisual";
        int fps = 30;
        double scale_x = 1, scale_y = 1;
        VisualElement* visual_tree_root = NULL;
        cv::Mat view;

        //Mouse Event Handler
        bool buttons[3];
        time_t buttons_down_time[3];

        static void OnMouse(int event,int x,int y,int flags,void* visualization);
    };

#endif

}