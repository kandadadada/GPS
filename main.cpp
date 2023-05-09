#include "mbed.h"
#include "GPS.h"

#define PI 3.1415

GPS michibiki(GPSTX,GPSRX);
Serial pc(USBTX, USBRX, 115200);

float delta_x, delta_y, now_x, now_y, sita, goal_y_rad,temp1,temp2,gps_theta;

const float goal_x = 139.543255;             //ゴールの経度(初期値は適当,35.657941,139.542798
const float goal_y = 35.658841;             //ゴールの緯度
const float R = 6371000.0;                     //地球の半径 [m]

float r;


int main() {

    while(1){
    now_y = michibiki.latitude;//GPSを取得(タイマー割り込みで取得される)緯度
    now_x = michibiki.longtitude; 
    r = R * acos(sin(goal_y*PI/180) * sin(now_y*PI/180)+cos(now_y*PI/180) * cos(goal_y*PI/180)*cos((goal_x - now_x)*PI/180));     
    r = abs(r); 

    pc.printf("now_x=%f,now_y=%f r=%f\n",now_x,now_y,r);


    //北からの角度を出力する
    delta_x = delta_x * PI/180;
    now_x = now_x * PI/180;
    goal_y_rad = goal_y * PI/180;
    now_y = now_y * PI/180;

    temp1 = cos(now_y)*tan(goal_y_rad);
    temp2 = sin(now_y)*cos(delta_x);

    gps_theta = atan2(sin(delta_x),(temp1-temp2));
    gps_theta= gps_theta * 180/PI;  

    pc.printf("theta=%f\n",gps_theta);







    }
}

