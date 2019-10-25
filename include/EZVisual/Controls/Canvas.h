#include "EZVisual/Interfaces.h"
#include <map>
#include <tuple>
#include <queue>
#include <mutex>
#pragma once
#include <set>

using namespace std;

namespace EZVisual{

    /**@brief Canvas is a multi-layer view element which allows you to paint 2D shapes and images on.
     *
     * Canvas is a multi-layer view element which allows you to paint 2D shapes and images on. Each layer of a canvas has an index which falls in [0, layer_count).
     *
     * Each layer are initially transparent and is shown orderly on your screen: layer 0 is at the bottom and layer layer_count - 1 is on the top. You are able to draw on a layer or clear the content of it at any time. A multi-layer blend will be shown on the screen finally.
     */
    class Canvas : virtual public Backgroundable
                 , virtual public Marginable{

    public:
        Canvas(rapidjson::Value& json);

        void Draw(cv::Mat& target);
        void Measure(int desired_width, int desired_height);

        VisualElementType getType() const;

        /**@brief Paint color on this canvas.
         *
         * Paint color on this canvas. The color will always fill the viewport.
         *
         * @param color Color to be painted.
         * @param layer_index Index of the layer you prepare to paint on.
         */
        void PaintColor(const Color& color, int layer_index = 0);

        /**@brief Paint an image on this canvas.
         *
         * Paint an image on this canvas. The image is stored using OpenCV's data type, visit https://docs.opencv.org/3.4/d3/d63/classcv_1_1Mat.html to learn more. On a canvas, an image has to be painted with its original width and height. You can only specify a position to paint at which contains the desired top-left point of the image. A point is represented by it's coordinate on the canvas where (0, 0) is the coordinate of the top-left point of the canvas.
         *
         * @param mat Image to be painted.
         * @param layer_index Index of the layer you prepare to paint on.
         * @param origin_point The desired top-left point of the image.
         */
        void PaintImage(const cv::Mat& mat, int layer_index = 0, const std::pair<int, int>& origin_point = make_pair(0, 0));

        /**@brief Clear the content of a layer.
         *
         * Clear the content of a layer. The target layer will become totally transparent before you paint something on it.
         * @param layer_index Index of the layer you prepare to clear.
         */
        void ClearLayer(int layer_index = 0);

        /**@brief Set the count of layers.
         *
         * Set the count of layers. This operation will lead to the loss of content on some layers.
         *
         * @param count The new count to be set to.
         */
        void SetLayerCount(int count);

        /**@brief Set the size of the layer.
         *
         * Set the size of the layer. The visible range of the canvas is [0, layer_height) x [0, layer_width]. Pixel out of this range will be collapsed. If you reset the layer_size of a canvas, all the content on it will get lost. All layers have the same size.
         *
         * @param size Pair of (int, int) represents the width and height of the new size.
         */
        void SetLayerSize(const pair<int,int>& size);

        /**@brief Get height of the layer.
         *
         * Get height of the layer. The visible range of the canvas is [0, layer_height) x [0, layer_width]. Pixel out of this range will be collapsed. All layers have the same size.
         *
         * @ret Return the height of the layer.
         */
        int GetLayerCount() const;

        /**@brief Get width of the layer.
         *
         * Get width of the layer. The visible range of the canvas is [0, layer_height) x [0, layer_width]. Pixel out of this range will be collapsed. All layers have the same size.
         *
         * @ret Return the width of the layer.
         */
        int GetLayerWidth() const;

        /**@brief Get height of the layer.
         *
         * Get height of the layer. The visible range of the canvas is [0, layer_height) x [0, layer_width]. Pixel out of this range will be collapsed. All layers have the same size.
         *
         * @ret Return the height of the layer.
         */
        int GetLayerHeight() const;

        /**@brief Paint a curve on this canvas.
         *
         * Paint a curve which made up by points width a same color on this canvas. A point is represented by it's coordinate on the canvas where (0, 0) is the coordinate of the top-left point of the canvas.
         *
         * @param points Vector of points to be painted.
         * @param color Color of the curve. Use PaintPixel if you want to paint with more colors.
         * @param layer_index Index of the layer you prepare to paint on.
         */
        void PaintCurve(const std::vector<std::pair<int,int>>& points, const Color& color = 0xff000000, int layer_index = 0, float point_size = 0);

        /**@brief Paint a rectangle on this canvas.
         *
         * Paint a rectangle on this canvas. A rectangle is represented by it's top-left point, width and height. You can draw a border around your rectangle with specific color and thickness as well. In which a point is represented by it's coordinate on the canvas where (0, 0) is the coordinate of the top-left point of the canvas.
         *
         * @param origin_point Top-left point of the rectangle.
         * @param width Width of the rectangle.
         * @param height Height of the rectangle.
         * @param fill_color Color to be fill into the rectangle.
         * @param border_color Color of the border.
         * @param layer_index Index of the layer you prepare to paint on.
         * @param line_thickness Thickness of the border. Set this to 0 if you don't want a border.
         */
        void PaintRect(const pair<int, int>& origin_point, int width, int height, const Color& fill_color = 0, const Color& border_color = 0xff000000, int layer_index = 0, float border_thickness = 1);

        /**@brief Paint a circle on this canvas.
         *
         * Paint a circle on this canvas. A circle is represented by it's center and radius. You can draw a border around your circle with specific color and thickness as well. In which a point is represented by it's coordinate on the canvas where (0, 0) is the coordinate of the top-left point of the canvas.
         *
         * @param center_point Center of the circle.
         * @param r Radius of the circle.
         * @param fill_color Color to be fill into the circle.
         * @param border_color Color of the border.
         * @param layer_index Index of the layer you prepare to paint on.
         * @param line_thickness Thickness of the border. Set this to 0 if you don't want a border.
         */
        void PaintCircle(const pair<float, float>& center_point, float r, const Color& fill_color = 0, const Color& border_color = 0xff000000, int layer_index = 0, float border_thickness = 1);

        /**@brief Paint a line segment on this canvas.
         *
         * Paint a line segment on this canvas. A line segment is represented by it's endpoints. In which a point is represented by it's coordinate on the canvas where (0, 0) is the coordinate of the top-left point of the canvas.
         *
         * @param a An endpoint of the line segment.
         * @param b An endpoint of the line segment.
         * @param line_color Color of the line segment.
         * @param layer_index Index of the layer you prepare to paint on.
         * @param line_thickness Thickness of the line. The actual thickness will be at least 1 pixel.
         */
        void PaintLine(const pair<int, int>& a, const pair<int, int>& b, const Color& line_color = 0xff000000, int layer_index = 0, float line_thickness = 1);

        /**@brief Paint a pixel on this canvas.
         *
         * Paint a pixel on this canvas. In which a pixel is represented by it's coordinate on the canvas where (0, 0) is the coordinate of the top-left point of the canvas.
         *
         * @param point Coordinate of the pixel.
         * @param point_color Color of the pixel.
         * @param layer_index Index of the layer you prepare to paint on.
         */
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