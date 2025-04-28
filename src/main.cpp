#include "pinset.h"
#include "function.h"

// 定数の定義
const uint8_t DISPLAY_WIDTH = 128;
const uint8_t DISPLAY_HEIGHT = 64;
const uint8_t ANIMATION_INTERVAL = 100;  // アニメーションの更新間隔
const uint8_t MAX_ANIMATION_STEPS = 8;   // アニメーションの最大ステップ数

// 関数プロトタイプ
void initializeHardware();
void updateButtonStates();
void updateLEDs();
void updateDisplay();
void handleDisplayAnimation();

// グローバル変数
unsigned long previousMillis = 0;
uint8_t animationStep = 0;

void setup()
{
  initializeHardware();
}

void initializeHardware()
{
  for (int i = 0; i < sizeof(btn) / sizeof(btn[0]); i++)
  {
    pinMode(btn[i].pin, INPUT_PULLUP); // ボタンを入力として設定
  }

  // attachInterrupt(digitalPinToInterrupt(btn[1].pin), handleButtonPress, FALLING); // ボタンの割り込みを設定

  Serial.begin(115200);
  Serial.println();
  Wire.begin(19, 20); // Grove端子をI2C設定(SDA,SCL)

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // OLED初期設定
  {
    Serial.println(F("SSD1306:0 allocation failed"));
    while (true)
    {
      // エラー時の処理（例：LEDでエラー表示など）
      delay(1000);
    }
  }

  display.setTextColor(SSD1306_WHITE); // 文字色

  pixels.begin();  // NeoPixelを開始
  pixels2.begin(); // NeoPixelを開始
  pixels.setBrightness(5);
  pixels2.setBrightness(10);
}

void loop()
{
  updateButtonStates();
  updateLEDs();
  updateDisplay();
  handleDisplayAnimation();
}

void updateButtonStates()
{
  buttonState(btn[0]);
  buttonState(btn[3]);

  if (btn[1].buttonPressed)
  {
    printPixelData(pix[1]);
    btn[1].buttonPressed = false;
    btn[1].lastDebounceTime = millis();
  }

  if ((millis() - btn[1].lastDebounceTime) > btn[1].debounceDelay)
  {
    attachInterrupt(digitalPinToInterrupt(btn[1].pin), handleButtonPress, FALLING); // ボタンの割り込みを設定
  }
}

void updateLEDs()
{
  uint8_t brightness = btn[3].mode * 10;
  pixels.setBrightness(brightness);
  pixels2.setBrightness(brightness);
  pixels.show();  // LEDに色を反映
  pixels2.show(); // LEDに色を反映
}

void updateDisplay()
{
  // モードに応じた表示処理
  if (btn[0].mode < sizeof(pix) / sizeof(pix[0]))
  {
    disp(pix[btn[0].mode]);
  }
}

void handleDisplayAnimation()
{
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= ANIMATION_INTERVAL)
  {
    // アニメーションの更新
    display.fillRect(0, 0, 2, 7 * (animationStep + 1), SSD1306_WHITE);
    display.fillRect(3, DISPLAY_HEIGHT - 7 * (animationStep + 1), 2, 7 * (animationStep + 1), SSD1306_WHITE);
    display.display();
    
    previousMillis = currentMillis;
    
    if (animationStep < MAX_ANIMATION_STEPS)
    {
      animationStep++;
    }
    else
    {
      animationStep = 0;
      disp_mode(pix[btn[0].mode]);
    }
  }
}

// for(int i=0; i<NUMPIXELS; i++) { //LEDを１つずつ制御
//   display.fillRect(0, 0, 2, 7*(i+1), SSD1306_WHITE);
//   display.fillRect(3, 64-7*(i+1), 2, 7*(i+1), SSD1306_WHITE);
//   display.display();  //表示実行
//   delay(500); //500ms待機
// }