#include <iostream>
#include <string>
#include <thread>
#include "EZVisual/Border.h"
#include "EZVisual/Visualization.h"
#include "EZVisual/Canvas.h"
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
            vis.Invoke<Canvas>(15, [i](Canvas* text){
                cv::Mat mat = cv::Mat::zeros(50, 50, CV_8UC3);
                mat = Scalar(0, 0, 200);
                text->ClearLayer(0);
                double theta = i % 360 / 360.0 * 2 * 3.14159;
                int x = 75 + 30 * sin(theta);
                int y = 75 + 30 * cos(theta);
                text->Paint(mat, 0, make_pair(x, y));
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