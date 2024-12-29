#ifndef BUSMASTER_APPLICATION_UI_UICREATOR_H_
#define BUSMASTER_APPLICATION_UI_UICREATOR_H_

#include <map>
#include <string>
#include <iostream>

#include "IUICreator.h"
#include "IMenuCreator.h"
#include "IIdgenerator.h"

struct UIElements {
    CMFCRibbonBar* mRibbonBar;
};

class UICreator:public IUICreator {
private :
    UIElements mUiElements;
    IMenuCreator* mMenucreator = nullptr;
    IIdGenerator* mIdgenerator;
    std::map<std::string, std::list<RibbonButton>> mPluginMenuList;
public:

    UICreator(UICreator::UIElements, IIdGenerator*);
    ~UICreator();
	int Create(std::map<std::string, std::list<RibbonButton>> populatelist);
    int getPluginMenuInfo(unsigned int id, std::string& pluginId, std::string& actualMenuId);
    int CreateToolbar(CImageList* imagelist, std::list<ToolButton> path);
};

#endif // BUSMASTER_APPLICATION_UI_UICREATOR_H_
