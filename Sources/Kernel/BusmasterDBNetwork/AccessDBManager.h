#ifndef KERNEL_BUSMASTERDBNETWORK_ACCESSDBMANAGER_H_
#define KERNEL_BUSMASTERDBNETWORK_ACCESSDBMANAGER_H_

#include <Windows.h>

#include <list>
#include <string>

#include "ICluster.h"


class AccessDBManager {
  typedef ERRORCODE (*PARSEDBFILE)(
      std::string strFileName, ETYPE_BUS clusterType,
      std::list<ClusterResult>& ouClusterResultList);
  typedef ERRORCODE (*FREECLUSTER)(ICluster*);
  HMODULE mDllHandle;
  bool mDbManagerAvailable;

 public:
  AccessDBManager();
  PARSEDBFILE mParseDbFile;
  FREECLUSTER mFreeCluster;
  bool isDbManagerAvailable();
  HRESULT LoadDbManager();
  void ReleaseDbmanager();
  ~AccessDBManager();
};

#endif  // KERNEL_BUSMASTERDBNETWORK_ACCESSDBMANAGER_H_