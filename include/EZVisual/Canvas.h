#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "EZVisual/Interfaces/Interfaces.h"
#include <string>
#include <tuple>

using namespace std;
using namespace cv;

namespace EZVisual{
#ifndef _EZVISUAL_CANVAS_
#define _EZVISUAL_CANVAS_
    class Canvas : virtual public Marginable,
                 , virtual public Paddingable
                 , virtual public Backgroundable{
    public:
        Canvas(){}
        ~Canvas(){};

        void Draw(cv::Mat& target);
        void Measure();

        VisualElementType getType() const;

        bool NeedRedraw() const;
        void SetByJSON(rapidjson::Value& json_value);
        void RegistId(map<int, VisualElement*>& controls);

        void SetLayer(int layer_index, const vector<tuple<int, int>>& layer, const Color& layer_color);

        void SetLayer(int layer_index, const vector<int>& layer);

    protected:
        vector<vector<tuple<int, int, int>>> pixels;
    };
#endif
}
