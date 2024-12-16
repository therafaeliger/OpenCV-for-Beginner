#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

int main()
{
    /* image */
    // std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/test.png";
    // cv::Mat img = cv::imread(path);
    // cv::imshow("Image", img);
    // cv::waitKey(0);


    /* video */
    // std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/test_video.mp4";
    // cv::VideoCapture cap(path);
    // cv::Mat frame;

    // while(true)
    // {
    //     cap.read(frame);
    //     cv::imshow("Video", frame);
    //     cv::waitKey(10);
    // }

    /* webcam */
    cv::VideoCapture cap(0);
    cv::Mat frame;

    while(true)
    {
        cap.read(frame);
        cv::imshow("Webcam", frame);
        cv::waitKey(20);
    }
}