#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <iostream>

cv::Mat frame;
cv::VideoCapture cap(0);

std::vector<std::vector<int>> newPoints;

// Hue min | Hue max | Sat min | Sat max | Val min | Val max
std::vector<std::vector<int>> myColors { {99,126,70,196,156,253},
                                        {124,48,117,143,170,255},
                                        {68,72,156,102,126,255} }; // you can add another color

std::vector<cv::Scalar> myColorValues { {255,0,0},
                                        {255,0,255},
                                        {0,255,0} }; // you can add another color

cv::Point getContours(cv::Mat frame_get)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(frame_get, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    cv::Point myPoint(0,0);

    for(int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        std::cout << area << std::endl;

        if(area > 1000)
        {
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            std::cout << conPoly[i].size() << std::endl;
            boundRect[i] = cv::boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            cv::drawContours(frame, conPoly, i, cv::Scalar(255,0,255), 2);
            cv::rectangle(frame, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,0,255), 5);
        }
    }

    return myPoint;
}

std::vector<std::vector<int>> findColor(cv::Mat frame)
{
    cv::Mat frame_hsv;
    cv::cvtColor(frame, frame_hsv, cv::COLOR_BGR2HSV);

    for(int i = 0; i < myColors.size(); i++)
    {
        cv::Scalar lower(myColors[i][0], myColors[i][2], myColors[i][4]);
        cv::Scalar upper(myColors[i][1], myColors[i][3], myColors[i][5]);
        cv::Mat mask;
        cv::inRange(frame_hsv, lower, upper, mask);
        // cv::imshow(std::to_string(i), mask);
        cv::Point myPoint = getContours(mask);

        if(myPoint.x != 0 && myPoint.y != 0)
        {
            newPoints.push_back({myPoint.x, myPoint.y, i});
        }
    }
    return newPoints;
}

void drawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<cv::Scalar> myColorValues)
{
    for(int i = 0; i < newPoints.size(); i++)
    {
        cv::circle(frame, (cv::Point(newPoints[i][0], newPoints[i][1])), 10, myColorValues[newPoints[i][2]], cv::FILLED);
    }
}

int main()
{
    while(true)
    {
        cap.read(frame);
        newPoints = findColor(frame);
        drawOnCanvas(newPoints, myColorValues);

        cv::imshow("Webcam", frame);
        cv::waitKey(1);
    }
}