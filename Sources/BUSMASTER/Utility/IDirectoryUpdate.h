#ifndef BUSMASTER_UTILITY_IDIRECTORYUPDATE_H_
#define BUSMASTER_UTILITY_IDIRECTORYUPDATE_H_

#include <string>
#include "Utils_stdafx.h"

class IDirectoryUpdate
{
public:
    virtual void OnFileChanged(const std::string strFileName,DWORD dwAction)=0;
};

#endif // BUSMASTER_UTILITY_IDIRECTORYUPDATE_H_