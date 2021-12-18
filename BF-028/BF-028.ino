// Copyright 2021 BotanicFields, Inc.
// BF-028: Ambient Light Sensor and 5 Buttons of 3.3V Analog Signal and 5V Power
// test and example

//#define M5STACK
//#define M5STICKC
//#define M5STICKCPLUS
#define M5ATOM

#ifdef M5STACK
#include <M5Stack.h>
#endif
#ifdef M5STICKC
#include <M5StickC.h>
#endif
#ifdef M5STICKCPLUS
#include <M5StickCPlus.h>
#endif
#ifdef M5ATOM
#include <M5Atom.h>
#endif

#include "BF_AdcButton.h"
#include "BF_AdcButtonTest.h"

// loop contol
const int ambient_period_ms(1000);  // 5sec
const int loop_delay_ms(20);
unsigned int last_ms(0);
int loop_count(0);

void setup()
{
#ifdef M5STACK
  const bool lcd_enable(true);
  const bool sd_enable(true);
  const bool serial_enable(true);
  const bool i2c_enable(true);
  M5.begin(lcd_enable, sd_enable, serial_enable, i2c_enable);
  const int analog_port_button_pin(35);  // GPIO35 <NOT GROVE-A PORT> 
  const int ambient_light_pin(36);       // GPIO36 <NOT GROVE-A PORT>
#endif
#ifdef M5STICKC
  const bool lcd_enable(true);
  const bool power_enable(true);
  const bool serial_enable(true);
  M5.begin(lcd_enable, power_enable, serial_enable);
  const int analog_port_button_pin(33);  // GPIO33
  const int ambient_light_pin(32);       // GPIO32
#endif
#ifdef M5STICKCPLUS
  const bool lcd_enable(true);
  const bool power_enable(true);
  const bool serial_enable(true);
  M5.begin(lcd_enable, power_enable, serial_enable);
  const int analog_port_button_pin(33);  // GPIO33
  const int ambient_light_pin(32);       // GPIO32
#endif
#ifdef M5ATOM
  const bool serial_enable(true);
  const bool i2c_enable(true);
  const bool display_enable(true);
  M5.begin(serial_enable, i2c_enable, display_enable);
  const int analog_port_button_pin(32);  // GPIO32
  const int ambient_light_pin(26);       // GPIO26 <Wi-Fi CANNOT BE USED>
#endif

  AdcButtonBegin(analog_port_button_pin);
  ambient_light_sensor.Begin(ambient_light_pin);

  loop_count = 0;
  last_ms = millis();
}

void loop()
{
  M5.update();
  AdcButtonUpdate();

  if (loop_count % (ambient_period_ms / loop_delay_ms) == 0) {
    int ambient_light = ambient_light_sensor.Read();
    Serial.printf("Ambient light sensor = %d\n", ambient_light);
  }

//  TestisPressed();
//  TestisReleased(0);
//  TestisReleased(1);
//  TestisReleased(2);
//  TestisReleased(3);
//  TestisReleased(4);
  TestwasPressed();
  TestwasReleased();
  TestpressedFor(1000);
//  TestreleasedFor(0, 3000);
//  TestreleasedFor(1, 3000);
//  TestreleasedFor(2, 3000);
//  TestreleasedFor(3, 3000);
//  TestreleasedFor(4, 3000);

  ++loop_count;
  delay(last_ms + loop_delay_ms - millis());
  last_ms = millis();
}
