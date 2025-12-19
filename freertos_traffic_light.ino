#include <Arduino_FreeRTOS.h>
#include <task.h>

#define RED_LED     8
#define YELLOW_LED  9
#define GREEN_LED   10

typedef enum {
  STATE_RED,
  STATE_GREEN,
  STATE_YELLOW
} traffic_state_t;

traffic_state_t trafficState = STATE_RED;

void TrafficLightTask(void *pvParameters);

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  xTaskCreate(
    TrafficLightTask,
    "TrafficLight",
    128,
    NULL,
    1,
    NULL
  );

  vTaskStartScheduler();
}

void loop() {
}

void TrafficLightTask(void *pvParameters) {
  TickType_t lastWakeTime = xTaskGetTickCount();

  for (;;) {
    switch (trafficState) {

      case STATE_RED:
        digitalWrite(RED_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        trafficState = STATE_GREEN;
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(5000));
        break;

      case STATE_GREEN:
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        trafficState = STATE_YELLOW;
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(5000));
        break;

      case STATE_YELLOW:
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, HIGH);
        trafficState = STATE_RED;
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(2000));
        break;
    }
  }
}
