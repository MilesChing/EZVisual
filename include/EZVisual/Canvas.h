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

        void SetShape(int layer_index, const vector<tuple<int, int>>& layer, const Color& layer_color);

        void SetImage(int layer_index, const vector<int>& layer);

    protected:
        vector<vector<unsigned int>> pixels;
        int layer_count = 1, layer_width, layer_height;

    private:
        int GetPos(int r, int c);
    };
#endif
}
