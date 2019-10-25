#pragma once
#include "EZVisual/Interfaces/VisualElement.h"
#include "EZVisual/Core.h"
#include "EZVisual/Brushes.h"
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>
using namespace std;
using namespace cv;
namespace EZVisual{

    class Visualization{
    public:
        Visualization(string visual_config);
        ~Visualization();

        /**@brief Show a window with a content configured by visual_config.
         *
         * Show a window with a content configured by visual_config. The function will keep running until a specific key (default is 'Esc') is pressed and it have to destroy the window. So in many applications you'll need to run this function on a single thread.
         */
        void LaunchWindow();

        /**@brief Get specific visual element 't' using target_id.
         *
         * Get specific visual element 't' using target_id. Ensure the desired type is exactly correct when calling this, or you may get a std::bad_cast exception.
         *
         * @param target_id Id of the target visual element.
         * @param T Desired type of the target visual element.
         */
        template<typename T> T* GetVisualElement(int target_id){
            auto it = controls_table.find(target_id);
            VisualElement* res = NULL;
            if(it == controls_table.end()){
                res = visual_tree_root->SearchElementById(target_id);
                if(res) controls_table[target_id] = res;
            }
            else res = it->second;
            if(!res) throw "Id not found.";
            else return dynamic_cast<T*>(res);
        }

        /**@brief Invoke a function on the UI.
         *
         * Do an action on the UI. UI tasks including drawing and measuring runs on a seperate thread and shouldn't be modified freely. The only way to update attributes and preferences of visual elements is to invoke a function by calling this.
         *
         * @param operation Function to be invoked.
         * @warning Don't call Invoke recursively in "operation". It will cause a dead lock.
         */
        void Invoke(const function<void(Visualization*)>& operation);

    private:
        std::mutex view_mtx, measure_and_draw_mtx;

        EZVisual::Color background;

        string title = "EZVisual";
        int fps = 30;
        double scale_x = 1, scale_y = 1;
        VisualElement* visual_tree_root = NULL;
        cv::Mat view;
        unordered_map<int, VisualElement*> controls_table;

        //Mouse Event Handler
        bool buttons[3];
        time_t buttons_down_time[3];
        MouseEventParameter mouse_event_param;

        static void OnMouse(int event,int x,int y,int flags,void* visualization);
    };

}