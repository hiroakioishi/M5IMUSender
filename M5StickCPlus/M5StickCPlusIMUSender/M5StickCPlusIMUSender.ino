#include <M5StickCPlus.h>
#include "BluetoothSerial.h"

BluetoothSerial _serialBT;

String _bluetoothName = "BT_M5StickCPlus_IMU_Data";

// 加速度
float _accX = 0.0F;
float _accY = 0.0F;
float _accZ = 0.0F;
// ジャイロ（角速度）
float _gyroX = 0.0F;
float _gyroY = 0.0F;
float _gyroZ = 0.0F;
// ピッチ、ロール、ヨー
float _pitch = 0.0F;
float _roll  = 0.0F;
float _yaw   = 0.0F;

char _buff[60];

void setup()
{
  // 本体初期化
  M5.begin();
  // シリアル通信初期化
  Serial.begin(9600);
  // Bluetooth通信初期化 
  _serialBT.begin(_bluetoothName);
  // IMUを初期化
  M5.Imu.Init();
  // スクリーンを回転
  M5.Lcd.setRotation(3);
  // 背景を黒で塗りつぶす
  M5.Lcd.fillScreen(BLACK);
  // テキストサイズをセット
  M5.Lcd.setTextSize(1);
  // カーソルの位置をセット
  M5.Lcd.setCursor(80, 15);
  // 
  M5.Lcd.println("IMU TEST");
  //
  M5.Lcd.setCursor(30, 30);
  
  //M5.Lcd.setTextColor(RED);
  //M5.Lcd.println("  X");
  //M5.Lcd.setTextColor(GREEN);
  //M5.Lcd.println("          Y");
  //M5.Lcd.setTextColor(BLUE);
  //M5.Lcd.println("                  Z");
  M5.Lcd.println("  X       Y       Z");
  M5.Lcd.setCursor(30, 70);
  M5.Lcd.println("  Pitch   Roll    Yaw");

}

void loop()
{
  M5.update();

  // ジャイロの値を取得
  M5.IMU.getGyroData(&_gyroX, &_gyroY, &_gyroZ);
  // 加速度の値を取得
  M5.IMU.getAccelData(&_accX, &_accY, &_accZ);
  // 姿勢および方位参照システムのデータ（Attitude and Heading Reference System）の取得
  M5.IMU.getAhrsData(&_pitch, &_roll, &_yaw);

  sprintf(_buff, "%5.1f,%5.1f,%5.1f\n", _pitch, _roll, _yaw);
  _serialBT.print(_buff);
  
  // M5.Lcd.fillScreen(BLACK);
  // テキストの色を白色に設定
  // M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor( 30, 40);
  M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", _gyroX, _gyroY, _gyroZ);
  M5.Lcd.setCursor(170, 40);
  M5.Lcd.printf("o/s");
  M5.Lcd.setCursor( 30, 50);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", _accX, _accY, _accZ);
  M5.Lcd.setCursor(170, 50);
  M5.Lcd.printf("G");
  M5.Lcd.setCursor( 30, 80);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", _pitch, _roll, _yaw);

  M5.Lcd.setCursor(30, 95);
  delay(50);


}