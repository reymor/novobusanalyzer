#ifndef BUSMASTER_APPLICATION_IBUSMASTERBUSPLUGIN_H_
#define BUSMASTER_APPLICATION_IBUSMASTERBUSPLUGIN_H_

#include "ProtocolsDefinitions.h"
#include "IBMNetWorkService.h"
#include "IBusService.h"
#include "BaseDefs.h"
#include "IMenuInterface.h"
#include "IBusmasterPlugin.h"

class IBusmasterBusPlugin {
public:
	IBusmasterBusPlugin(){};
	virtual ETYPE_BUS getBusType() = 0;
	virtual IBusService* getBusService() = 0;
    virtual void setBusmasterInterface(IBusmasterBusPluginInterface*) = 0;
    virtual ESTATUS_BUS getBusStatus() = 0;
    virtual void getMenuInterface(IMenuInterface**) = 0;
    virtual void getConfiguration(xmlNodePtr& pNodePtr) = 0;            //TODO
    virtual void setConfiguration(const xmlDocPtr) = 0;            //TODO
	virtual void closureOperations() = 0;
    
	virtual ~IBusmasterBusPlugin(){};
};

#endif // BUSMASTER_APPLICATION_IBUSMASTERBUSPLUGIN_H_
