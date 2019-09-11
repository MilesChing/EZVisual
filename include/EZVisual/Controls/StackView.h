#include "EZVisual/Interfaces.h"
#include "EZVisual/Core.h"

using namespace cv;

#ifndef _EZVISUAL_STACK_VIEW_
#define _EZVISUAL_STACK_VIEW_
namespace EZVisual{

    class StackView : virtual public Backgroundable
                    , virtual public MinWidthable
                    , virtual public MinHeightable
                    , virtual public Marginable
                    , virtual public Paddingable
                    , virtual public Childrenable
                    , virtual public Orientationable{
    public:
        StackView(rapidjson::Value& json);
        ~StackView();

        void Draw(cv::Mat& target);
        void Measure();

        VisualElementType getType() const;
    };

}
#endif