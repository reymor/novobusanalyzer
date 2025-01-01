#ifndef BUSMASTER_APPLICATION_UI_IMENUCREATOR_H_
#define BUSMASTER_APPLICATION_UI_IMENUCREATOR_H_

#include "IIdGenerator.h"
#include "Menus.h"

#include <map>
#include <string>
#include <iostream>

typedef std::list<RibbonButton> pluginMenuList;

class IMenuCreator {
public:
    virtual ~IMenuCreator() {};
	virtual void populateRibbonBar(CMFCRibbonBar* mainMenu, std::map<std::string, pluginMenuList> menulist, IIdGenerator* idgenerator) = 0;
    virtual void getPluginMenuInfo(unsigned int id, std::string& pluginId, std::string& actualMenuId) = 0;
};

#endif // BUSMASTER_APPLICATION_UI_IMENUCREATOR_H_
