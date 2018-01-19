#include "module.h"

Module::Module(const String name, int freq)
    : name(name)
    , freq(freq)
    , last_time(0)
{}

void Module::tick()
{
    last_time = millis();
}

long Module::next_time()
{
    return last_time + freq;
}

void Module::send_message(const String& message)
{
    Serial.print(name);
    Serial.print(":");
    Serial.println(message);
}

const String Module::get_name()
{
    return name;
}

int Module::get_freq()
{
    return freq;
}
