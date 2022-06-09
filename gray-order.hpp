#ifndef _GRAY_ORDER_HPP_
#define _GRA_ORDER_HPP_


#include "z-order.hpp"
#include "draw.hpp"


namespace gray{


    int Gray(int gray){
        int binary=0;
        for(;gray;gray=gray>>1){
            binary^=gray; //binary=binary^gray;
        }
        return binary;
    }

    int getGray(int x, int y){
        return Gray(zcord::getZcord(x,y ));
        
    }

    void draw(){
        drawer::draw(getGray, "GrayGrid.png");
    }
}




#endif