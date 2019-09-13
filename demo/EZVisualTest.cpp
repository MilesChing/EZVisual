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
        Visualization vis("EZVisual_Demo.json");

        thread t(&Visualization::LaunchWindow, &vis);

        vis.Invoke<Canvas>(16, [](Canvas* canvas){
            cerr << 0;
            canvas->PaintCircle(make_pair(150, 171.133), 100, 0, 0x33ff0000, 0xff000000, 10);
            canvas->PaintCircle(make_pair(250, 171.133), 100, 0, 0x3300ff00, 0xff000000, 10);
            canvas->PaintCircle(make_pair(200, 257.736), 100, 0, 0x330000ff, 0xff000000, 10);
            cerr << 1;
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