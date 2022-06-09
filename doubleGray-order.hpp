#ifndef _DOUBLE_GRAY_ORDER_HPP_
#define _DOUBLE_GRAY_ORDER_HPP_


#include "z-order.hpp"
#include "draw.hpp"


namespace doubleGray{


    int doubleGray(int x){
        int x_ = x ^ (x >> 1);
        return x_;
    }

    int getDoubleGray(int x, int y){
        return doubleGray(zcord::getZcord(x,y ));
        
    }

    void draw(){
        drawer::draw(getDoubleGray, "DoubleGrayGrid.png");
    }
}




#endif