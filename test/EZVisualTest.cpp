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
        Visualization vis("/home/milesching/workspace/EZVisual/test/test_visual_config.json");

        thread t(&Visualization::LaunchWindow, &vis);
        int i = 0;

        while(++i){
            usleep(10000);
            vis.Invoke<Canvas>(15, [i](Canvas* canvas){
                cv::Mat mat = cv::Mat::zeros(50, 50, CV_8UC3);
                mat = Scalar(0, 0, 200);
                canvas->ClearLayer(0);
                Color c1(i % 255, i % 255, i % 255);
                Color c2(255 - i%255,255 - i%255,255 - i%255);
                canvas->PaintColor(c1);
                canvas->PaintCircle(make_pair(i % 100, i % 100), 100, 0, 0xffff0000, c2, 4);
            });
        }

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