/* Demo of EZVisual
 * This demo is a blackboard application where you can switch colors or paint with a mouse.
 */
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

EZVisual::Border* borders[4];
EZVisual::Canvas* canvas;
int current_index = 0;
EZVisual::Color current_color;
bool drawing = false;
bool first_point = true;
pair<int, int> current_point;

//Check this path if you get a "file not exist" exception.
string visual_profile_path = "../demo/EZVisual_Demo.json";

int main(){
    /*
    //Create visualization object
    Visualization vis(visual_profile_path);
    //Launch up a window
    thread t(&Visualization::LaunchWindow, &vis);
    vis.Invoke([&](Visualization* visualization){
        for(int i = 0; i < 4; ++i){
            //Store Border in borders
            //You could only store pointers to visual elements outside function "Invoke"
            //Modifing outside is not permitted
            borders[i] = visualization->GetVisualElement<Border>(i + 10);

            //Register listeners
            borders[i]->MouseLeftPressed += [&](const EZVisual::MouseEventParameter& param){
                //Don't use i here
                if(current_index == param.sender->GetId() - 10) return;
                //We need another Invoke because these codes are in a listener
                //Thess invoking won't cause deadlock
                //Use vis not visualization here
                vis.Invoke([&](Visualization* visualization){
                    Border* target = visualization->GetVisualElement<Border>(current_index);
                    target->SetBackground(0);
                });
                current_index = param.sender->GetId() - 10;
                //Update the color of the selected border
                vis.Invoke([&](Visualization* visualization){
                    Border* target = visualization->GetVisualElement<Border>(current_index);
                    target->SetBackground(0xffffffff);
                    target = visualization->GetVisualElement<Border>(current_index + 10);
                    current_color = target->GetBackground();
                });
            };
        }

        //Register listener for canvas
        canvas = visualization->GetVisualElement<Canvas>(16);

        //Set drawing mode when left button pushed.
        canvas->MouseLeftPressed += [&](const EZVisual::MouseEventParameter& param){
            drawing = true;
            first_point = true;
        };
        //Set drawing mode when left button released.
        canvas->MouseLeftReleased += [&](const EZVisual::MouseEventParameter& param){
            drawing = false;
            first_point = false;
        };
        //Set drawing mode when pointer leaved.
        canvas->MouseLeaved += [&](const EZVisual::MouseEventParameter& param){
            drawing = false;
            first_point = false;
        };

        //Draw points
        canvas->MouseMoving += [&](const EZVisual::MouseEventParameter& param){
            if(!drawing) return;
            if(first_point){
                //At the first point after pointer down, draw a circle.
                vis.Invoke([&](Visualization* visualization){
                    canvas->PaintCircle(make_pair(param.relative_x, param.relative_y),
                        2, current_color, 0, 0, 0);
                });
                first_point = false;
            }
            else{
                //At other points, draw line segments.
                vis.Invoke([&](Visualization* visualization){
                    canvas->PaintLine(make_pair(param.relative_x, param.relative_y),
                        current_point, current_color, 0, 2.0);
                });
            }
            current_point = make_pair(param.relative_x, param.relative_y);
        };
    });

    //Window will be waiting for key 27 by default
    t.join();
    */
    return 0;
}