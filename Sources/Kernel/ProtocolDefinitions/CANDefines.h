#ifndef KERNEL_PROTOCOLDEFINITION_CANDEFINES_H_
#define KERNEL_PROTOCOLDEFINITION_CANDEFINES_H_

#include "IClusterProps.h"
#include "CommonDefines.h"
#include "CCompuMethod.h"

#define FRAMEFORMATE            2147483648
#define DEFAULT_DBC_IDENTIFIER  "Vector__XXX"

enum eCANMsgType {
    eCan_Standard,
    eCan_Extended
};

class CANFrameProps : public FrameProps {
public:
	CANFrameProps() {
		m_eProtocol = eProtocolType::eCANProtocol;
	}
    eCANMsgType m_canMsgType;
};

class CANCompuMethods : public CompuMethodProps {
public:
	CANCompuMethods() {
		this->m_eType = eCANProtocol;
	}
    CCompuMethod m_CompuMethod;
};

class CANSignalProps : public SignalProps {
public:
	CANSignalProps() {
		this->eType  = eCANProtocol;
	}
};

class CANEcuProperties : public EcuProperties {
public:
	eProtocolType m_eProtocol;

	CANEcuProperties() {
		m_eProtocol = eProtocolType::eCANProtocol;
	}
};

#endif // KERNEL_PROTOCOLDEFINITION_CANDEFINES_H_