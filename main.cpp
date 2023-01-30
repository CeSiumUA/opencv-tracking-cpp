//
// Created by fedir on 1/29/23.
//

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){

    Ptr<Tracker> tracker;
    tracker = TrackerMIL::create();

    VideoCapture video("/home/fedir/projects/opencv-tracking/2.mp4");

    if(!video.isOpened()){
        cout << "File not found!" << endl;
        return 1;
    }

    double original_fps = video.get(CAP_PROP_FPS);
    double period = 1000 / original_fps;

    Mat frame;
    bool ok = video.read(frame);

    while(video.read(frame)){
        double start_time = (double)getTickCount();

        putText(frame, "Waiting for an object", Point(20, 80), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

        putText(frame, "Original FPS: " + static_cast<std::ostringstream &>(std::ostringstream() << std::dec << int(original_fps)).str(), Point(20, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

        putText(frame, "Alg: MIL", Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

        imshow("Tracking", frame);

        int delay = 1;

        double ticks_diff = (((double)getTickCount() - start_time)/getTickFrequency()) * 1000;

        if(period > ticks_diff){
            delay = period - ticks_diff;
        }

        int k = waitKey(delay);
        if(k == 27){
            break;
        }
    }

    waitKey(0);

    destroyAllWindows();

    return 0;
}