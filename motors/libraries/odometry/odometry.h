#ifndef ODOMETRY_H
# define ODOMETRY_H

# include <module.h>
# include <SoftwareSerial.h>

class OdometryModule : public Module
{
public:
    OdometryModule(const String name, int freq);
    virtual void on_receive(const String& message) override;
    virtual void tick() override;
private:
    String line;
    SoftwareSerial ser;
};

#endif
