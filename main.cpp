#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgcodecs.hpp>

#include <bitset>
#include <cmath>

constexpr int DIM  = 1000;
constexpr int SIDEDIM = 8;
constexpr int OFFSET = 100;


constexpr int bits = 3;
constexpr int bsize = 4;
constexpr int Level = bits - 1;  


int intercalateBits(int x, int level){    

    
    int y = (x << (1<<level));

    int m = (1<<(Level - level)) + 1;
    int x_ = (m<<bsize ) | (m);

    int y_ =  (x | y) & (x_);
    
    // printf("for level %d, m = [%d],res = [%d]\n", level, m,  y_);
    // std::cout<<"x "<<std::bitset<bsize * 2>{x}<<std::endl;
    // std::cout<<"y "<<std::bitset<bsize * 2>{y}<<std::endl;
    // std::cout<<"x_ "<<std::bitset<bsize * 2>{x_}<<std::endl;
    // std::cout<<"y_ "<<std::bitset<bsize * 2>{y_}<<std::endl;

    if(level == 0) return y_;
    else return intercalateBits(y_, level-1);
}


int getZcord(int x, int y){

    x =  intercalateBits(x, Level - 1);
    y =  intercalateBits(y, Level - 1);
    y = (y<<1);

    return (x | y);
}


std::vector<std::pair<cv::Point, int>> getZcordinates(){

    std::vector<std::pair<cv::Point, int>> res{};

    for(int y = 0; y < SIDEDIM; y++){
        
        for(int x = 0; x< SIDEDIM; x++){

           res.push_back(  {cv::Point{ x * OFFSET + OFFSET, y * OFFSET + OFFSET}, getZcord(x,y)} ); 

        //    std::cout<<res.back().first.x<<" "<<res.back().first.y<<","<<res.back().second<<'\n';
        }

        // return {};
    }

    std::sort(res.begin(), res.end(), []
    (   const std::pair<cv::Point, int>& p1, 
        const std::pair<cv::Point, int>& p2){
        return p1.second < p2.second;
    });


    return res;
}

int main(){




    cv::Mat imagen(1000,1000,CV_8UC3,cv::Scalar(0,0,0));


    // //RGB
    // //default -> BGR
    // // c:
    cv::Scalar colorLine(0,0,255);
    int grosor = 2;

    auto cord = getZcordinates();
    
    auto p1 = cord.begin();
    for(auto p2 =  cord.begin()+ 1; p2 != cord.end();p2++){

        cv::line(imagen, (*p1).first, (*p2).first, colorLine, grosor);
        p1++;
    }

    cv::imwrite("imagen.png", imagen);
    return 0;

}