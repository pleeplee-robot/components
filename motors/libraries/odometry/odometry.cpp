#include <Arduino.h>
#include "odometry.h"

OdometryModule::OdometryModule(const String name, int freq)
    : Module(name, freq)
    , line("")
    , ser(2, 444)
{
    ser.begin(9600);
    ser.setTimeout(50);
}

void OdometryModule::on_receive(const String& message)
{
}

void OdometryModule::tick()
{
    Module::tick();
    line = ser.readStringUntil('\n');
    if (line == "")
        return;
    send_message(line);
}
