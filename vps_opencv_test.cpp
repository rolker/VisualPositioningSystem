#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

int main(int argc, char* argv[])
{
    std::string device = "/dev/video0";
    if(argc > 1)
        device = argv[1];

    cv::namedWindow("vps");
    
    cv::VideoCapture vc(device);
    
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    
    char keyboard = 0;
    while( keyboard != 'q' && keyboard != 27 )
    {
        cv::Mat frame_in, frame_out;

        vc.read(frame_in);
        frame_in.copyTo(frame_out);
        
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners;
        cv::aruco::detectMarkers(frame_in, dictionary, markerCorners, markerIds);

        cv::aruco::drawDetectedMarkers(frame_out, markerCorners, markerIds);
        imshow("vps",frame_out);
        
        keyboard = (char)cv::waitKey(30);
    }
    
    return 0;
}

