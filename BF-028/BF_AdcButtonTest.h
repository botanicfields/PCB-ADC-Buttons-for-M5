// Copyright 2021 BotanicFields, Inc.
// BF-028: test of ADC Button
// test

#ifndef BF_ADC_BUTTON_TEST_H_INCLUDED
#define BF_ADC_BUTTON_TEST_H_INCLUDED

void TestisPressed();
void TestisReleased(int button);
void TestwasPressed();
void TestwasReleased();
void TestpressedFor(int ms);
void TestreleasedFor(int button, int ms);

#endif // BF_ADC_BUTTON_TEST_H_INCLUDED
