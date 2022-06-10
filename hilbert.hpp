#ifndef _HILBERT_HPP_
#define _HILBERT_HPP_

#include "headers.h"


namespace hilbert{


    
    constexpr int DIM  = 1000;
    constexpr int SIDEDIM = 8;
    constexpr int OFFSET = 110;

    constexpr int level = 2;


    typedef  cv::Point PType;
    std::vector<PType> curvePoints;

    void LineTo(int x, int y){
        curvePoints.push_back({x,y});
        std::cout<<x<<" "<<y<<'\n';
    }
    
    void hilbert(int x, int y, int xi, int xj, int yi, int yj, int n){
        if(n<= 0){
            LineTo(x + (xi + yi)/2, y + (xj + yj)/2);
        }
        else{
            hilbert(x               , y             , yi/2  , yj/2  , xi/2  , xj/2, n-1);
            hilbert(x + xi/2        , y + xj/2      , xi/2  , xj/2  , yi/2  , yj/2, n-1);
            hilbert(x + xi/2 + yi/2 , y+xj/2+yj/2   , xi/2  , xj/2  , yi/2  , yj/2, n-1);
            hilbert(x + xi/2 + yi   , y+xj/2+yj     , -yi/2 , -yj/2 , -xi/2 , -xj/2, n-1);
        }
    }


        
    void projectToScreen(PType &p){
        p.x = p.x * OFFSET + OFFSET;
        p.y = p.y * OFFSET + OFFSET;
    }


    void draw(){
        cv::Mat img(DIM, DIM,CV_8UC3,cv::Scalar(0,0,0));
        cv::Scalar colorLine(0,0,255);

        int grosor = 2;


        curvePoints.clear();
        //origen, eje x, eje y
        hilbert(0, 0, 
                DIM , 0, 
                0, DIM ,  6);
        

        auto cord = curvePoints;

        auto p1 = cord.begin();
        for(auto p2 =  cord.begin()+ 1; p2 != cord.end();p2++){
            
            PType a = *p1;
            PType b = *p2;


            // if(adj(a,b)){
                // projectToScreen(a);
                // projectToScreen(b);
                cv::line(img, a, b, colorLine, grosor);            
            // }
            // else{
            //     auto curve = curve42points(a,b);
            //     curve.convertTo(curve, CV_32S);

            //     polylines(img, curve, true, cv::Scalar(0,0,255), 2, CV_8UC3);

            // }
            p1++;
        }

        cv::imwrite("img/hilbert.png" , img);
    }

}


#endif