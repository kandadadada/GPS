#ifndef GPS_H
#define GPS_H
 



//GPS Library for GYSFDMAXB
/*
秋月電子にて販売されているGYSFDMAXB(GPS受信機1pps出力付きみちびき対応)用ライブラリです
Uartの受信割り込みを用いて、センテンスを受信し始めると自動的に処理を行い、緯度経度を計算します。

※注意　割り込み設定を行わないと正常に動作しません。mbedの場合は全ての割りこみが同じ優先順位なので優先順位の衝突が生じます
STMマイコンの場合は、
NVIC_SetPriority(USART3_IRQn,2);
などとmain内に追加します。usart3とは、Serial3_TXとSerial3_RXを使っているためです。Serial1_TX,RXを使用するなら、usart1と入れてください
'2'は、優先順位のことです。mbedではデフォルトで全て2に設定されています(stmマイコンの場合)。0が一番優先順位が高く、1,2,3の順に低くなります。




*/

#define GPSTX D1//GPSのTXピン
#define GPSRX D0//GPSのRXピン
#define GPSBAUD 9600//GPSのボーレート
#define ODR 30//max 10Hz　更新周期
 
class GPS {
public:
    GPS(PinName gpstx,PinName gpsrx);
    
    void gpscmd(char *command);
    void getgps();
    
    float longtitude;//緯度
    float latitude;//経度
    //上の二つは自動的に更新される この二つを読むことでデータ取得が出来る
    
    bool result;//trueで成功、falseで失敗
    char buf[100];
  
private:  
    Serial _gps;
};
 
#endif
