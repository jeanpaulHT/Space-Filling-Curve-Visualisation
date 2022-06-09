#ifndef _Z_ORDER_HPP_
#define _Z_ORDER_HPP_

#include "headers.h"
#include "draw.hpp"

namespace zcord{

    constexpr int bits = 3;
    constexpr int bsize = 4;
    constexpr int Level = bits - 1;  


    int intercalateBits(int x, int level){    
        int s = (1<<level);
        int y = (x << (s));

        int m = (1<<(Level - level)) + 1;
        int x_ = (m<<bsize ) | (m);

        int y_ =  (x | y) & (x_);


        if(level == 0) return y_;
        else return intercalateBits(y_, level-1);
    }


    int getZcord(int x, int y){

        x =  intercalateBits(x, Level - 1);
        y =  intercalateBits(y, Level - 1);
        y = (y<<1);

        return (x | y);
    }


    void draw(){
        drawer::draw(getZcord, "ZGrid.png");
    }

}
#endif