#ifndef _M5_DIGITAL_CLOCKS_H_
#define _M5_DIGITAL_CLOCKS_H_

#include <M5Stack.h>
#include "Arduino.h"

class m5_internet_time{
    public:     
        
        m5_internet_time(int text_color,int background_color , int x_pos , int y_pos );       

        void update(unsigned long epoch);        
       
        void display();

    private:
        uint8_t   ss   = 0;        // seconds
        uint8_t   mm   = 0;        // minutes
        uint8_t   hh   = 0;        // hours 
        uint8_t   dw   = 0;        // Day  of week   
        uint8_t   dm   = 0;        // Day  of Month 
        uint8_t   mn   = 0;        // Month
        uint8_t   yy   = 0;        // Year       
      
        int  tc;       // text color
        int  bc;       // background color
        int  ts = 4;   // text size
        int  ypos;     // y position
        int  xpos;     // x position
        
   private:

};

#endif

