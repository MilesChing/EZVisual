#include "EZVisual/Interfaces.h"
#include <map>
#include <tuple>

using namespace std;

#ifndef _EZVISUAL_CANVAS_
#define _EZVISUAL_CANVAS_

namespace EZVisual{


    class Canvas : virtual public Backgroundable
                 , virtual public Marginable{

    public:
        Canvas(rapidjson::Value& json);
        ~Canvas(){}

        void Draw(cv::Mat& target);
        void Measure();

        VisualElementType getType() const;

        void Paint(const Color& color, int layer_index = 0);

        void Paint(const cv::Mat& mat, int layer_index = 0, const std::pair<int, int>& origin_point = make_pair(0, 0));

        void ClearLayer(int layer_index = 0);

        void Paint(const std::vector<std::pair<int,int>>& points, const Color& color = 0xffffffff, int layer_index = 0);

        void Paint(const std::vector<std::tuple<int,int,Color>>& points, int layer_index = 0);

        void SetLayerCount(int count);

        void SetLayerSize(const pair<int,int>& size);

        int GetLayerCount() const;

        int GetLayerWidth() const;

        int GetLayerHeight() const;

    protected:
        int layer_count = 1;
        int layer_width, layer_height;

        vector<vector<Color>> pixels;

        int GetIndex(int x, int y);
    };

}

#endif
