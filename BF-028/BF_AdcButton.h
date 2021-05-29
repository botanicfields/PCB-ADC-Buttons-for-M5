// Copyright 2021 BotanicFields, Inc.
// BF-028: Ambient Light Sensor and 5 Buttons of 3.3V Analog Signal and 5V Power 
//
// - Modification of JC_Button https://github.com/JChristensen/JC_Button
// - class Button --> class AdcButton
// - class ToggleButton --> not supported
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// class ADCButtonPort: Analog Digital Converter Port for 5 Buttons
//   Begein and Update collectively, instead of individual read of JC_Button
// class ADCButton: 5 Buttons connected to the Analog Signal Port
//   can be used as the JC_Button
// class AmbientLightSensor: Analog Read of Ambient Light Sensor

#ifndef BF_ADC_BUTTON_H_INCLUDED
#define BF_ADC_BUTTON_H_INCLUDED

#include <Arduino.h>

//..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8
class AmbientLightSensor {
 public:
  AmbientLightSensor() : m_als_pin(0) {}
  void Begin(int als_pin) { m_als_pin = als_pin; }
  int Read() { return analogRead(m_als_pin); }
//  int Read() { return analogReadMilliVolts(m_als_pin); }
 private:
  int m_als_pin;
};

//..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8
class AdcButtonPort {
 public:
  AdcButtonPort()
    : m_adc_read(m_adc_read_max), m_adc_pin(0) {}
  void Begin(int adc_pin);
  void Update();
  bool DigitalRead(int button);
 private:
  const int m_adc_read_max = 4095;
  int m_adc_read;
  int m_adc_pin;
  void AdcReadStable();
  void AdcStatistics();
};

//..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8
// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

//[Adc] #ifndef JC_BUTTON_H_INCLUDED
//[Adc] #define JC_BUTTON_H_INCLUDED

//[Adc] #include <Arduino.h>

//[Adc] class Button
class AdcButton
{
    public:
        // Button(pin, dbTime, puEnable, invert) instantiates a button object.
        //
        // Required parameter:
        // pin      The Arduino pin the button is connected to
        //
        // Optional parameters:
        // dbTime   Debounce time in milliseconds (default 25ms)
        // puEnable true to enable the AVR internal pullup resistor (default true)
        // invert   true to interpret a low logic level as pressed (default true)
//[Adc]        Button(uint8_t pin, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true)
//[Adc]            : m_pin(pin), m_dbTime(dbTime), m_puEnable(puEnable), m_invert(invert) {}
        AdcButton(uint8_t pin, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true)
            : m_pin(pin), m_dbTime(dbTime), m_puEnable(puEnable), m_invert(invert) {}

        // Initialize a Button object and the pin it's connected to
//[Adc]        void begin();
        void begin(AdcButtonPort* adc_btn);

        // Returns the current debounced button state, true for pressed,
        // false for released. Call this function frequently to ensure
        // the sketch is responsive to user input.
        bool read();

        // Returns true if the button state was pressed at the last call to read().
        // Does not cause the button to be read.
        bool isPressed();

        // Returns true if the button state was released at the last call to read().
        // Does not cause the button to be read.
        bool isReleased();

        // Returns true if the button state at the last call to read() was pressed,
        // and this was a change since the previous read.
        bool wasPressed();

        // Returns true if the button state at the last call to read() was released,
        // and this was a change since the previous read.
        bool wasReleased();

        // Returns true if the button state at the last call to read() was pressed,
        // and has been in that state for at least the given number of milliseconds.
        bool pressedFor(uint32_t ms);

        // Returns true if the button state at the last call to read() was released,
        // and has been in that state for at least the given number of milliseconds.
        bool releasedFor(uint32_t ms);

        // Returns the time in milliseconds (from millis) that the button last
        // changed state.
        uint32_t lastChange();

    private:
        uint8_t m_pin;          // arduino pin number connected to button
        uint32_t m_dbTime;      // debounce time (ms)
        bool m_puEnable;        // internal pullup resistor enabled
        bool m_invert;          // if true, interpret logic low as pressed, else interpret logic high as pressed
        bool m_state;           // current button state, true=pressed
        bool m_lastState;       // previous button state
        bool m_changed;         // state changed since last read
        uint32_t m_time;        // time of current state (ms from millis)
        uint32_t m_lastChange;  // time of last state change (ms)

        AdcButtonPort* m_adc_btn;  // for Adc_button
};

// a derived class for a "push-on, push-off" (toggle) type button.
//[Adc]class ToggleButton : public Button
//[Adc]#endif

//..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8
// instances
extern AmbientLightSensor ambient_light_sensor;

extern AdcButtonPort adc_btn;

extern AdcButton btn_right;
extern AdcButton btn_up;
extern AdcButton btn_down;
extern AdcButton btn_left;
extern AdcButton btn_select;

void AdcButtonBegin(int adc_pin);
void AdcButtonUpdate();

#endif // BF_ADC_BUTTON_H_INCLUDED
