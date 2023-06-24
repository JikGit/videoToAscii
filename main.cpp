#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>
#include <thread>


char getAsciiFromPixel(int pixelIntensivity) {
    std::string ASCII_CHARS = "@%#*+=-. ";

    return ASCII_CHARS[ASCII_CHARS.length() - ASCII_CHARS.length() * pixelIntensivity / 256];
}

int main() {
    cv::VideoCapture video("./vids/vid2.mp4");
    cv::Mat frame, grayFrame, resizedFrame;

    if (!video.isOpened())
        return -1;

    const int FPS = video.get(cv::CAP_PROP_FPS);

    int frameWidth = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int frameHeight = video.get(cv::CAP_PROP_FRAME_HEIGHT);

    float width = 500; //character
    float height = width * frameHeight / frameWidth * 0.42;

    for (; ;) {
        video >> frame;
        if (frame.empty())
            break;

        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        resize(grayFrame, resizedFrame, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);

        std::string asciiFrame = "";
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int pixelIntensity = (int)resizedFrame.at<uchar>(y,x);
                asciiFrame += getAsciiFromPixel(pixelIntensity);
            }
            asciiFrame += '\n';
        }

        system("clear");
        std::cout << asciiFrame;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/FPS));
    }

    video.release();
    cv::destroyAllWindows();
}







