# EZVisual

A lightweight C++ visual framework for quickly and customizationally generating graphical interfaces using JSON.

EZVisual has the following features:

- Free and flexible GUI;
- Thread-safe dynamic UI updates;
- Free 2D drawing with alpha channels;

![EZVisual Demo](https://milesching.github.io/images/Others/EZVisual_Demo.gif)

## Build EZVisual in Linux

EZVisual uses following software and library as its dependencies:

- [CMake](https://cmake.org/)
- [RapidJSON](http://rapidjson.org/index.html)
- [OpenCV](https://opencv.org/)
- [EZEvent](https://github.com/MilesChing/EZEvent)

**Clone** or **download** our [source code](https://github.com/MilesChing/EZVisual/archive/master.zip).

~~~shell
git clone https://github.com/MilesChing/EZVisual.git
~~~

Build EZVisual from source using [CMake](https://cmake.org/).

~~~shell
cd EZVisual
mkdir build
cd build
cmake ..
~~~

From build directory execute **make** to build the project.

~~~shell
make -j4
~~~

Install libraries and get start!

~~~shell
sudo make install
~~~

## Brief guide to EZVisual

### Visual profile

EZVisual using [JSON](https://json.org/) as a GUI description language. Each visual profile describes the related properties of a window and the layout, controls, and their properties in the window. A window starts with a JSON object, and you can set attributes like `FPS`, `Background` or `Title` to the object.

~~~json
{
    "Title": "EZVisual",
    "FPS": 40,
    "Background": "#000000",
    "Layout": {
        "Type": "Border",
        "Width": 300,
        "Height": 150,
        "Margin": [20, 20, 20, 40],
        "Background": "#ffc408"
    }
}
~~~

Obviously, the `Layout` property is the most important of which, and we use it to set the visual element at the root. Each visual element is also an object, the example above shows a Border with no content. We can use attributes `Width`, `Height` or `Margin` just like using HTML or XAML.

### Create a window

In an application built by EZVisual, each window is based on an object of the `Visualization` class. This object provides a way to start the interface thread, as well as the entire method for getting and setting control properties.

After compiling and installing EZVisual, add this to your header files to include our libraries:

~~~cpp
#include "EZVisual/EZVisual.h"
~~~

Now, try to read the profile through a Visualization object and create a new window.

~~~cpp
EZVisual::Visualization visual("{path to your visual profile}");
visual.LaunchWindow();
//It is highly recommended that you use a new thread like this:
//    thread t(&Visualization::LaunchWindow, &visual);
~~~

Lucky, you'll see a black window with a yellow rectangle in it.

![Guide](https://milesching.github.io/images/Others/EZVisual_Guide.png)
