#ifndef KERNEL_BUSMASTERKERNEL_IBUSMASTERKERNEL_H_
#define KERNEL_BUSMASTERKERNEL_IBUSMASTERKERNEL_H_

#include "IBMNetWorkService.h"
#include "IBusService.h"
#include "ProtocolsDefinitions.h"

#include <memory>

class IBusMasterKernel {
 public:
  virtual ~IBusMasterKernel() {};
  virtual HRESULT getBusService(ETYPE_BUS busType, IBusService** busService) = 0;
  virtual HRESULT getDatabaseService(IBMNetWorkService** dbService) = 0;
};

#if defined BUSMASTERKERNEL_EXPORTS
#define KERNEL_USAGEMODE __declspec(dllexport)
#else
#define KERNEL_USAGEMODE __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

KERNEL_USAGEMODE HRESULT getBusmasterKernel(std::shared_ptr<IBusMasterKernel>&);
KERNEL_USAGEMODE HRESULT DIL_GetInterface(ETYPE_BUS eBusType, void** ppvInterface);

#ifdef __cplusplus
}
#endif

#endif  // KERNEL_BUSMASTERKERNEL_IBUSMASTERKERNEL_H_