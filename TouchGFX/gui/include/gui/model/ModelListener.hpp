#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void info_SetDeviceSerialNum(char* str){}
    virtual void info_SetDeviceModelName(char* str){}
    virtual void info_SetDeviceAdminName(char* str){}
    virtual void info_SetDeviceGroup(char* str){}

    virtual void Network_SetListMax(int count){}
    virtual void Network_SetListData(int index,char *name,char *ip){}

    virtual void Process_SetListMax(int count){}
    virtual void Process_SetListInfo(int index,char *name,int val){}
    virtual void Process_SetCpuUsage(int val){}

    virtual void Storage_SetListMax(int count){}
    virtual void Storage_SetListInfo(int index,char *name,int val){}

    virtual void UtilRate_SetCpuUsage(int val){}
    virtual void UtilRate_SetMemoryUsage(int val){}
    virtual void UtilRate_SetDiskUsage(int val){}
    virtual void UtilRate_SetTotalCpuCore(int val){}
    virtual void UtilRate_SetTotalMemory(float val){}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
