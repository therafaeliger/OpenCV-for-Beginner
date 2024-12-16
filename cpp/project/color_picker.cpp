#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <iostream>

cv::Mat frame_hsv, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

int main()
{
    cv::VideoCapture cap(0);
    cv::Mat frame;

    cv::namedWindow("Trackbars", (640,200));
    cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
    cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
    cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
    cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while(true)
    {
        cap.read(frame);
        cv::cvtColor(frame, frame_hsv, cv::COLOR_BGR2HSV);

        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(frame_hsv, lower, upper, mask);

        std::cout << "Hue min: " << hmin << " | "
                  << "Hue max: " << hmax << " | "
                  << "Sat min: " << smin << " | "
                  << "Sat max: " << smax << " | "
                  << "Val min: " << vmin << " | "
                  << "Val max: " << vmax << std::endl;

        cv::imshow("Webcam", frame);
        cv::imshow("Mask", mask);
        cv::waitKey(1);
    }
}