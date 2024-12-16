#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <iostream>

cv::Mat img_gray, img_blur, img_canny, img_dil, img_erode;

void getContours(cv::Mat img_dil, cv::Mat img)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(img_dil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // cv::drawContours(img, contours, -1, cv::Scalar(255,0,255), 10);

    for(int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        std::cout << area << std::endl;

        std::vector<std::vector<cv::Point>> conPoly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());
        std::string objectType;

        if(area > 1000)
        {
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            std::cout << conPoly[i].size() << std::endl;
            boundRect[i] = cv::boundingRect(conPoly[i]);

            int objCor = (int)conPoly[i].size();
            if(objCor == 3)
            {
                objectType = "Tri";
            } else if(objCor == 4)
            {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                std::cout << aspRatio << std::endl;
                if(aspRatio > 0.95 && aspRatio < 1.05)
                {
                    objectType = "Square";
                } else
                {
                    objectType = "Rect";
                }
            } else if(objCor > 4)
            {
                objectType = "Circle";
            }

            cv::drawContours(img, conPoly, i, cv::Scalar(255,0,255), 2);
            cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,0,255), 5);
            cv::putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,255), 2);
        }
    }
}

int main()
{
    std::string path = "/home/rafael/sinau/OpenCV-for-Beginner/resources/shapes.png";
    cv::Mat img = cv::imread(path);

    // Preprocessing
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(img_gray, img_blur, cv::Size(3,3), 3, 0);
    cv::Canny(img_blur, img_canny, 25, 75);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::dilate(img_canny, img_dil, kernel);
    // cv::erode(img_dil, img_erode, kernel);

    getContours(img_dil, img);

    cv::imshow("Image", img);
    // cv::imshow("Image Gray", img_gray);
    // cv::imshow("Image Blur", img_blur);
    // cv::imshow("Image Canny", img_canny);
    // cv::imshow("Image Dilate", img_dil);
    // cv::imshow("Image Erode", img_erode);
    cv::waitKey(0);
}