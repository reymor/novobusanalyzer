#ifndef BUSMASTER_APPLICATION_UI_IUICREATOR_H_
#define BUSMASTER_APPLICATION_UI_IUICREATOR_H_

#include "Menus.h"

#include <map>
#include <list>
#include <string>
#include <iostream>

class IUICreator {
public:
    virtual ~IUICreator() {};
	virtual int Create(std::map<std::string, std::list<RibbonButton>> populatelist) = 0;
    virtual int getPluginMenuInfo(unsigned int id, std::string& pluginId, std::string& actualMenuId) = 0;
};

#endif // BUSMASTER_APPLICATION_UI_IUICREATOR_H_
