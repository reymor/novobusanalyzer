#ifndef BUSMASTER_APPLICATION_UI_IDGENERATOR_H_
#define BUSMASTER_APPLICATION_UI_IDGENERATOR_H_

#include "Menus.h"
#include "IIdGenerator.h"

#include <map>

static std::map <std::string, int> menuidlist;
class IdGenerator :public IIdGenerator {
public:
    int generateId(std::string, int& id);
	bool removeid(std::string);
    int setStartId(int mid);
	std::string GetMenuItem(UINT id, std::map<std::string, std::list<RibbonButton>>);
private:
    int mCurrentId;

};

#endif // BUSMASTER_APPLICATION_UI_IDGENERATOR_H_
