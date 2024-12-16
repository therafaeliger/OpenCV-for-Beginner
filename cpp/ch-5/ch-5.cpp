#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

float w = 250, h = 350;
cv::Mat matrix, img_warp;

int main()
{
    std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/cards.jpg";
    cv::Mat img = cv::imread(path);

    cv::Point2f src[4] = {{529,142}, {771,190}, {405,395}, {674,457}};
    cv::Point2f dst[4] = {{0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h}};

    matrix = cv::getPerspectiveTransform(src, dst);
    cv::warpPerspective(img, img_warp, matrix, cv::Point(w,h));

    for(int i = 0; i < 4; i++)
    {
        cv::circle(img, src[i], 10, cv::Scalar(0,0,255), cv::FILLED);
    }

    cv::imshow("Image", img);
    cv::imshow("Image Warp", img_warp);
    cv::waitKey(0);
}