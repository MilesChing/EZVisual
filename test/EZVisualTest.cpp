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

        vis.LaunchWindow();
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