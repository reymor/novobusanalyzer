#ifndef BUSMASTER_UTILITY_IFILELINEANALYSISFILTER_H_
#define BUSMASTER_UTILITY_IFILELINEANALYSISFILTER_H_

#include <string.h>

class IFileLineAnalysisFilter
{
public:
    virtual HRESULT AnalyseLine(std::string strLine,const unsigned long& nLineNo) = 0;
};

#endif // BUSMASTER_UTILITY_IFILELINEANALYSISFILTER_H_