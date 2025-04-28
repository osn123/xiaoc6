// ボタンの状態を監視し、モードを切り替える関数
void buttonState(Btn &btn)
{
  btn.State = digitalRead(btn.pin);  // ボタンの現在の状態を読み取る
  if (btn.State != btn.lastState)    // 状態が変化した場合
  {
    delay(50); // デバウンシングのための遅延（チャタリング防止）

    if (btn.State == LOW)  // ボタンが押されたとき
    {
      // モードを切り替える（0からxcnt-1まで循環）
      btn.mode = (btn.mode + 1) % xcnt;
    }
    btn.lastState = btn.State; // ボタンの状態を更新
  }
}

// ピクセルの色情報をシリアルモニタに表示する関数（デバッグ用）
void printPixelData(Pixel &pix)
{
  // RGBWの各色の値を表示
  Serial.print(">red:");
  Serial.println(String(pix.red));
  Serial.print(">green:");
  Serial.println(String(pix.green));
  Serial.print(">blue:");
  Serial.println(String(pix.blue));

  // ボタンの状態情報を表示
  Serial.print(">State:");
  Serial.println(String(btn[0].State));
  Serial.print(">mode:");
  Serial.println(String(btn[0].mode));
  Serial.print(">pin:");
  Serial.println(String(btn[0].pin));
  Serial.print(">lastState:");
  Serial.println(String(btn[0].lastState));
  Serial.println(String(btn[0].mode));
}

// サイドバーのアニメーションを表示する関数
void disp_sidebar(Pixel &pix)
{
  // 左右のサイドバーを描画
  display.fillRect(0, 0, 2, 7 * (i + 1), SSD1306_WHITE);
  display.fillRect(3, 64 - 7 * (i + 1), 2, 7 * (i + 1), SSD1306_WHITE);
  display.display(); // 表示実行
}

// 現在のモード情報をOLEDに表示する関数
void disp_mode(Pixel &pix)
{
  display.clearDisplay();                        // 表示クリア
  display.setTextSize(2);                        // 文字サイズ（2）
  display.setCursor(10, 6);                      // 表示開始位置
  display.println("mode" + String(btn[0].mode)); // モード番号を表示

  display.setTextSize(1); // 文字サイズを1に変更

  // 色情報を表示（RGBW）
  char buffer[8];
  sprintf(buffer, "%3d", pix.red);
  display.setCursor(62, 0);
  display.println("    red " + String(buffer));

  sprintf(buffer, "%3d", pix.green);
  display.setCursor(62, 9);
  display.println("  green " + String(buffer));

  sprintf(buffer, "%3d", pix.blue);
  display.setCursor(62, 18);
  display.println("   blue " + String(buffer));

  sprintf(buffer, "%3d", pix.white);
  display.setCursor(62, 27);
  display.println("  white " + String(buffer));

  // 明るさ情報を表示
  sprintf(buffer, "%3d", btn[3].mode * 10);
  display.setCursor(62, 45);
  display.println("    pow " + String(buffer));

  display.setCursor(62, 54);
  display.println("  speed " + String("ee"));

  display.display(); // 表示実行
}

// NeoPixelの色を設定して表示する関数
void disp_pixel(Pixel &pix)
{
  // 1つ目のNeoPixelの設定
  pixels.clear();
  pixels.setPixelColor(btn[0].mode, pixels.Color(pix.red, pix.green, pix.blue));
  pixels.show();

  // 2つ目のNeoPixelの設定
  pixels2.clear();
  // pixels2.setPixelColor(btn[0].mode, pixels.getPixelColor(btn[0].mode));
  pixels2.setPixelColor(btn[0].mode, pixels.Color(pix.red, pix.green, pix.blue,pix.white));
  pixels2.show();
}

// 表示を更新する関数
void disp(Pixel &pix)
{
  if (btn[0].mode != btn[0].lastmode)  // モードが変更された場合のみ更新
  {
    disp_pixel(pix);    // NeoPixelの色を更新
    disp_mode(pix);     // OLEDの表示を更新
  }
}

// ボタン割り込みハンドラ
void handleButtonPress()
{
  detachInterrupt(digitalPinToInterrupt(btn[1].pin));  // 割り込みを一時的に無効化
  btn[1].buttonPressed = true;  // ボタン押下フラグをセット
}
