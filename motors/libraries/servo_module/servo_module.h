#ifndef SERVO_MODULE_H
# define SERVO_MODULE_H

# include <module.h>
# include <Servo.h>

class ServoModule : public Module
{
public:
    ServoModule(const String name, int freq, int pinPWM);
    virtual void on_receive(const String& message) override;
    virtual void tick() override;
private:
    Servo servo;
    bool changed;
    int angle;
    int pinPWM;
};

#endif
