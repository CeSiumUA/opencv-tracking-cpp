#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

char* get_cmd_option(char ** begin, char ** end, const std::string & option);
bool cmd_option_exists(char** begin, char** end, const std::string& option);
void show_help();

int main(int argc, char** argv){

    if(cmd_option_exists(argv, argv + argc, "-h")){
        show_help();
        return 0;
    }

    Ptr<Tracker> tracker;
    tracker = TrackerMIL::create();

    Ptr<VideoCapture> video;

    if(cmd_option_exists(argv, argv + argc, "-f")){
        char* file_name = get_cmd_option(argv, argv + argc, "-f");
        video = new VideoCapture(file_name);
    }else if(cmd_option_exists(argv, argv + argc, "-c")){
        int cam_index = atoi(get_cmd_option(argv, argv + argc, "-c"));
        video = new VideoCapture(cam_index);
    }
    else{
        show_help();
        return 0;
    }

    if(!video -> isOpened()){
        cout << "File or cam not found!" << endl;
        return 1;
    }

    double original_fps = video -> get(CAP_PROP_FPS);
    double period = 1000 / original_fps;

    Mat frame;
    bool ok = video -> read(frame);

    Rect roi;

    cout << "Press an ESC key to exit" << endl;

    while(video -> read(frame)){

        double start_time = (double)getTickCount();

        putText(frame, "Original FPS: " + to_string(int(original_fps)), Point(20, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

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
            int diff = period - ticks_diff;
            delay = diff == 0 ? 1 : diff;
        }

        int k = waitKey(delay);

        if(k != -1){
            cout << "key pressed: " << to_string(k) << endl;
        }

        if(k == 27){
            break;
        }
        else if(k == 115){
            putText(frame, "Press enter when selected a target", Point(20, 110), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
            roi = selectROI("Tracking", frame);
            tracker -> init(frame, roi);
        }
    }

    video.release();

    destroyAllWindows();

    return 0;
}

char* get_cmd_option(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmd_option_exists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

void show_help(){
        cout << "To capture from file: -f <file name>" << endl;
        cout << "To capture from cam: -c <cam index (usually 0)>" << endl;
}