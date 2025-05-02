#include <Arduino.h>  // Arduinoの基本ライブラリ
#include <Wire.h>  // I2C通信用ライブラリ
#include <Adafruit_SSD1306.h>  // OLEDディスプレイ用ライブラリ
#include <Adafruit_NeoPixel.h>  // NeoPixel用ライブラリ

#define PIN 22  // 1つ目のNeoPixelのデータピン
#define PIN2 18  // 2つ目のNeoPixelのデータピン
#define NUMPIXELS 7  // 1つ目のNeoPixelのLED数
#define NUMPIXELS2 10  // 2つ目のNeoPixelのLED数

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  // 1つ目のNeoPixelの設定
Adafruit_NeoPixel pixels2(NUMPIXELS2, PIN2, NEO_GRBW + NEO_KHZ800);  // 2つ目のNeoPixelの設定

#define SCREEN_WIDTH 128  // OLED 幅指定
#define SCREEN_HEIGHT 64  // OLED 高さ指定
#define OLED_RESET -1  // リセット端子（未使用-1）
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // OLEDディスプレイの設定

const int button[] = {17,1,23,0};  // ボタンピンNo

int i = 0;  // アニメーション用カウンタ
unsigned long previousMillis = 0;  // 前回の更新時間
const long interval = 500;  // 更新間隔（500ms）

int const xcnt = 7;  // モードの最大数

class Pixel  // ピクセルクラスの定義
{
public:
  uint8_t red, green, blue, white;  // RGBWの各色の値
};

Pixel pix[10] = {  // プリセットカラーの定義
    {.red = 100, .green = 0, .blue = 0, .white = 10},  // 赤
    {.red = 0, .green = 100, .blue = 0, .white = 20},  // 緑
    {.red = 0, .green = 0, .blue = 100, .white = 15},  // 青
    {.red = 100, .green = 100, .blue = 0, .white = 30},  // 黄
    {.red = 100, .green = 100, .blue = 100, .white = 40},  // 白
    {.red = 0, .green = 100, .blue = 100, .white = 10},  // シアン
    {.red = 100, .green = 0, .blue = 100, .white = 50},  // マゼンタ
    {.red = 0, .green = 100, .blue = 100, .white = 255},  // 明るいシアン
    {.red = 0, .green = 100, .blue = 100, .white = 200},  // 中程度のシアン
    {.red = 0, .green = 100, .blue = 100, .white = 150}  // 暗いシアン
};

struct Hsv  // HSV色空間の構造体
{
  unsigned short hue;  // 色相
  byte sat, val;  // 彩度、明度
};

Hsv hsv[] = {  // HSVプリセットの定義
    {.hue = 200 * 255, .sat = 255, .val = 155},  // 青系
    {.hue = 140 * 255, .sat = 255, .val = 155},  // 緑系
    {.hue = 30 * 255, .sat = 255, .val = 155},   // オレンジ系
};

struct Btn  // ボタン構造体の定義
{
  int pin, mode, State, lastState, lastmode;  // ピン番号、モード、状態関連
  String name;  // ボタン名
  unsigned long lastDebounceTime;  // 最後のデバウンス時間
  int debounceDelay;  // デバウンス遅延時間
  volatile bool buttonPressed;  // ボタン押下フラグ
  byte presscnt;  // 押下回数カウンタ
};

Btn btn[] = {  // ボタン配列の初期化
    {.pin = button[0],  // ボタン0の設定
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[1],  // ボタン1の設定
     .mode = 1,
     .State = 1,
     .lastState = 0,
     .lastmode = 0,
     .name = "green",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[2],  // ボタン2の設定
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[3],  // ボタン3の設定
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[4],  // ボタン4の設定
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[5],  // ボタン5の設定
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[6],  // ボタン6の設定
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},
};
