#include "EZVisual/Interfaces.h"
#include <map>
#include <tuple>
#include <queue>
#include <mutex>
#include <set>

using namespace std;

#ifndef _EZVISUAL_CANVAS_
#define _EZVISUAL_CANVAS_

namespace EZVisual{


    class Canvas : virtual public Backgroundable
                 , virtual public Marginable
                 , virtual public Paddingable{

    public:
        Canvas(rapidjson::Value& json);
        ~Canvas(){}

        void Draw(cv::Mat& target) const;
        void Measure(int desired_width, int desired_height);

        VisualElementType getType() const;

        void PaintColor(const Color& color, int layer_index = 0);

        void PaintImage(const cv::Mat& mat, int layer_index = 0, const std::pair<int, int>& origin_point = make_pair(0, 0));

        void ClearLayer(int layer_index = 0);

        void SetLayerCount(int count);

        void SetLayerSize(const pair<int,int>& size);

        int GetLayerCount() const;

        int GetLayerWidth() const;

        int GetLayerHeight() const;




        void PaintCurve(const std::vector<std::pair<int,int>>& points, const Color& color = 0xff000000, int layer_index = 0, float point_size = 0);

        void PaintRect(const pair<int, int>& origin_point, int width, int height, int layer_index = 0, const Color& fill_color = 0, const Color& border_color = 0xff000000, float border_thickness = 1);

        void PaintCircle(const pair<float, float>& center_point, float r, int layer_index = 0, const Color& fill_color = 0, const Color& border_color = 0xff000000, float border_thickness = 1);

        void PaintLine(const pair<int, int>& a, const pair<int, int>& b, const Color& line_color = 0xff000000, int layer_index = 0, float line_thickness = 1);

        void PaintPixel(const pair<int, int>& point, const Color& point_color = 0xff000000, int layer_index = 0);


    protected:
        int layer_count = 1;
        int layer_width, layer_height;

        vector<vector<Color>> pixels;

        int GetIndex(int x, int y) const;

        std::mutex inner_q_mtx;
        queue<pair<int, int>> inner_q;
        set<pair<int, int>> inner_set;
    };

}

#endif
