#include "BusMasterKernel.h"

#include "BaseDIL_CAN.h"
#include "BaseDIL_FLEXRAY.h"
#include "BaseDIL_J1939.h"
#include "BaseDIL_LIN.h"
#include "BusMasterNetWork.h"

#include <memory>

#define defBusmaster_Dil_Dll_Name "BusmasterDriverInterface.dll"
#define defBusmaster_Dil_GetDil_Func "GetDilInterface"

std::shared_ptr<BusMasterKernel> BusMasterKernel::mKernel;

std::shared_ptr<BusMasterKernel> BusMasterKernel::create()
{
  if (mKernel == nullptr) {
    mKernel = std::make_shared<BusMasterKernel>();
  }
  return mKernel;
}

BusMasterKernel::BusMasterKernel() {
  mDIL_GetInterface = nullptr;
  mBmNetworkService = new BMNetwork();
  loadDilInterface();
}

BusMasterKernel::~BusMasterKernel() {}

HRESULT BusMasterKernel::getBusService(ETYPE_BUS busType, IBusService** busService) {
  if (nullptr != mDIL_GetInterface) {
    return mDIL_GetInterface(busType, busService);
  }
  return S_FALSE;
}

HRESULT BusMasterKernel::getDatabaseService(IBMNetWorkService** dbService) {
  *dbService = mBmNetworkService;
  return S_FALSE;
}

bool BusMasterKernel::loadDilInterface() {
  bool result = true;

  if (nullptr == mDIL_GetInterface) {
    mDIL_GetInterface = nullptr;
    mDriverLibrary = LoadLibrary(defBusmaster_Dil_Dll_Name);
    if (nullptr == mDriverLibrary) {
      result = false;
    }
    mDIL_GetInterface = (pDIL_GetInterface)GetProcAddress(mDriverLibrary, defBusmaster_Dil_GetDil_Func);
    if (nullptr == mDIL_GetInterface) {
      result = false;
    }
  }
  return result;
}

KERNEL_USAGEMODE HRESULT getBusmasterKernel(std::shared_ptr<IBusMasterKernel>& kernel) {
  kernel = BusMasterKernel::create();
  return S_OK;
}

KERNEL_USAGEMODE HRESULT DIL_GetInterface(ETYPE_BUS eBusType, void** ppvInterface)
{
  std::shared_ptr<IBusMasterKernel> kernel;
  getBusmasterKernel(kernel);
  if (nullptr != kernel) {
    IBusService* busService;
    kernel->getBusService(eBusType, &busService);

    HRESULT hResult = S_OK;

    switch (eBusType) {
      case CAN: {
        CBaseDIL_CAN* dil = (CBaseDIL_CAN*)busService;
        *ppvInterface = (void*)dil;
      } break;
      case LIN: {
        CBaseDIL_LIN* dil = (CBaseDIL_LIN*)busService;
        *ppvInterface = (void*)dil;
      } break;
      case MCNET:
        break;
      case J1939: {
        CBaseDILI_J1939* dil = (CBaseDILI_J1939*)busService;
        *ppvInterface = (void*)dil;
      } break;
      case FLEXRAY: {
        CBaseDIL_FLEXRAY* dil = (CBaseDIL_FLEXRAY*)busService;
        *ppvInterface = (void*)dil;
      } break;
      default: {
        hResult = S_FALSE;
      } break;
    }

    return hResult;
  }
  return S_FALSE;
}