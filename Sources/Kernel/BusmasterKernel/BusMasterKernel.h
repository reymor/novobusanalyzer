#ifndef KERNEL_BUSMASTERKERNEL_BUSMASTERKERNEL_H_
#define KERNEL_BUSMASTERKERNEL_BUSMASTERKERNEL_H_

#include "BusmasterDriverInterface.h"
#include "IBMNetWorkService.h"
#include "IBusMasterKernel.h"

#include <Windows.h>

#include <memory>

class BusMasterKernel : public IBusMasterKernel {
 public:
  BusMasterKernel();
  virtual ~BusMasterKernel();
  HRESULT getBusService(ETYPE_BUS busType, IBusService** busService) override;
  HRESULT getDatabaseService(IBMNetWorkService** dbService) override;
  static std::shared_ptr<BusMasterKernel> create();

 private:
  pDIL_GetInterface mDIL_GetInterface;
  HMODULE mDriverLibrary;
  static std::shared_ptr<BusMasterKernel> mKernel;
  IBMNetWorkService* mBmNetworkService;

  bool loadDilInterface();
};

#endif  // KERNEL_BUSMASTERKERNEL_BUSMASTERKERNEL_H_