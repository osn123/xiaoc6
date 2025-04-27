void buttonState(Btn &btn)
{
  btn.State = digitalRead(btn.pin);
  if (btn.State != btn.lastState)
  {
    delay(50); // デバウンシングのための遅延

    if (btn.State == LOW)
    {
      // ボタン1が押されたときの処理を記述
      btn.mode = (btn.mode + 1) % xcnt; // 3つのモードを切り替える（0, 1, 2）
    }
    btn.lastState = btn.State; // ボタン1の状態を更新
  }
}

void printPixelData(Pixel &pix)
{
  // for (int i = 0; i < xcnt; ++i)
  // { // 配列の要素数分ループ
  //   // Serial.println("x[" + String(pix.name[i]) + "] = " + String(pix.x[i]++));
  // }
  Serial.print(">red:");
  Serial.println(String(pix.red));
  Serial.print(">green:");
  Serial.println(String(pix.green));
  Serial.print(">blue:");
  Serial.println(String(pix.blue));

  Serial.print(">State:");
  Serial.println(String(btn[0].State));

  Serial.print(">mode:");
  Serial.println(String(btn[0].mode));

  Serial.print(">pin:");
  Serial.println(String(btn[0].pin));

  Serial.print(">lastState:");
  Serial.println(String(btn[0].lastState));

  // Serial.println(btn[0].State);
  // Serial.println(btn[0].mode);
  // Serial.println(btn[0].pin);
  // Serial.println(btn[0].lastState);
}

void disp_sidebar(Pixel &pix)
{
  // display.clearDisplay(); // 表示クリア
  display.fillRect(0, 0, 2, 7 * (i + 1), SSD1306_WHITE);
  display.fillRect(3, 64 - 7 * (i + 1), 2, 7 * (i + 1), SSD1306_WHITE);
  display.display(); // 表示実行
}

void disp_mode(Pixel &pix)
{
  display.clearDisplay();                        // 表示クリア
  display.setTextSize(2);                        // 文字サイズ（1）
  display.setCursor(10, 6);                      // 表示開始位置左上角（X,Y）
  display.println("mode" + String(btn[0].mode)); // 表示内容

  display.setTextSize(1); // 文字サイズ（1）

  char buffer[8];
  sprintf(buffer, "%3d", pix.red);

  display.setCursor(62, 0);                     // 表示開始位置左上角（X,Y）
  display.println("    red " + String(buffer)); // 表示内容
  // display.println("    red " + String(pix.red));   // 表示内容

  display.setCursor(62, 9);                        // 表示開始位置左上角（X,Y）
  sprintf(buffer, "%3d", pix.green);
  display.println("  green " + String(buffer)); // 表示内容

  sprintf(buffer, "%3d", pix.blue);
  display.setCursor(62, 18);                       // 表示開始位置左上角（X,Y）
  display.println("   blue " + String(buffer));  // 表示内容

  sprintf(buffer, "%3d", pix.white);
  display.setCursor(62, 27);                       // 表示開始位置左上角（X,Y）
  display.println("  white " + String(buffer)); // 表示内容

  sprintf(buffer, "%3d", btn[3].mode * 10);
  display.setCursor(62, 45);                              // 表示開始位置左上角（X,Y）
  display.println("    pow " + String(buffer)); // 表示内容

  // sprintf(buffer, "%3d", pix.red);
  display.setCursor(62, 54);                              // 表示開始位置左上角（X,Y）
  display.println("  speed " + String("ee"));             // 表示内容

  display.display(); // 表示実行
}

void disp_pixel(Pixel &pix)
{
  pixels.clear();
//   pixels.setPixelColor(btn[0].mode, pixels.Color(pix.red, pix.green, pix.blue, pix.white)); // LEDの色を設定
  pixels.setPixelColor(btn[0].mode, pixels.Color(pix.red, pix.green, pix.blue)); // LEDの色を設定
  // pixels.rainbow()
  pixels.show(); // LEDに色を反映

  pixels2.clear();
  // pixels2.setPixelColor(0, pixels2.Color(pix.red, pix.green, pix.blue)); // LEDの色を設定

  pixels2.setPixelColor(1, pixels.getPixelColor(btn[0].mode)); // pixels.rainbow()
  pixels2.setPixelColor(0, pixels.getPixelColor(btn[0].mode)); // pixels.rainbow()
  // pixels2.setPixelColor(0, pixels2.ColorHSV(hsv[btn[0].mode].hue*256,hsv[btn[0].mode].sat,hsv[btn[0].mode].val )); // pixels.rainbow()
  // pixels2.setPixelColor(0, pixels2.ColorHSV(65535/(btn[0].mode+1),255,(btn[0].mode+1) * 60 )); // pixels.rainbow()
  // pixels2.setPixelColor(0, pixels2.ColorHSV(btn[0].mode * 255,255,(btn[0].mode+1) * 60 )); // pixels.rainbow()
  pixels2.show(); // LEDに色を反映
}

void disp(Pixel &pix)
{
  if (btn[0].mode != btn[0].lastmode)
  {
    disp_pixel(pix);
    // disp_sidebar(pix);
    disp_mode(pix);
  }
}

void handleButtonPress()
{
  detachInterrupt(digitalPinToInterrupt(btn[1].pin));
  btn[1].buttonPressed = true;
}
