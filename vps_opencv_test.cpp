#include<opencv2/opencv.hpp>

int main(int argc, char* argv[])
{
    std::string device = "/dev/video0";
    if(argc > 1)
        device = argv[1];

    cv::namedWindow("vps");
    
    cv::VideoCapture vc(device);
    
    cv::Mat frame;
    
    char keyboard = 0;
    while( keyboard != 'q' && keyboard != 27 )
    {
        vc.read(frame);
        imshow("vps",frame);
        
        keyboard = (char)cv::waitKey(30);
    }
    
    return 0;
}

