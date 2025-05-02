// ボタンの状態を監視し、モードを切り替える関数
void buttonState(Btn &btn)  // ボタンの状態を監視し、モードを切り替える関数
{
  btn.State = digitalRead(btn.pin);  // ボタンの現在の状態を読み取る
  if (btn.State != btn.lastState)    // 状態が変化した場合
  {
    delay(50);  // デバウンシングのための遅延（チャタリング防止）

    if (btn.State == LOW)  // ボタンが押されたとき
    {
      btn.mode = (btn.mode + 1) % xcnt;  // モードを切り替える（0からxcnt-1まで循環）
    }
    btn.lastState = btn.State;  // ボタンの状態を更新
  }
}

// ピクセルの色情報をシリアルモニタに表示する関数（デバッグ用）
void printPixelData(Pixel &pix)  // ピクセルの色情報をシリアルモニタに表示する関数（デバッグ用）
{
  Serial.print(">red:");  // 赤色の値を表示
  Serial.println(String(pix.red));
  Serial.print(">green:");  // 緑色の値を表示
  Serial.println(String(pix.green));
  Serial.print(">blue:");  // 青色の値を表示
  Serial.println(String(pix.blue));

  Serial.print(">State:");  // ボタンの状態情報を表示
  Serial.println(String(btn[0].State));
  Serial.print(">mode:");  // モード情報を表示
  Serial.println(String(btn[0].mode));
  Serial.print(">pin:");  // ピン番号を表示
  Serial.println(String(btn[0].pin));
  Serial.print(">lastState:");  // 前回の状態を表示
  Serial.println(String(btn[0].lastState));
  Serial.println(String(btn[0].mode));  // 現在のモードを表示
}

// サイドバーのアニメーションを表示する関数
void disp_sidebar(Pixel &pix)  // サイドバーのアニメーションを表示する関数
{
  display.fillRect(0, 0, 2, 7 * (i + 1), SSD1306_WHITE);  // 左サイドバーを描画
  display.fillRect(3, 64 - 7 * (i + 1), 2, 7 * (i + 1), SSD1306_WHITE);  // 右サイドバーを描画
  display.display();  // 表示実行
}

// 現在のモード情報をOLEDに表示する関数
void disp_mode(Pixel &pix)  // 現在のモード情報をOLEDに表示する関数
{
  display.clearDisplay();  // 表示クリア
  display.setTextSize(2);  // 文字サイズ（2）
  display.setCursor(10, 6);  // 表示開始位置
  display.println("mode" + String(btn[0].mode));  // モード番号を表示

  display.setTextSize(1);  // 文字サイズを1に変更

  char buffer[8];  // バッファの宣言
  sprintf(buffer, "%3d", pix.red);  // 赤色の値をフォーマット
  display.setCursor(62, 0);  // カーソル位置を設定
  display.println("    red " + String(buffer));  // 赤色の値を表示

  sprintf(buffer, "%3d", pix.green);  // 緑色の値をフォーマット
  display.setCursor(62, 9);  // カーソル位置を設定
  display.println("  green " + String(buffer));  // 緑色の値を表示

  sprintf(buffer, "%3d", pix.blue);  // 青色の値をフォーマット
  display.setCursor(62, 18);  // カーソル位置を設定
  display.println("   blue " + String(buffer));  // 青色の値を表示

  sprintf(buffer, "%3d", pix.white);  // 白色の値をフォーマット
  display.setCursor(62, 27);  // カーソル位置を設定
  display.println("  white " + String(buffer));  // 白色の値を表示

  sprintf(buffer, "%3d", btn[3].mode * 10);  // 明るさの値をフォーマット
  display.setCursor(62, 45);  // カーソル位置を設定
  display.println("    pow " + String(buffer));  // 明るさの値を表示

  display.setCursor(62, 54);  // カーソル位置を設定
  display.println("  speed " + String("ee"));  // 速度情報を表示

  display.display();  // 表示実行
}

// NeoPixelの色を設定して表示する関数
void disp_pixel(Pixel &pix)  // NeoPixelの色を設定して表示する関数
{
  pixels.clear();  // 1つ目のNeoPixelをクリア
  pixels.setPixelColor(btn[0].mode, pixels.Color(pix.red, pix.green, pix.blue));  // 1つ目のNeoPixelの色を設定
  pixels.show();  // 1つ目のNeoPixelを表示

  pixels2.clear();  // 2つ目のNeoPixelをクリア
  pixels2.setPixelColor(btn[0].mode, pixels.Color(pix.red, pix.green, pix.blue,pix.white));  // 2つ目のNeoPixelの色を設定
  pixels2.show();  // 2つ目のNeoPixelを表示
}

// 表示を更新する関数
void disp(Pixel &pix)  // 表示を更新する関数
{
  if (btn[0].mode != btn[0].lastmode)  // モードが変更された場合のみ更新
  {
    disp_pixel(pix);    // NeoPixelの色を更新
    disp_mode(pix);     // OLEDの表示を更新
  }
}

// ボタン割り込みハンドラ
void handleButtonPress()  // ボタン割り込みハンドラ
{
  detachInterrupt(digitalPinToInterrupt(btn[1].pin));  // 割り込みを一時的に無効化
  btn[1].buttonPressed = true;  // ボタン押下フラグをセット
}
