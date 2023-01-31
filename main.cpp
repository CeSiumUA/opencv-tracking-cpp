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

    Rect roi;

    cout << "Press an ESC key to exit" << endl;

    while(video.read(frame)){

        double start_time = (double)getTickCount();

        putText(frame, "Original FPS: " + static_cast<std::ostringstream &>(std::ostringstream() << std::dec << int(original_fps)).str(), Point(20, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

        putText(frame, "Alg: MIL", Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

        bool tracked = false;

        if(!roi.empty()){
            tracked = tracker -> update(frame, roi);
            rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
        }

        string tracking_text = "Waiting for an object";

        if(tracked){
            tracking_text = "Target detected";
        }

        putText(frame, tracking_text, Point(20, 80), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

        imshow("Tracking", frame);

        int delay = 1;

        double ticks_diff = (((double)getTickCount() - start_time)/getTickFrequency()) * 1000;

        if(period > ticks_diff){
            delay = period - ticks_diff;
        }

        int k = waitKey(delay);

        if(k != -1){
            cout << "key pressed: " << to_string(k) << endl;
        }

        if(k == 27){
            break;
        }
        else if(k == 115){
            roi = selectROI("Tracking", frame);
            tracker -> init(frame, roi);
        }
    }

    destroyAllWindows();

    return 0;
}