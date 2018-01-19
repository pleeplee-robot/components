#ifndef DEBUG_MODULE_H
# define DEBUG_MODULE_H

# include <module.h>

class DebugModule : public Module
{
public:
    DebugModule(const String name, int freq);
    virtual void on_receive(const String& message) override;
    virtual void tick() override;
private:
    int val;
};

#endif
