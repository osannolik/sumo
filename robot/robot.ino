#include <Wire.h>
#include "sensors.h"
#include "motors.h"
#include "communication.h"


#define AN_BATTERY               A0

#define AN_FR_LEFT_SENSOR        A6
#define AN_FR_MID_SENSOR         A3
#define AN_FR_RIGHT_SENSOR       A2
#define AN_LEFT_SENSOR           A7
#define AN_RIGHT_SENSOR          A1

#define DIG_FR_RIGHT_GROUND_SENSOR  2
#define DIG_FR_LEFT_GROUND_SENSOR   3
#define DIG_FR_BACK_GROUND_SENSOR   7

#define LEFT_MOTORS_FORWARD      6
#define LEFT_MOTORS_BACKWARD     5

#define RIGHT_MOTORS_FORWARD     9
#define RIGHT_MOTORS_BACKWARD    10

#define START                    4
#define STATUS_LED               8

//Macros
#define TOGGLE_STATUS_LED        PORTB ^= 1

bool armed = false;


void setup() {

  Serial.begin(115200);

  Wire.begin();

  pinMode(AN_FR_LEFT_SENSOR, INPUT);
  pinMode(AN_FR_MID_SENSOR, INPUT);
  pinMode(AN_FR_RIGHT_SENSOR, INPUT);
  pinMode(AN_LEFT_SENSOR, INPUT);
  pinMode(AN_RIGHT_SENSOR, INPUT);

  pinMode(DIG_FR_RIGHT_GROUND_SENSOR, INPUT);
  pinMode(DIG_FR_LEFT_GROUND_SENSOR, INPUT);
  pinMode(DIG_FR_BACK_GROUND_SENSOR, INPUT);

  pinMode(LEFT_MOTORS_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTORS_FORWARD, OUTPUT);
  pinMode(LEFT_MOTORS_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTORS_BACKWARD, OUTPUT);

  pinMode(STATUS_LED, OUTPUT);
  
  pinMode(START, INPUT);

  digitalWrite(STATUS_LED, 0);
}

void loop()
{
  TOGGLE_STATUS_LED;
    
  const int dt = 5;

  /* Check for motor control commands */
  static parser_t p;
  static int m_cnt = 0;
  const  int m_period = 50;

  m_cnt += dt;
  if (m_cnt >= m_period) {
    m_cnt = 0;
    motor_cmd_t cmd;
    if (get_motor_command(&p, &cmd)) {
      set_motors(cmd);
    }
  }

  /* Sample sensors and send sensor values */
  static int s_cnt = 0;
  const  int s_period = 20;

  s_cnt += dt;
  if (s_cnt >= s_period) {
    s_cnt = 0;
    sensor_data_t sensors;
    read_sensors(&sensors);
    send_sensor_data(sensors);
  }
  
  delay(dt);
}
