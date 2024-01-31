#ifndef BUSMASTER_UTILITY_IDIRECTORYWATCHER_H_
#define BUSMASTER_UTILITY_IDIRECTORYWATCHER_H_

#include <string>
#include "Utils_stdafx.h"
#include "IDirectoryUpdate.h"

class IDirectoryWatcher
{
public:
    virtual HRESULT AddDirectoryWatch(std::string strDirName,IDirectoryUpdate* pIDirHdlr)=0;
    virtual HRESULT RemoveDirectoryWatch(std::string strDirName,IDirectoryUpdate* pIDirHdlr)=0;
};

#endif // BUSMASTER_UTILITY_IDIRECTORYWATCHER_H_