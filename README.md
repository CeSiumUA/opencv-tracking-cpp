# opencv-tracking-cpp

Project for OpenCV tracker

## Building and configuring

#### Building OpenCV

Install basic tools:
```
sudo apt install -y g++ cmake make wget unzip
```

Download sources:
```
git clone https://github.com/opencv/opencv.git
git -C opencv checkout 4.x
```

Configure and build:
```
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j7
```

Install:
```
sudo make install
```

Source: [OpenCV Docs](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)
For MacOS: [OpenCV Install to MacOS](https://docs.opencv.org/4.x/d0/db2/tutorial_macos_install.html)
For Windows: [OpenCV Install for Windows](https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html)

#### Building tracker

Build:
```
mkdir build
cd build
cmake ..
make
```

Run:

From file:
```
./opencv_tracking_cpp -f /home/fedir/projects/opencv-tracking/1.mp4
```

From cam:
```
./opencv_tracking_cpp -c 0
```