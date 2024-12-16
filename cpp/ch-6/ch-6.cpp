#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

cv::Mat img_hsv, mask;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 179, smax = 255, vmax = 255;

int main()
{
    // std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/lambo.png";
    std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/shapes.png";
    cv::Mat img = cv::imread(path);

    cv::cvtColor(img, img_hsv, cv::COLOR_BGR2HSV);

    cv::namedWindow("Trackbars", (640,200));
    cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
    cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
    cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
    cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while(true)
    {
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(img_hsv, lower, upper, mask);

        cv::imshow("Image", img);
        cv::imshow("Image HSV", img_hsv);
        cv::imshow("Image Mask", mask);
        cv::waitKey(1);
    }
}