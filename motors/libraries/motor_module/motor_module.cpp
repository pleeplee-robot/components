#include <Arduino.h>
#include "motor_module.h"

MotorModule::MotorModule(const String name, int freq, int pinENA, int pinENB, int pinPWM)
    : Module(name, freq)
    , speed_changed(false)
    , speed(0)
    , pinENA(pinENA)
    , pinENB(pinENB)
    , pinPWM(pinPWM)
{
    pinMode(pinENA, OUTPUT);
    pinMode(pinENB, OUTPUT);
    pinMode(pinPWM, OUTPUT);
    digitalWrite(pinENA, LOW);
    digitalWrite(pinENB, LOW);
    digitalWrite(pinPWM, LOW);
}

void MotorModule::on_receive(const String& message)
{
    speed = message.toInt();
    if (speed < 0)
    {
        speed = -speed;
        digitalWrite(pinENA, LOW);
        digitalWrite(pinENB, HIGH);
        analogWrite(pinPWM, speed);
    }
    else if (speed > 0)
    {
        digitalWrite(pinENA, HIGH);
        digitalWrite(pinENB, LOW);
        analogWrite(pinPWM, speed);
    }
    else
        analogWrite(pinPWM, speed);
    speed_changed = true;
}

void MotorModule::tick()
{
/*    if (speed_changed)
    {
        speed_changed = false;
        analogWrite(pin, speed);
        send_message("OK");
    }*/
}
