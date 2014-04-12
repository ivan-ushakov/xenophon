#include "object.h"

#include "log.h"
#include "common.h"

object_t::~object_t()
{
    LOGI("destroing %s object...", _name.c_str());

    if (_object != NULL)
        (*_object)->Destroy(_object);
}

SLObjectItf &object_t::object()
{
    return _object;
}

void object_t::realize()
{
    SLresult result = (*_object)->Realize(_object, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS)
    {
        LOGE("fail to realize object");
        throw sl_exception(result);
    }    
}
