#include "pinset.h"  // ピン設定とライブラリのインクルード

#include "function.h"  // 関数定義のインクルード

// 初期設定
void setup()
{
  // 各ボタンのピンを入力として設定
  for (int i = 0; i < sizeof(btn) / sizeof(btn[0]); i++)  // ボタン配列の要素数分ループ
  {
    pinMode(btn[i].pin, INPUT_PULLUP);  // ボタンを入力として設定（内部プルアップ抵抗使用）
  }

  // attachInterrupt(digitalPinToInterrupt(btn[1].pin), handleButtonPress, FALLING);  // ボタンの割り込みを設定（現在はコメントアウト）

  Serial.begin(115200);  // シリアル通信の初期化（デバッグ用）
  Serial.println();  // 改行を出力
  
  Wire.begin(19,20);  // I2C通信の初期化（OLEDディスプレイ用）(SDA:19, SCL:20)

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // OLED初期設定
  {
    Serial.println(F("SSD1306:0 allocation failed"));  // エラーメッセージを出力
    for (;;)  // 無限ループ
      ; 
  }
  
  display.setTextColor(SSD1306_WHITE);  // 文字色を白に設定

  pixels.begin();  // 1つ目のNeoPixelを開始
  pixels2.begin();  // 2つ目のNeoPixelを開始
  pixels.setBrightness(5);    // 1つ目のNeoPixelの明るさを設定
  pixels2.setBrightness(10);  // 2つ目のNeoPixelの明るさを設定
}

// メインループ
void loop()
{
  buttonState(btn[0]);  // ボタン0の状態を監視（モード切り替え用）

  buttonState(btn[3]);  // ボタン3の状態を監視（明るさ調整用）

  pixels.setBrightness(btn[3].mode * 10);  // 1つ目のNeoPixelの明るさを設定
  pixels.show();  // LEDに色を反映
  pixels2.setBrightness(btn[3].mode * 10);  // 2つ目のNeoPixelの明るさを設定
  pixels2.show();  // LEDに色を反映

  if (btn[1].buttonPressed == true)  // ボタン1が押された時の処理（デバッグ表示用）
  {
    printPixelData(pix[1]);  // 現在の色情報をシリアルモニタに表示
    btn[1].buttonPressed = false;  // ボタン押下フラグをリセット
    btn[1].lastDebounceTime = millis();  // デバウンス時間を更新
  }

  if ((millis() - btn[1].lastDebounceTime) > btn[1].debounceDelay)  // デバウンス時間経過後に割り込みを再設定
  {
    attachInterrupt(digitalPinToInterrupt(btn[1].pin), handleButtonPress, FALLING);  // 割り込みを再設定
  }

  switch (btn[0].mode)  // モードに応じた色を表示
  {
  case 0: 
    disp(pix[0]);  // 赤色を表示
    break;
  case 1: 
    disp(pix[1]);  // 緑色を表示
    break;
  case 2: 
    disp(pix[2]);  // 青色を表示
    break;
  case 3: 
    disp(pix[3]);  // 黄色を表示
    break;
  case 4: 
    disp(pix[4]);  // マゼンタを表示
    break;
  case 5: 
    disp(pix[5]);  // マゼンタ（明るさ中）を表示
    break;
  case 6: 
    disp(pix[6]);  // マゼンタ（明るさ低）を表示
    break;

  default:  // その他の処理
    break;
  }

  btn[0].lastmode = btn[0].mode;  // モードを更新

  unsigned long currentMillis = millis();  // 現在の時間を取得
  if (currentMillis - previousMillis >= interval)  // 定期的な表示更新（500ms間隔）
  {
    display.fillRect(0, 0, 2, 7 * (i + 1), SSD1306_WHITE);  // 左サイドバーを描画
    display.fillRect(3, 64 - 7 * (i + 1), 2, 7 * (i + 1), SSD1306_WHITE);  // 右サイドバーを描画
    display.display();  // 表示実行
    previousMillis = currentMillis;  // 時間を更新
    
    if (i < 8)  // アニメーションカウンタの更新
      i++;
    else
    {
      i = 0;  // カウンタをリセット
      disp_mode(pix[btn[0].mode]);  // モード情報を表示
    }
  }
}