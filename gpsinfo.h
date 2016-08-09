#ifndef GPS_INFO_H
#define GPS_INFO_H

#include <fcntl.h>       //文件打开关闭操作
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     //文件读写操作

#include <termios.h>    //串口设置
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include <ctype.h>
#include <errno.h>
#include <sys/mman.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/select.h>
#include <termios.h>
#include <pthread.h>

typedef struct{
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
}date_time;

typedef struct{
         date_time D;//时间
         char status;  		//接收状态
         double	latitude;   //纬度
         double longitude;  //经度
         char NS;           //南北极
         char EW;           //东西
         double speed;      //速度
         double high;       //高度
}GPS_INFO;

 void gps_parse(char *line,GPS_INFO *GPS);
 void show_gps(GPS_INFO *GPS);

#endif // GPS_INFO_H
