#include <list.h>
#include <odometry.h>
#include <motor_module.h>
#include <servo_module.h>

#include <Servo.h>

List<Module*>* modules = nullptr;

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(10);
    modules = new List<Module*>(new OdometryModule("odometry", 100));
    modules->push_back(new MotorModule("motor1", 100, 12, 13, 11));
    modules->push_back(new MotorModule("motor2", 100, A1, A0, 3));
    modules->push_back(new MotorModule("motor3", 100, 10, 4, 6));
    modules->push_back(new MotorModule("motor4", 100, 7, 8, 5));
    modules->push_back(new ServoModule("servo", 100, 9));
}

Module* get_module_by_name(List<Module*>* modules, String& name)
{
    list_for_each(modules)
    {
        if ((*modules->get_elem())->get_name() == name)
            return *modules->get_elem();
    }
    return nullptr;
}

void loop() {
    String str = "";
    while (1)
    {
        List<Module*>* l = modules;
        list_for_each(l)
        {
            (*l->get_elem())->tick();
        }
        if (Serial.available())
        {
            str.concat(Serial.readString());
        }
        if (str != "")
        {
            int line_id = str.indexOf('\n');
            if (line_id == -1)
                continue;
            String line = str.substring(0, line_id);
            str = str.substring(line_id + 1);
            int colon_idx = line.indexOf(':');
            String module_name = line.substring(0, colon_idx);
            String msg = line.substring(colon_idx + 1);
            Module *module = get_module_by_name(modules, module_name);
            if (module) {
                module->on_receive(msg);
            }
        }
    }
}
