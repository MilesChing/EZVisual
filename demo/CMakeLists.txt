find_package(OpenCV)

if(OpenCV_FOUND)
    include_directories( ${OpenCV_INCLUDE_DIRS} )
    add_executable(EZVisualTest "EZVisualTest.cpp")
    target_link_libraries(EZVisualTest EZVisual ${OpenCV_LIBS})
endif(OpenCV_FOUND)