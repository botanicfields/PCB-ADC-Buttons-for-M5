// Copyright 2021 BotanicFields, Inc.
// BF-028: Ambient Light Sensor and 5 Buttons of 3.3V Analog Signal and 5V Power 
//
// - Modification of JC_Button https://github.com/JChristensen/JC_Button
// - class Button --> class AdcButton
// - class ToggleButton --> not supported
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// class AdcButtonPort
//   Analog Digital Converter Port for 5 Buttons
// class ADCButton
//   buttons connected to the AdcButtonPort, can be used as the JC_Button
// instances
//   Begin and Update collectively, instead of individual read of AdcButton

#include "BF_AdcButton.h"

//..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8
void AdcButtonPort::Begin(int adc_pin)
{
  m_adc_pin = adc_pin;
}

void AdcButtonPort::Update()
{
  m_adc_read = analogRead(m_adc_pin);
//  AdcReadStable();  // use this instead of the line above to check the stability of analog read
//  AdcStatistics();  // for statistical analysis of analog reads
}

// The argument button specifies the button number instead of the GPIO number.
// Returns false when the button is pressed to be consistent with digitalRead().
//   button   Resistor    voltage ratio      95%    mV  105%   95%   ADC  105%       experimental
//   0  Right      0     0 /  3300 = 0               0..   0           0..   0 -->          0.. 200
//   1  Up      1000  1000 /  4300 = 0.233   729.. 767.. 806   905.. 952..1000      700.. 820..1100
//   2  Down    1000  2000 /  5300 = 0.377  1183..1245..1308  1468..1545..1623 --> 1300..1430..1700
//   3  Left    1500  3500 /  6800 = 0.515  1614..1699..1783  2002..2108..2213 --> 1900..2000..2300
//   4  Select  5100  8600 / 11900 = 0.723  2266..2385..2504  2811..2959..3107 --> 2700..2870..3100
//   -    -     3300                 1.0    3135..3300        3890..4095
bool AdcButtonPort::DigitalRead(int button)
{
  switch (button) {
    case 0: if (                     m_adc_read <  200) return false;  break;
    case 1: if (m_adc_read >  700 && m_adc_read < 1100) return false;  break;
    case 2: if (m_adc_read > 1300 && m_adc_read < 1700) return false;  break;
    case 3: if (m_adc_read > 1900 && m_adc_read < 2300) return false;  break;
    case 4: if (m_adc_read > 2700 && m_adc_read < 3100) return false;  break;
    default: break;
  }
  return true;
}

void AdcButtonPort::AdcReadStable()
{
  const int stable_range(50);    // range to judge stable
  const int loop_count_max(10);  // timeout to judge stable

  int adc_read1(m_adc_read_max);
  int loop_count(0);
  int adc_read_history[loop_count_max];
  while (true) {
    int adc_read2 = analogRead(m_adc_pin);
    adc_read_history[loop_count] = adc_read2;
    if (abs(adc_read1 - adc_read2) < stable_range)
      break;
    adc_read1 = adc_read2;

    if (++loop_count >= loop_count_max) {
      adc_read1 = m_adc_read_max;
      Serial.println("[ADC Read] Times over for stable");
      break;
    }
  }
  m_adc_read = adc_read1;

  if (m_adc_read != m_adc_read_max) {
    Serial.printf("[ADC Read] loop_count= %d: ", loop_count);
    for (int i = 0; i <= loop_count; ++i)
      Serial.printf("%d, ", adc_read_history[i]);
    Serial.printf("m_adc_read= %d\n", m_adc_read);
  }
}

void AdcButtonPort::AdcStatistics()
{
  const int     show_period(100);  // 100 times
  static int    adc_count(0);
  static int    adc_max(0);
  static int    adc_min(m_adc_read_max);
  static double adc_sum(0.0);
  static double adc_sq_sum(0.0);

  if (m_adc_read < m_adc_read_max) {
    ++adc_count;
    if (adc_max < m_adc_read) adc_max = m_adc_read;
    if (adc_min > m_adc_read) adc_min = m_adc_read;
    adc_sum += (double)m_adc_read;
    adc_sq_sum += (double)m_adc_read * (double)m_adc_read;

    if (adc_count % show_period == 0) {
      double adc_average = adc_sum / (double)adc_count;
      double adc_variance = (adc_sq_sum - adc_sum * adc_sum / (double)adc_count) / (double)adc_count;
      double adc_std_deviation = sqrt(adc_variance);
      Serial.printf("[ADC Read] n= %d, ave= %.4f  sdv= %.4f  min= %d  max= %d\n",
                    adc_count, adc_average, adc_std_deviation, adc_min, adc_max);
    }
  }
}

//..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8
// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

//[Adc]#include "JC_Button.h"

/*----------------------------------------------------------------------*
/ initialize a Button object and the pin it's connected to.             *
/-----------------------------------------------------------------------*/
//[Adc]void Button::begin()
void AdcButton::begin(AdcButtonPort* adc_btn)
{
    m_adc_btn = adc_btn;
//[Adc]    pinMode(m_pin, m_puEnable ? INPUT_PULLUP : INPUT);
//[Adc]    m_state = digitalRead(m_pin);
    m_state = m_adc_btn->DigitalRead(m_pin);
    if (m_invert) m_state = !m_state;
    m_time = millis();
    m_lastState = m_state;
    m_changed = false;
    m_lastChange = m_time;
}

/*----------------------------------------------------------------------*
/ returns the state of the button, true if pressed, false if released.  *
/ does debouncing, captures and maintains times, previous state, etc.   *
/-----------------------------------------------------------------------*/
//[Adc]bool Button::read()
bool AdcButton::read()
{
    uint32_t ms = millis();
//[Adc]    bool pinVal = digitalRead(m_pin);
    bool pinVal = m_adc_btn->DigitalRead(m_pin);
    if (m_invert) pinVal = !pinVal;
    if (ms - m_lastChange < m_dbTime)
    {
        m_changed = false;
    }
    else
    {
        m_lastState = m_state;
        m_state = pinVal;
        m_changed = (m_state != m_lastState);
        if (m_changed) m_lastChange = ms;
    }
    m_time = ms;
    return m_state;
}

/*----------------------------------------------------------------------*
 * isPressed() and isReleased() check the button state when it was last *
 * read, and return false (0) or true (!=0) accordingly.                *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
//[Adc]bool Button::isPressed()
bool AdcButton::isPressed()
{
    return m_state;
}

//[Adc]bool Button::isReleased()
bool AdcButton::isReleased()
{
    return !m_state;
}

/*----------------------------------------------------------------------*
 * wasPressed() and wasReleased() check the button state to see if it   *
 * changed between the last two reads and return false (0) or           *
 * true (!=0) accordingly.                                              *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
//[Adc]bool Button::wasPressed()
bool AdcButton::wasPressed()
{
    return m_state && m_changed;
}

//[Adc]bool Button::wasReleased()
bool AdcButton::wasReleased()
{
    return !m_state && m_changed;
}

/*----------------------------------------------------------------------*
 * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
 * pressed (or released), and has been in that state for the specified  *
 * time in milliseconds. Returns false (0) or true (!=0) accordingly.   *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
//[Adc]bool Button::pressedFor(uint32_t ms)
bool AdcButton::pressedFor(uint32_t ms)
{
    return m_state && m_time - m_lastChange >= ms;
}

//[Adc]bool Button::releasedFor(uint32_t ms)
bool AdcButton::releasedFor(uint32_t ms)
{
    return !m_state && m_time - m_lastChange >= ms;
}

/*----------------------------------------------------------------------*
 * lastChange() returns the time the button last changed state,         *
 * in milliseconds.                                                     *
 *----------------------------------------------------------------------*/
//[Adc]uint32_t Button::lastChange()
uint32_t AdcButton::lastChange()
{
    return m_lastChange;
}

//..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8
// instances
AmbientLightSensor ambient_light_sensor;

AdcButtonPort adc_btn;
AdcButton btn_right  = AdcButton(0);
AdcButton btn_up     = AdcButton(1);
AdcButton btn_down   = AdcButton(2);
AdcButton btn_left   = AdcButton(3);
AdcButton btn_select = AdcButton(4);

void AdcButtonBegin(int adc_pin)
{
  adc_btn.Begin(adc_pin);
  btn_right.begin(&adc_btn);
  btn_up.begin(&adc_btn);
  btn_down.begin(&adc_btn);
  btn_left.begin(&adc_btn);
  btn_select.begin(&adc_btn);
}

void AdcButtonUpdate()
{
  adc_btn.Update();
  btn_right.read();
  btn_up.read();
  btn_down.read();
  btn_left.read();
  btn_select.read();
}
