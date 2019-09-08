find_package(OpenCV)

set(all_src ${all_src} "Border.cpp")
set(all_src ${all_src} "Core.cpp")
set(all_src ${all_src} "VisualElement.cpp")
set(all_src ${all_src} "Visualization.cpp")
set(all_src ${all_src} "StackView.cpp")
set(all_src ${all_src} "PlainText.cpp")
set(all_src ${all_src} "AutoWrapStack.cpp")

add_library(EZVisual ${all_src})
