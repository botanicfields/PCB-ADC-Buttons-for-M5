# PCB-ADC-Button-for-M5
a PCB converts 5 buttons into 1 analog output


# M5 用光センサ・押しボタン 5 基板
## Ambient Light Sensor and 5 Buttons for M5

<img src="./image/front.JPEG" width=300>
<img src="./image/back.JPEG" width=300>

### 委託販売: スイッチサイエンス

https://www.switch-science.com/catalog/7227/

# 1. 特徴

- 周囲の明るさをアナログ電圧で出力します
- 押しボタン 5 個の操作を、1 本のアナログ電圧で出力します
- GROVE コネクタで接続します
- 出力レベルは 0 ~ 3.3V で、M5(ESP32) の GPIO に合わせています
- 電源は 5V で、M5シリーズの GROVE コネクタに合わせています
- JC_Button と同等の判定を可能とするプログラムを用意しています
- 手に持つことを考慮し、スルーホール部品を使用していません
- センサーへの影響を考慮し、パイロットランプはありません。

# 2. 注意
- 押しボタンスイッチのチャタリングや接触抵抗による誤動作が皆無とは言えません。時刻の設定など、結果を確認しながら操作し、やり直しを可能とするなど、運用でカバーできる範囲でご利用ください。

- 複数ボタンの同時押しの判定はできません。

- M5Stack Basic の GROVE コネクタに直結して使用することはできません。
「GROVE-ジャンパケーブル」などを用いて、アナログ入力の GPIO および 5V, GND に接続する必要があります。

「GROVE - 4ピン - ジャンパオスケーブル（5本セット）」

https://www.switch-science.com/catalog/6245/)

「GROVE - 4ピン-ジャンパメスケーブル (5本セット)」

https://www.switch-science.com/catalog/1048/

M5Stack Basic で、G35, G36, 5V, GND に接続した例

<img src="./image/m5stack.jpeg" width=300>

## M5 シリーズの GROVE ポート

　M5 シリーズ (ESP32) では、アナログ入力として一般に G32 ～ G39 が使用されます。
G2, G4, G12 ~ G15, G24 ~ G26 のアナログ入力機能は、Wi-Fi 等が使用しますので
一般には使いづらいです。G0 はプルアップがあるなどアナログ入力には向きません。

| モデル | GROVE | 主な用途 |
|:-:|:-:|:-:|
| M5Stack Basic| G22, G21 | I2C |
| M5Stack Core2| G33, G32 | I2C, I/O, UART |
| M5StickC | G33, G32 | I2C, I/O, UART |
| M5Atom | G32, G26 | I2C, I/O, UART |


# 3. 内容

## 光センサ
Everlight ALS-PT19

https://jp.everlight.com/wp-content/plugins/ItemRelationship/product_files/pdf/ALS-PT19-315C-L177-TR8_V8.pdf

## ソフトウェア

### (1) BF_AdcButton.h, BF_Adc_Button.cpp
光センサの出力を読み出すプログラム、および 5 個の押しボタンの状態を読み出すプログラムです。JC_Button を流用・改変しています。

https://github.com/JChristensen/JC_Button

### (2) BF_AdcButtonTest.h, BF_Adc_ButtonTest.cpp
上記コードを呼び出すテスト用のプログラムです。

### (3) BF-028.ino
上記テストプログラムのメインプログラムです。

# 4. 解説
Qiita 「ESP32 のアナログ入力で、押しボタン 5 個を判別する」

https://qiita.com/BotanicFields/items/15d8d45836a4d2f6c87a

# 5. 接続例
「RGB LED 276 for M5Atom」への接続例です。

<img src="./image/example.JPEG" width=300>
