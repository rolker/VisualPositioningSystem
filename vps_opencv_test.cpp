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
    
    int tw = w/4;
    int th = h/4;
    
    std::cout << tw << "x" << th << std::endl;
    
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_50);
    
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
        resize(frame_out,thumbnail,cv::Size(tw,th));
        imshow("vps",thumbnail);
        //imshow("vps",frame_out);
        
        if(!markerIds.empty())
        {
            for (int i = 0; i < markerIds.size(); i++)
            {
                std::cout << markerIds[i] << " size: ";
                cv::Point2f d1 = markerCorners[i][2] - markerCorners[i][0];
                cv::Point2f d2 = markerCorners[i][3] - markerCorners[i][1];
                
                std::cout << (norm(d1)+norm(d2))/2.0 << " px, ";
                
                double a1 = atan2(markerCorners[i][0].y-markerCorners[i][3].y,markerCorners[i][0].x-markerCorners[i][3].x)*180.0/M_PI;
                double a2 = atan2(markerCorners[i][1].y-markerCorners[i][2].y,markerCorners[i][1].x-markerCorners[i][2].x)*180.0/M_PI;
                
                double aa = (a1+a2)/2.0;
                
                aa = aa+90.0;
                
                if(aa < 0.0)
                    aa += 360.0;
                
                
                std::cout << " heading: " << aa << " degs, ";
            }
            std::cout << std::endl;
        }
        
        keyboard = (char)cv::waitKey(30);
    }
    
    return 0;
}

