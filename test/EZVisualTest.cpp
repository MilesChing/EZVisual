#include <iostream>
#include <string>
#include <thread>
#include "EZVisual/Border.h"
#include "EZVisual/Visualization.h"
#include "opencv2/opencv.hpp"
#include "unistd.h"
using namespace std;
using namespace rapidjson;
using namespace EZVisual;
#define debug(a) cerr<<#a<<" = "<<a<<endl

int main(){
    try{
        Visualization vis("/home/milesching/workspace/EZVisual/test/test_visual_config.json");
        thread t(&Visualization::LaunchWindow, &vis);
        unsigned int k = 0;
        while(k += 255){
            usleep(10000);
            vis.Invoke(15, [k](VisualElement* element){
                element->SetBackground(k);
            });
        }
        t.join();
    }
    catch(const char* s){
        cout << s;
    }
    return 0;
}