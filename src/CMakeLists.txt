set(all_src ${all_src} "./Brushes/Brush.cpp")
set(all_src ${all_src} "./Brushes/SolidColorBrush.cpp")
set(all_src ${all_src} "./Brushes/LinearGradientBrush.cpp")

set(all_src ${all_src} "./Controls/Border.cpp")
set(all_src ${all_src} "./Controls/StackView.cpp")
set(all_src ${all_src} "./Controls/PlainText.cpp")
set(all_src ${all_src} "./Controls/Canvas.cpp")
set(all_src ${all_src} "./Controls/Button.cpp")
set(all_src ${all_src} "VisualElement.cpp")
set(all_src ${all_src} "Visualization.cpp")

add_library(EZVisual SHARED ${all_src})

install(TARGETS EZVisual DESTINATION lib)
