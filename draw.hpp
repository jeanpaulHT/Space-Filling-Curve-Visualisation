#ifndef _DRAW_HPP_H_
#define _DRAW_HPP_H_

#include "headers.h"




namespace drawer{

    constexpr int DIM  = 1000;
    constexpr int SIDEDIM = 8;
    constexpr int OFFSET = 110;


    typedef std::function<int(int,int)> cord_func;
    typedef  cv::Point PType;



    std::vector<std::pair<PType, int>> getcordinates(cord_func pFunc){


        std::vector<std::pair<PType, int>> res{};

        for(int y = 0; y < SIDEDIM; y++){
            
            for(int x = 0; x< SIDEDIM; x++){
                int cord = pFunc(x,y);
                res.push_back(  {PType{ x,y}, cord } ); 

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

        return ( abs(a.x - b.x) <= 1 || abs(a.y - b.y) <= 1);
    }


    
    void projectToScreen(PType &p){
        p.x = p.x * OFFSET + OFFSET;
        p.y = p.y * OFFSET + OFFSET;
    }


    void draw(cord_func pFunc, std::string fname){


        cv::Mat imagen(DIM, DIM,CV_8UC3,cv::Scalar(0,0,0));
        
        cv::Scalar colorLine(0,0,255);
        int grosor = 2;

        auto cord =  getcordinates(pFunc);

        
        auto p1 = cord.begin();
        for(auto p2 =  cord.begin()+ 1; p2 != cord.end();p2++){
            

            PType a = p1->first;
            PType b = p2->first;

            projectToScreen(a);
            projectToScreen(b);
            

            cv::line(imagen, a, b, colorLine, grosor);
            p1++;
        }

        cv::imwrite("img/" + fname , imagen);
    }

}




#endif