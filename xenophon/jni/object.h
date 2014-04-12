#ifndef _BEATPAD_OBJECT
#define _BEATPAD_OBJECT

#include <string>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class object_t
{
protected:
    std::string _name;
    SLObjectItf _object;

public:
    object_t(std::string name) : _name(name) {};
    explicit object_t(std::string name, SLObjectItf object) : _name(name), _object(object) {};
    ~object_t();

    SLObjectItf &object();

    void realize();
};

#endif