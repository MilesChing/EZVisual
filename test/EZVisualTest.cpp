#include <iostream>
#include <string>
#include <thread>
#include "EZVisual/Border.h"
#include "EZVisual/Visualization.h"
#include "EZVisual/PlainText.h"
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
        int i = 0;
        while(++i){
            usleep(100000);
            vis.Invoke<PlainText>(15, [i](PlainText* text){
                text->SetText(to_string(i).c_str());
            });
        }
    }
    catch(string s){
        cout << s;
    }
    catch(const char* s){
        cout << s;
    }
    catch(double s){
        cout << s;
    }
    return 0;
}