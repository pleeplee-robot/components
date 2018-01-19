#include <Arduino.h>
#include "debug_module.h"

DebugModule::DebugModule(const String name, int freq)
    : Module(name, freq)
    , val(HIGH)
{}

void DebugModule::on_receive(const String& message)
{
    int speed = message.toInt();
    val = speed ? HIGH : LOW;
    send_message(message);
}

void DebugModule::tick()
{
    Module::tick();
    digitalWrite(13, val);
}
