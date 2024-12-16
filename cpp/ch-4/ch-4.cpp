#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

int main()
{
    // create blank image
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255,255,255));

    cv::circle(img, cv::Point(256,256), 155, cv::Scalar(0,0,0), 10);
    cv::circle(img, cv::Point(256,256), 100, cv::Scalar(255,0,0), cv::FILLED);

    cv::rectangle(img, cv::Point(130,226), cv::Point(382,286), cv::Scalar(0,255,0), 3);
    cv::rectangle(img, cv::Point(150,246), cv::Point(362,266), cv::Scalar(0,0,255), cv::FILLED);

    cv::line(img, cv::Point(130,300), cv::Point(382,300), cv::Scalar(0,0,0), 2);

    cv::putText(img, "OpenCV for Beginner", cv::Point(136,200), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0,0,255), 2);

    cv::imshow("Image", img);
    cv::waitKey(0);
}