#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

int main(int argc, char* argv[])
{
    std::string path = "./";
    if (argc > 1)
        path = argv[1];
    
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_50);

    for(int i = 0; i < 50; i++)
    {
        cv::Mat marker;
        cv::aruco::drawMarker(dictionary, i, 400, marker);
        std::stringstream fname;
        fname << path << "aruco_7x7_50_";
        if (i < 10)
            fname << 0;
        fname << i;
        fname << ".png";
        cv::imwrite(fname.str(),marker);
    }
    
}

