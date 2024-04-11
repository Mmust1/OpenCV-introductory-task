#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat image = imread("Blueapp.jpg");

    if(image.empty()) {
        cout << "Can't load image" << endl; // check if image received correctly
        return -1;
    }

    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV); //Convert image from BGR to HSV and store in "hsvImage" variable


    Mat histogram; // start storing parameters of the histogram
    int histSize = 256; // Number of bins
    float range[] = {0, 256}; // Range of pixel values
    const float* histRange = {range};
    int channels[] = {0}; // Only 1 channel (hue)

    calcHist(&hsvImage, 1, channels, Mat(), histogram, 1, &histSize, &histRange, true, false); //Calculate histogram

    Point maxLoc; // used to find dominant color
    minMaxLoc(histogram, 0, 0, 0, &maxLoc); // store max value of bin in "maxLoc"
    cout << &maxLoc.x;

    cout << "Dominant Color (HSV): " << maxLoc.x << endl; // Display the dominant color in HSV
    //float dominantHue = maxLoc.x;

    Mat dominantColor(1, 1, CV_8UC3, Scalar(maxLoc.x, 255, 255));
    //Mat dominantColor(1, 1, CV_8UC3, Scalar(255, 255, dominantHue));

    cvtColor(dominantColor, dominantColor, COLOR_HSV2BGR); // Convert dominant color from HSV to BGR

    Vec3b bgrColor = dominantColor.at<Vec3b>(0, 0);
    cout << "Dominant Color (BGR): (" << (int)bgrColor[0] << ", " << (int)bgrColor[1] << ", " << (int)bgrColor[2] << ")" << endl; // output dominant colour

    cout << "Dominant Color (BGR): (" << (int)bgrColor[0] << ", " << (int)bgrColor[1] << ", " << (int)bgrColor[2] << ")" << endl;

    // Display the image
    imshow("Image", image);
    waitKey(0);

    return 0;
}
