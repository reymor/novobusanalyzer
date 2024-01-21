#ifndef KERNEL_BUSMASTERKERNEL_BUSMASTERKERNEL_H_
#define KERNEL_BUSMASTERKERNEL_BUSMASTERKERNEL_H_
#include <Windows.h>

#include "BusmasterDriverInterface.h"
#include "IBMNetWorkService.h"
#include "IBusMasterKernel.h"

class BusMasterKernel : public IBusMasterKernel {
  pDIL_GetInterface mDIL_GetInterface;
  HMODULE mDriverLibrary;
  static BusMasterKernel* mKernel;
  IBMNetWorkService* mBmNetworkService;

 public:
  BusMasterKernel();
  virtual ~BusMasterKernel();
  HRESULT getBusService(ETYPE_BUS busType, IBusService** busService);
  HRESULT getDatabaseService(IBMNetWorkService** dbService);
  static BusMasterKernel* create();

 private:
  bool loadDilInterface();
};

#endif  // KERNEL_BUSMASTERKERNEL_BUSMASTERKERNEL_H_