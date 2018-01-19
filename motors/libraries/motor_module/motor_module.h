#ifndef MOTOR_MODULE_H
# define MOTOR_MODULE_H

# include <module.h>

class MotorModule : public Module
{
public:
    MotorModule(const String name, int freq, int pinENA, int pinENB, int pinPWM);
    virtual void on_receive(const String& message) override;
    virtual void tick() override;
private:
    bool speed_changed;
    int speed;
    int pinENA;
    int pinENB;
    int pinPWM;
};

#endif
