#include "pinset.h"

#include "function.h"

// #include "props.h"

// #include "methods.h"

void setup()
{
  for (int i = 0; i < sizeof(btn) / sizeof(btn[0]); i++)
  {
    pinMode(btn[i].pin, INPUT_PULLUP); // ボタンを入力として設定
  }

  // attachInterrupt(digitalPinToInterrupt(btn[1].pin), handleButtonPress, FALLING); // ボタンの割り込みを設定

  Serial.begin(115200);
  Serial.println();
  Wire.begin(19,20); // Grove端子をI2C設定(SDA,SDL)

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // OLED初期設定
  {
    Serial.println(F("SSD1306:0 allocation failed"));
    for (;;)
      ; // エラーなら無限ループ
  }
  
  display.setTextColor(SSD1306_WHITE); // 文字色

  pixels.begin();  // NeoPixelを開始
  pixels2.begin(); // NeoPixelを開始
  pixels.setBrightness(5);
  pixels2.setBrightness(10);
}

void loop()
{
  buttonState(btn[0]);

  buttonState(btn[3]);
  pixels.setBrightness(btn[3].mode * 10);
  pixels.show(); // LEDに色を反映
  pixels2.setBrightness(btn[3].mode * 10);
  pixels2.show(); // LEDに色を反映

  //   buttonState(btn[4]);

  if (btn[1].buttonPressed == true)
  {

    printPixelData(pix[1]);

    btn[1].buttonPressed = false;
    btn[1].lastDebounceTime = millis();
  }
  if ((millis() - btn[1].lastDebounceTime) > btn[1].debounceDelay)
  {
    attachInterrupt(digitalPinToInterrupt(btn[1].pin), handleButtonPress, FALLING); // ボタンの割り込みを設定
  }

  // disp(pix[btn[0].mode]);

  switch (btn[0].mode)
  {
  case 0: 
    disp(pix[0]);
    break;
  case 1: 
    disp(pix[1]);
    break;
  case 2: 
    disp(pix[2]);
    break;
  case 3: 
    disp(pix[3]);
    break;
  case 4: 
    disp(pix[4]);
    break;
  case 5: 
    disp(pix[5]);
    break;
  case 6: 
    disp(pix[6]);
    break;
  case 7: 
    disp(pix[7]);
    break;
  case 8: 
    disp(pix[8]);
    break;
  case 9: 
    disp(pix[9]);
    break;

  default: // その他の処理
    break;
  }

  btn[0].lastmode = btn[0].mode;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    // 一定時間経過した時の処理
    display.fillRect(0, 0, 2, 7 * (i + 1), SSD1306_WHITE);
    display.fillRect(3, 64 - 7 * (i + 1), 2, 7 * (i + 1), SSD1306_WHITE);
    display.display();              // 表示実行
    previousMillis = currentMillis; // 時間を更新
    if (i < 8)
      i++;
    else
    {
      i = 0;
      disp_mode(pix[btn[0].mode]);
    }
  }

  // for(int i=0; i<NUMPIXELS; i++) { //LEDを１つずつ制御
  //   display.fillRect(0, 0, 2, 7*(i+1), SSD1306_WHITE);
  //   display.fillRect(3, 64-7*(i+1), 2, 7*(i+1), SSD1306_WHITE);
  //   display.display();  //表示実行
  //   delay(500); //500ms待機
  // }
}