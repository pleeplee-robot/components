#ifndef MODULE_H
# define MODULE_H

# include <Arduino.h>

class Module
{
public:
    Module(const String name, int freq);
    virtual void on_receive(const String& message) = 0;
    virtual void tick();
    long next_time();
    const String get_name();
    int get_freq();
private:
    const String name;
    int freq;
    int last_time;
protected:
    void send_message(const String& message);
};

#endif
