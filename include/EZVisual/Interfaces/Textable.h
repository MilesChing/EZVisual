#include "EZVisual/Interfaces/VisualElement.h"

namespace EZVisual{

#ifndef _EZVISUAL_TEXTABLE_
#define _EZVISUAL_TEXTABLE_
    class Textable : virtual public VisualElement{
    public:
        Textable(rapidjson::Value& json) : VisualElement(json){
            if(json["FontColor"].IsString())
                font_color = Color(json["FontColor"].GetString());
            if(json["FontWeight"].IsInt())
                font_weight = json["FontWeight"].GetInt();
            if(json["Text"].IsString())
                text = json["Text"].GetString();
            if(json["FontSize"].IsNumber())
                font_size = json["FontSize"].GetDouble();
            if(json["FontFamily"].IsInt())
                font_family = json["FontFamily"].GetInt();
        }

        /**Set text for this element.*/
        void SetText(const char* text){
            this->text = string(text);
        }

        /**Set font size for this element.
         *
         * @param font_size Font size to be set for. 0.8 is recommended for ordinary texts.
         */
        void SetFontSize(double font_size){
            if(font_size == this->font_size) return;
            this->font_size = font_size;
        }

        /**Set font color for this element.
         *
         * @param color Font color to be set for.
         */
        void SetFontColor(const Color& color){
            if(color == this->font_color) return;
            this->font_color = color;
        }

        /**Set font weight for this element.
         *
         * @param font_weight Font weight to be set for. 1 is recommended for ordinary texts.
         */
        void SetFontWeight(int font_weight){
            if(font_weight == this->font_weight) return;
            this->font_weight = font_weight;
        }

        /**@brief Set font family for this element.
         *
         * Set font family for this element. Font family is an integer falls in [0, 7]. Visit https://docs.opencv.org/2.4.13.6/modules/core/doc/drawing_functions.html#initfont for details.
         *
         * @param font_family Font family to be set for.
         */
        void SetFontFamily(int font_family){
            this->font_family = font_family;
        }

        /**Get text of this element.
         *
         * @ret Text of this element.
         */
        string GetText(){
            return string(text);
        }

        /**Get font size of this element.
         *
         * @ret Font size of this element.
         */
        double SetFontSize(){
            return font_size;
        }

        /**Get font color of this element.
         *
         * @ret Font color of this element.
         */
        Color GetFontColor(){
            return font_color;
        }

        /**Get font weight of this element.
         *
         * @ret Font weight of this element.
         */
        int GetFontWeight(){
            return font_weight;
        }

        /**@brief Get font family of this element.
         *
         * Get font family of this element. Font family is an integer falls in [0, 7]. Visit https://docs.opencv.org/2.4.13.6/modules/core/doc/drawing_functions.html#initfont for details.
         *
         * @ret font_family Font family of this element.
         */
        int GetFontFamily(){
            return font_family;
        }

        void MeasureText(){
            auto size = cv::getTextSize(
                text,
                font_family,
                font_size,
                font_weight,
                &text_base_line
            );

            text_width = size.width;
            text_height = size.height;
        }

    protected:
        Color font_color = Color(0xff000000);
        int font_weight = 1;
        string text = "";
        double font_size = 0.75;
        int font_family = 0;

        int text_height, text_width, text_base_line;
    };

#endif

}

