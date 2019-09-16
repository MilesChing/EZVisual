#include <iostream>
#include <string>
#include <thread>
#include "EZVisual/EZVisual.h"
#include "opencv2/opencv.hpp"
#include "unistd.h"
#include <cmath>
using namespace std;
using namespace rapidjson;
using namespace EZVisual;
using namespace cv;
#define debug(a) cerr<<#a<<" = "<<a<<endl

int main(){
    try{
        Visualization vis("/home/milesching/workspace/EZVisual/demo/EZVisual_Demo.json");

        thread t(&Visualization::LaunchWindow, &vis);

        bool drawing = false;

        vis.Invoke<EZVisual::Canvas>(16, [&drawing](EZVisual::Canvas* canvas){
            canvas->AddMouseListener(MouseLeftDown, [&drawing](const MouseEventParameter& param){
                drawing = true;
            });
            canvas->AddMouseListener(MouseLeftUp, [&drawing](const MouseEventParameter& param){
                drawing = false;
            });
            canvas->AddMouseListener(MouseMoving, [&drawing, &canvas](const MouseEventParameter& param){
                if(drawing){
                    canvas->PaintPixel(make_pair(param.relative_x, param.relative_y), 0xffffffff);
                }
            });
        });

        t.join();
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