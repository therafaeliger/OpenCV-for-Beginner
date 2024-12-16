#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

int main()
{
    std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/test.png";
    cv::Mat img = cv::imread(path);
    cv::Mat img_resize, img_crop;

    // std::cout << "Image size: " << img.size() << std::endl;
    // cv::resize(img, img_resize, cv::Size(640, 480));
    cv::resize(img, img_resize, cv::Size(), 0.5, 0.5);

    cv::Rect roi(200,100,300,300);
    img_crop = img(roi);

    cv::imshow("Image", img);
    cv::imshow("Image Resize", img_resize);
    cv::imshow("Image Crop", img_crop);
    cv::waitKey(0);
}