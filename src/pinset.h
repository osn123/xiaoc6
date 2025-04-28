#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h> //別途「Adafruit BusIO」ライブラリ必要
#include <Adafruit_NeoPixel.h>

#define PIN 22
#define PIN2 18       // INが接続されているピンを指定

#define NUMPIXELS 7 // LEDの数を指定
#define NUMPIXELS2 10 // LEDの数を指定

// Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS2, PIN2, NEO_RGBW + NEO_KHZ800); // 800kHzでNeoPixelを駆動

#define SCREEN_WIDTH 128                                                  // OLED 幅指定
#define SCREEN_HEIGHT 64                                                  // OLED 高さ指定
#define OLED_RESET -1                                                     // リセット端子（未使用-1）
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // I2Cに接続されたSSD1306用「display」の宣言

// const int button[] = {13,14,15,16,17,18,19}; // ボタンピンNo
// const int button[] = {17, 13, 16, 14, 15, 18, 19}; // ボタンピンNo
const int button[] = {17,1,23,0}; // ボタンピンNo

// int buttonState1 = 0;     // ボタン1の状態を保持する変数
// int lastButtonState1 = 0; // ボタン1の直前の状態を保持する変数

// int mode = 0;     // 現在のモードを示す変数
// int lastmode = 0; // 現在のモードを示す変数

int i = 0;
//unsigned long previousMillis = 0;
const long interval = 500; // インターバルを1秒に設定

// volatile bool buttonPressed = false; // ボタンが押されたかどうかを示すフラグ
int const xcnt = 7;

// int const SDApinNo = 21;
// int const SCLpinNo = 22;
// Grove端子をI2C設定(SDA,SCL)

class Pixel
{
public:
  // uint16_t x[xcnt];
  // String name[xcnt];
  uint8_t red, green, blue, white;
};

// Pixel pix = {{0, 1, 2}, {"Name1", "Name2", "Name3"}, 255, 0, 0};
Pixel pix[10] = {

    {//   .x = {0, 1, 2},
     //  .name = {"Name1", "Name2", "Name3"},
     .red = 100,
     .green = 0,
     .blue = 0,
     .white = 55},

    {.red = 0,
     .green = 100,
     .blue = 0,
     .white = 200},
    {.red = 0,
     .green = 0,
     .blue = 100,
     .white = 150},
    {.red = 100,
     .green = 100,
     .blue = 0,
     .white = 100},

    {.red = 255,
     .green = 0,
     .blue = 255,
     .white = 200},
    {.red = 255,
     .green = 0,
     .blue = 255,
     .white = 100},
    {.red = 255,
     .green = 0,
     .blue = 255,
     .white = 50},

    {.red = 0,
     .green = 255,
     .blue = 255,
     .white = 255},
    {.red = 0,
     .green = 255,
     .blue = 255,
     .white = 200},
    {.red = 0,
     .green = 255,
     .blue = 255,
     .white = 150}

};
struct Hsv
{
  // long hue;
  unsigned short hue;
  byte sat, val;
};

Hsv hsv[] = {
    {
        .hue = 200 * 255,
        .sat = 255,
        .val = 155,
    },
    {
        .hue = 140 * 255,
        .sat = 255,
        .val = 155,
    },
    {
        .hue = 30 * 255,
        .sat = 255,
        .val = 155,
    },

};

struct Btn
{
  int pin, mode, State, lastState, lastmode;
  String name;
  unsigned long lastDebounceTime;
  int debounceDelay;
  volatile bool buttonPressed;
  byte presscnt;
};

Btn btn[] = {
    {.pin = button[0],
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[1],
     .mode = 1,
     .State = 1,
     .lastState = 0,
     .lastmode = 0,
     .name = "green",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[2],
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[3],
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[4],
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[5],
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

    {.pin = button[6],
     .mode = 0,
     .State = 0,
     .lastState = 0,
     .lastmode = 0,
     .name = "red",
     .lastDebounceTime = 0,
     .debounceDelay = 50,
     .buttonPressed = false},

};