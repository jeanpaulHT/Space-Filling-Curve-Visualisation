#ifndef _DRAW_HPP_H_
#define _DRAW_HPP_H_

#include "headers.h"




namespace drawer{

    constexpr int DIM  = 1000;
    constexpr int SIDEDIM = 8;
    constexpr int OFFSET = 110;


    typedef std::function<int(int,int)> cord_func;


    std::vector<std::pair<cv::Point, int>> getcordinates(cord_func pFunc){


        std::vector<std::pair<cv::Point, int>> res{};

        for(int y = 0; y < SIDEDIM; y++){
            
            for(int x = 0; x< SIDEDIM; x++){
                int cord = pFunc(x,y);
                res.push_back(  {cv::Point{ x,y}, cord } ); 

            }
        }

        std::sort(res.begin(), res.end(), []
        (   const std::pair<cv::Point, int>& p1, 
            const std::pair<cv::Point, int>& p2){
            return p1.second < p2.second;
        });

        return res;
    }





    void draw(cord_func pFunc, std::string fname){


        cv::Mat imagen(DIM, DIM,CV_8UC3,cv::Scalar(0,0,0));
        
        cv::Scalar colorLine(0,0,255);
        int grosor = 2;

        auto cord =  getcordinates(pFunc);

        
        auto p1 = cord.begin();
        for(auto p2 =  cord.begin()+ 1; p2 != cord.end();p2++){

            cv::Point a = {(*p1).first.x * OFFSET + OFFSET,(*p1).first.y * OFFSET + OFFSET};
            cv::Point b = {(*p2).first.x * OFFSET + OFFSET,(*p2).first.y * OFFSET + OFFSET};


            cv::line(imagen, a, b, colorLine, grosor);
            p1++;
        }

        cv::imwrite("img/" + fname , imagen);
    }

}




#endif