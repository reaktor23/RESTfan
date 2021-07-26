#include "esphome.h"
using namespace esphome;

#define FAN_SPEED_1 5
#define FAN_SPEED_2 4
#define FAN_SPEED_3 0

class RestFanOutput : public Component, public FloatOutput {
  public:
    void write_state(float state) override {
      if (state < 0.3) {
        // OFF
        digitalWrite(FAN_SPEED_1, LOW);
        digitalWrite(FAN_SPEED_2, LOW);
        digitalWrite(FAN_SPEED_3, LOW);
      } else if (state < 0.6) {
        // low speed
        digitalWrite(FAN_SPEED_2, LOW);
        digitalWrite(FAN_SPEED_3, LOW);
        delay(100); // Delay to give relays time to switch off
        digitalWrite(FAN_SPEED_1, HIGH);
      } else if (state < 0.9) {
        // medium speed
        digitalWrite(FAN_SPEED_1, LOW);
        digitalWrite(FAN_SPEED_3, LOW);
        delay(100); // Delay to give relays time to switch off
        digitalWrite(FAN_SPEED_2, HIGH);
      } else {
        // high speed
        digitalWrite(FAN_SPEED_1, LOW);
        digitalWrite(FAN_SPEED_2, LOW);
        delay(100); // Delay to give relays time to switch off
        digitalWrite(FAN_SPEED_3, HIGH);
      }
    }
};
