// Copyright 2021 BotanicFields, Inc.
// BF-028: test of ADC Button
// test

#include "BF_AdcButton.h"
#include "BF_AdcButtonTest.h"

void TestisPressed()
{
  if (btn_right.isPressed())  { Serial.printf("[AdcButton Test] Right  is Pressed, last change = %dms\n", btn_right.lastChange());  }
  if (btn_up.isPressed())     { Serial.printf("[AdcButton Test] Up     is Pressed, last change = %dms\n", btn_up.lastChange());     }
  if (btn_down.isPressed())   { Serial.printf("[AdcButton Test] Down   is Pressed, last change = %dms\n", btn_down.lastChange());   }
  if (btn_left.isPressed())   { Serial.printf("[AdcButton Test] Left   is Pressed, last change = %dms\n", btn_left.lastChange());   }
  if (btn_select.isPressed()) { Serial.printf("[AdcButton Test] Select is Pressed, last change = %dms\n", btn_select.lastChange()); }
}

void TestisReleased(int button)
{
  switch (button) {
    case 0: if (btn_right.isReleased())  { Serial.printf("[AdcButton Test] Right  is Released, last change = %dms\n", btn_right.lastChange());  } break;
    case 1: if (btn_up.isReleased())     { Serial.printf("[AdcButton Test] Up     is Released, last change = %dms\n", btn_up.lastChange());     } break;
    case 2: if (btn_down.isReleased())   { Serial.printf("[AdcButton Test] Down   is Released, last change = %dms\n", btn_down.lastChange());   } break;
    case 3: if (btn_left.isReleased())   { Serial.printf("[AdcButton Test] Left   is Released, last change = %dms\n", btn_left.lastChange());   } break;
    case 4: if (btn_select.isReleased()) { Serial.printf("[AdcButton Test] Select is Released, last change = %dms\n", btn_select.lastChange()); } break;
    default: break;
  }
}

void TestwasPressed()
{
  if (btn_right.wasPressed())  { Serial.printf("[AdcButton Test] Right  was Pressed, last change = %dms\n", btn_right.lastChange());  }
  if (btn_up.wasPressed())     { Serial.printf("[AdcButton Test] Up     was Pressed, last change = %dms\n", btn_up.lastChange());     }
  if (btn_down.wasPressed())   { Serial.printf("[AdcButton Test] Down   was Pressed, last change = %dms\n", btn_down.lastChange());   }
  if (btn_left.wasPressed())   { Serial.printf("[AdcButton Test] Left   was Pressed, last change = %dms\n", btn_left.lastChange());   }
  if (btn_select.wasPressed()) { Serial.printf("[AdcButton Test] Select was Pressed, last change = %dms\n", btn_select.lastChange()); }
}

void TestwasReleased()
{
  if (btn_right.wasReleased())  { Serial.printf("[AdcButton Test] Right  was Released, last change = %dms\n", btn_right.lastChange());  }
  if (btn_up.wasReleased())     { Serial.printf("[AdcButton Test] Up     was Released, last change = %dms\n", btn_up.lastChange());     }
  if (btn_down.wasReleased())   { Serial.printf("[AdcButton Test] Down   was Released, last change = %dms\n", btn_down.lastChange());   }
  if (btn_left.wasReleased())   { Serial.printf("[AdcButton Test] Left   was Released, last change = %dms\n", btn_left.lastChange());   }
  if (btn_select.wasReleased()) { Serial.printf("[AdcButton Test] Select was Released, last change = %dms\n", btn_select.lastChange()); }
 }

void TestpressedFor(int ms)
{
  if(btn_right.pressedFor(ms))  { Serial.printf("[AdcButton Test] Right  pressed For %dms, last change = %dms\n", ms, btn_right.lastChange());  }
  if(btn_up.pressedFor(ms))     { Serial.printf("[AdcButton Test] Up     pressed For %dms, last change = %dms\n", ms, btn_up.lastChange());     }
  if(btn_down.pressedFor(ms))   { Serial.printf("[AdcButton Test] Down   pressed For %dms, last change = %dms\n", ms, btn_down.lastChange());   }
  if(btn_left.pressedFor(ms))   { Serial.printf("[AdcButton Test] Left   pressed For %dms, last change = %dms\n", ms, btn_left.lastChange());   }
  if(btn_select.pressedFor(ms)) { Serial.printf("[AdcButton Test] Select pressed For %dms, last change = %dms\n", ms, btn_select.lastChange()); }
}

void TestreleasedFor(int button, int ms)
{
  switch (button) {
    case 0: if (btn_right.releasedFor(ms))  { Serial.printf("[AdcButton Test] Right  released For %dms, last change = %dms\n", ms, btn_right.lastChange());  } break;
    case 1: if (btn_up.releasedFor(ms))     { Serial.printf("[AdcButton Test] Up     released For %dms, last change = %dms\n", ms, btn_up.lastChange());     } break;
    case 2: if (btn_down.releasedFor(ms))   { Serial.printf("[AdcButton Test] Down   released For %dms, last change = %dms\n", ms, btn_down.lastChange());   } break;
    case 3: if (btn_left.releasedFor(ms))   { Serial.printf("[AdcButton Test] Left   released For %dms, last change = %dms\n", ms, btn_left.lastChange());   } break;
    case 4: if (btn_select.releasedFor(ms)) { Serial.printf("[AdcButton Test] Select released For %dms, last change = %dms\n", ms, btn_select.lastChange()); } break;
    default: break;
  }
}
