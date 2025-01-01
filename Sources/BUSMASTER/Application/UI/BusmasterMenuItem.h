#ifndef BUSMASTER_APPLICATION_UI_BUSMASTERMENUITEM_H_
#define BUSMASTER_APPLICATION_UI_BUSMASTERMENUITEM_H_

#include "IMenuInterface.h"
#include "MFCRibbonBarEx.h"

class BusmasterMenuItem : public IMenuItem {
private:
    CMFCRibbonButtonEx* mRibbonButton;
    CCmdUI* mMfcMenu;
public:
    BusmasterMenuItem(CMFCRibbonButtonEx*, CCmdUI* pMfcCmd);
    ~BusmasterMenuItem();
    void enableItem(bool);
    void checkItem(bool);
    void setName(char*);
    void getName(char*, int maxlength);
    void setImageIndex(int index, BOOL isLarge);
};

#endif // BUSMASTER_APPLICATION_UI_BUSMASTERMENUITEM_H_
