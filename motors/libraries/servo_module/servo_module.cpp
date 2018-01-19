#include <Arduino.h>
#include <Servo.h>
#include "servo_module.h"

ServoModule::ServoModule(const String name, int freq, int pinPWM)
    : Module(name, freq)
    , servo()
    , changed(true)
    , angle(90)
    , pinPWM(pinPWM)
{
    pinMode(pinPWM, OUTPUT);
    servo.attach(pinPWM);
    servo.write(90);
}

void ServoModule::on_receive(const String& message)
{
    angle = message.toInt();
    changed = true;
}

void ServoModule::tick()
{
    if (changed) {
        servo.attach(pinPWM);
        servo.write(angle);
        delay(200);
        servo.detach();
        
    }
    changed = false;
}
