#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

int main()
{
    std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/test.png";
    cv::Mat img = cv::imread(path);
    cv::Mat img_gray, img_blur, img_canny, img_dil, img_erode;

    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(img_gray, img_blur, cv::Size(3,3), 3, 0);
    cv::Canny(img_blur, img_canny, 25, 75);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));
    cv::dilate(img_canny, img_dil, kernel);
    cv::erode(img_dil, img_erode, kernel);

    cv::imshow("Image", img);
    cv::imshow("Image Gray", img_gray);
    cv::imshow("Image Blur", img_blur);
    cv::imshow("Image Canny", img_canny);
    cv::imshow("Image Dilate", img_dil);
    cv::imshow("Image Erode", img_erode);
    cv::waitKey(0);
}