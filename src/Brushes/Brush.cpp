#include "EZVisual/Brushes.h"
#include "EZVisual/Tools/StringConverter.hpp"

using namespace rapidjson;

namespace EZVisual{

    Brush* Brush::CreateInstance(rapidjson::Value& json){
        if(json.IsString()) return new SolidColorBrush(json);
        else{
            rapidjson::Value& brush_type = json["BrushType"];
            if(!brush_type.IsString()) throw "BrushType not found.";
            else{
                BrushType type = StringConverter::ToBrushType(brush_type.GetString());
                if(type == BrushType::Null) throw "Unknown BrushType.";
                else switch (type){
                    case BrushType::SolidColorBrush: return new SolidColorBrush(json);
                    case BrushType::LinearGradientBrush: return new LinearGradientBrush(json);
                    default: return NULL;
                }
            }
        }
    }

    BrushType Brush::GetType() const{
        return BrushType::Null;
    }

}