#ifndef BUSMASTER_APPLICATION_UI_IIDGENERATOR_H_
#define BUSMASTER_APPLICATION_UI_IIDGENERATOR_H_

#include <string>

class IIdGenerator {
public:
    IIdGenerator();
    virtual ~IIdGenerator();
    virtual int generateId(std::string, int& id) = 0;
    virtual bool removeid(std::string) = 0;
    virtual int setStartId(int mid) = 0;
};

#endif // BUSMASTER_APPLICATION_UI_IIDGENERATOR_H_
