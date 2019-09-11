#include "opencv2/opencv.hpp"
#include "EZVisual/Core.h"
#include "EZVisual/Interfaces.h"
#include <string>
#include <map>

using namespace std;
using namespace cv;

namespace EZVisual{
#ifndef _EZVISUAL_AUTO_WRAP_STACK_
#define _EZVISUAL_AUTO_WRAP_STACK_
    class AutoWrapStack : virtual public Childrenable
                        , virtual public Marginable
                        , virtual public Paddingable
                        , virtual public Backgroundable
                        , virtual public MinWidthable
                        , virtual public MinHeightable
                        , virtual public Orientationable{
    public:
        AutoWrapStack(rapidjson::Value& json);
        ~AutoWrapStack(){};

        void Draw(cv::Mat& target);
        void Measure();

        VisualElementType getType() const;

        void SetWrapLength(int length);

    protected:
        vector<pair<int, int>> children_origins;
        int wrap_length = 200;
    };
#endif
}
