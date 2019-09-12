# EZVisual

A lightweight C++ visual framework for quickly and customizationally generating graphical interfaces using JSON.

![EZVisual Demo](https://milesching.github.io/images/Others/EZVisual_Demo.png)

## Build EZVisual in Linux

EZVisual uses following software and library as its dependencies:

- [CMake](https://cmake.org/)
- [RapidJSON](http://rapidjson.org/index.html)
- [OpenCV](https://opencv.org/)

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


