set(all_src ${all_src} "./Controls/Border.cpp")
set(all_src ${all_src} "./Controls/StackView.cpp")
set(all_src ${all_src} "./Controls/PlainText.cpp")
set(all_src ${all_src} "./Controls/Canvas.cpp")
set(all_src ${all_src} "VisualElement.cpp")
set(all_src ${all_src} "Visualization.cpp")

add_library(EZVisual SHARED ${all_src})

install(TARGETS EZVisual DESTINATION lib)
