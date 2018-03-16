#include <M5Stack.h>
#include "m5_internet_time.h"


#define LEAP_YEAR(_year) ((_year%4)==0)
static  byte monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};
static String SMTWTFS[7] = {"Sun" , "Mon" , "Tue" , "Wed" , "Thu" , "Fri" , "Sat" };

void m5_internet_time::update(unsigned long epoch)
{ 
 
  byte          year;
  byte          month, monthLength;
  long          days ;
  unsigned long dd ; 
  long          year_days; 
  
  ss   = (epoch % 60);  
  mm   = (epoch % 3600)/60;
  hh   = (epoch % 86400L)/3600;
  dd   = (epoch/86400L);  
  dw   = ((epoch/86400L) + 4) % 7; //0 is Sunday    

  // Determine year
  // Year as years from 1900 
  year = 70;  
  days = 0;
  while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= dd) {
    year++;
  }   
  yy = 1900 + year - 2000;    

  // Determine month  , day of year
  year_days = dd - (days - (LEAP_YEAR(year) ? 366 : 365));   
  
  for (month = 0; month < 12; month++)
  {   
    monthLength = (month == 1) ? (LEAP_YEAR(year) ? 29 : 28) : monthDays[month]; 
    dm = year_days + 1;     
    year_days   =  year_days - monthLength;      
    if(year_days <=  0)
    {
        mn = month + 1;
        break;  
    }   
  }   
}

 
m5_internet_time::m5_internet_time(int text_color,int background_color , int x_pos , int y_pos)
{
    tc = text_color;
    bc = background_color;    
    xpos = x_pos;
    ypos = y_pos;
} 
   
void m5_internet_time::display()
{    
    M5.Lcd.setTextColor(tc, bc);   

    // Format: mn_dm_yy day_of_week hh:mm:ss

    String smn = String(mn);                // month
    if(mn < 10) (smn = '0' + smn);    
    String sdm = String(dm);                // day of month
    if(dm < 10) ('0' + sdm); 
    String syy = String(yy);                // year             
    String sdw = ' ' + SMTWTFS[dw] + ' ';   // day of week
    String shh = String(hh);                // Hour
    if(hh < 10)('0' + hh);
    String smm = String(mm);                // Minute
    if(hh < 10)('0' + mm);
    String sss = String(ss);                // Second
    if(hh < 10)('0' + ss);
    
    String out = smn + '_' + sdm + '_' + syy + sdw + shh + ':' + smm + ':' + sss;
    //Serial.print(out);
    //Serial.print('\n');
    M5.Lcd.drawString(out, xpos, ypos, ts);     
    
}
