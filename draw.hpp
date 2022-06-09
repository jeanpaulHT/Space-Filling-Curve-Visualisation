#ifndef _DRAW_HPP_H_
#define _DRAW_HPP_H_

#include "headers.h"




namespace drawer{

    constexpr int DIM  = 1000;
    constexpr int SIDEDIM = 8;
    constexpr int OFFSET = 110;


    typedef std::function<int(int,int)> cord_func;
    typedef  cv::Point2f PType;



    std::vector<std::pair<PType, int>> getcordinates(cord_func pFunc){


        std::vector<std::pair<PType, int>> res{};

        for(int y = 0; y < SIDEDIM; y++){
            
            for(int x = 0; x< SIDEDIM; x++){
                int cord = pFunc(x,y);
                res.push_back(  {PType{  (float) x, (float) y}, cord } ); 

            }
        }

        std::sort(res.begin(), res.end(), []
        (   const std::pair<PType, int>& p1, 
            const std::pair<PType, int>& p2){
            return p1.second < p2.second;
        });

        return res;
    }


    inline bool adj(const PType& a, const PType& b){

        return ( abs(a.x - b.x) <= 1 && abs(a.y - b.y) <= 1);
    }


    
    void projectToScreen(PType &p){
        p.x = p.x * OFFSET + OFFSET;
        p.y = p.y * OFFSET + OFFSET;
    }

    cv::Mat curve42points(PType a, PType b){
        //Define the curve through equation. In this example, a simple parabola
        std::vector<PType> curvePoints;

        for (float x = a.x; x <= b.x; x+=1){
            float y = 0.0425*x*x - 6.25*x + 258;
            PType new_point = PType(x, y);                  //resized to better visualize]
            projectToScreen(new_point);
            curvePoints.push_back(new_point);                       //add point to vector/list
        }

        std::cout<<"hola\n";
        for(auto it: curvePoints){
            std::cout<<it.x<<" ";
        }
        std::cout<<'\n';
        
        cv::Mat curve(curvePoints, true);

        return curve;
    }


    void draw(cord_func pFunc, std::string fname){


        cv::Mat img(DIM, DIM,CV_8UC3,cv::Scalar(0,0,0));
        
        cv::Scalar colorLine(0,0,255);
        int grosor = 2;

        auto cord =  getcordinates(pFunc);

        
        auto p1 = cord.begin();
        for(auto p2 =  cord.begin()+ 1; p2 != cord.end();p2++){
            
            PType a = p1->first;
            PType b = p2->first;


            // if(adj(a,b)){
                projectToScreen(a);
                projectToScreen(b);
                cv::line(img, a, b, colorLine, grosor);            
            // }
            // else{
            //     auto curve = curve42points(a,b);
            //     curve.convertTo(curve, CV_32S);

            //     polylines(img, curve, true, cv::Scalar(0,0,255), 2, CV_8UC3);

            // }
            p1++;
        }

        cv::imwrite("img/" + fname , img);
    }

}




#endif