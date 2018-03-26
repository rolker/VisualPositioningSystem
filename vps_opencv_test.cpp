#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

int main(int argc, char* argv[])
{
    std::string device = "/dev/video0";
    if(argc > 1)
        device = argv[1];

    cv::namedWindow("vps");
    
    cv::VideoCapture vc(device);
    int w = vc.get(CV_CAP_PROP_FRAME_WIDTH);
    int h = vc.get(CV_CAP_PROP_FRAME_HEIGHT);
    
    std::cout << w << "x" << h << std::endl;

    vc.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    
    w = 3280;
    h = 2464;
    
    vc.set(CV_CAP_PROP_FRAME_WIDTH,w);
    vc.set(CV_CAP_PROP_FRAME_HEIGHT,h);
    
    w = vc.get(CV_CAP_PROP_FRAME_WIDTH);
    h = vc.get(CV_CAP_PROP_FRAME_HEIGHT);
    
    std::cout << w << "x" << h << std::endl;
    
    
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
        
        cv::Mat thumbnail;
        resize(frame_out,thumbnail,cv::Size(320,240));
        imshow("vps",thumbnail);
        //imshow("vps",frame_out);
        
        if(!markerIds.empty())
        {
            for (auto id: markerIds)
                std::cout << id << ", ";
            std::cout << std::endl;
        }
        
        keyboard = (char)cv::waitKey(30);
    }
    
    return 0;
}

