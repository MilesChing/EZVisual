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
        void Invoke(int target_id, std::function<void(VisualElement*)> operation);
    private:
        std::mutex view_mtx, measure_and_draw_mtx;

        EZVisual::Color background;

        map<int, VisualElement*> controls;
        string title = "EZVisual";
        int fps = 30;
        double scale_x = 1, scale_y = 1;
        VisualElement* visual_tree_root = NULL;
        cv::Mat view;
    };

#endif

}