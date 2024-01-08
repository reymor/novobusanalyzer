// CAN_RUSOKU.cpp : Defines the initialization routines for the DLL.
//


#include "CAN_RUSOKU_stdafx.h"
#include "CAN_RUSOKU.h"
#include "canal.h"
#include "BaseDIL_CAN_Controller.h"
#include "DILPluginHelperDefs.h"
#include "CAN_RUSOKU_Extern.h"
#include "Utility/Utility_Thread.h"

#define USAGE_EXPORT

BEGIN_MESSAGE_MAP(CCANRUSOKUApp, CWinApp)
END_MESSAGE_MAP()


CCANRUSOKUApp::CCANRUSOKUApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCANRUSOKUApp object

CCANRUSOKUApp theApp;

/********************************************************************************************************************************************************************/

#define MAX_BUFF_ALLOWED 16

typedef struct tagAckMap
{
    UINT m_MsgID;
    UINT m_ClientID;
    UINT m_Channel;

    BOOL operator == (const tagAckMap& RefObj)const
    {
        return ((m_MsgID == RefObj.m_MsgID) && (m_Channel == RefObj.m_Channel));
    }
} SACK_MAP;

static CRITICAL_SECTION sg_CritSectForAckBuf;       // To make it thread safe

typedef std::list<SACK_MAP> CACK_MAP_LIST;
static CACK_MAP_LIST sg_asAckMapBuf;

static int nWriteMessage(STCAN_MSG sMessage, DWORD /*dwClientID*/);
void vMarkEntryIntoMap(const SACK_MAP& RefObj);
BOOL bRemoveMapEntry(const SACK_MAP& RefObj, UINT& ClientID);
static void vWriteIntoClientsBuffer(STCANDATA& sCanData);
DWORD WINAPI CanMsgReadThreadProc_CAN_Rusoku_CAN(LPVOID pVoid);

/**
 * Client and Client Buffer map
 */
typedef struct tagClientBufMap
{
    DWORD dwClientID;
    BYTE hClientHandle;
//  typedef CBaseMsgBufFSE<STCANDATA> CBaseCANBufFSE;
//  CBaseMsgBufFSE<STCANDATA> *m_pClientBuf[MAX_BUFF_ALLOWED];
    CBaseCANBufFSE* pClientBuf[MAX_BUFF_ALLOWED];
    char pacClientName[MAX_PATH];
    UINT unBufCount;

    tagClientBufMap()
    {
        dwClientID = 0;
        hClientHandle = 0;
        unBufCount = 0;
        memset(pacClientName, 0, sizeof(char) * MAX_PATH);
        for (int i = 0; i < MAX_BUFF_ALLOWED; i++)
        {
            pClientBuf[i] = nullptr;
        }

    }
} SCLIENTBUFMAP;


#define MAX_CLIENT_ALLOWED 16
static SCLIENTBUFMAP sg_asClientToBufMap[MAX_CLIENT_ALLOWED];
static UINT sg_unClientCnt = 0;
std::string sg_acErrStr = "";

static UINT sg_nNoOfChannels = 0;
static UINT sg_ucNoOfHardware = 0;

static CPARAM_THREADPROC sg_sParmRThread;

//CANAL
canal_dev_list sg_nCanDevList;

static STCANDATA sg_asCANMsg;
static STCAN_MSG sg_ReadMsg;
static SCONTROLLER_DETAILS sg_ControllerDetails[defNO_OF_CHANNELS];
static INTERFACE_HW sg_HardwareIntr[defNO_OF_CHANNELS];

static CChannel sg_aodChannels[defNO_OF_CHANNELS];
static INT sg_anSelectedItems[CHANNEL_ALLOWED];

/* Forward declarations*/
static BOOL bRemoveClient(DWORD dwClientId);
static DWORD dwGetAvailableClientSlot();
static BOOL bClientExist(std::string pcClientName, INT& Index);
static BOOL bClientIdExist(const DWORD& dwClientId);
static BOOL bGetClientObj(DWORD dwClientID, UINT& unClientIndex);
static void vRetrieveAndLog(DWORD /*dwErrorCode*/, char* File, int Line);
static BOOL bIsBufferExists(const SCLIENTBUFMAP& sClientObj, const CBaseCANBufFSE* pBuf);
static BOOL bRemoveClientBuffer(CBaseCANBufFSE* RootBufferArray[MAX_BUFF_ALLOWED], UINT& unCount, CBaseCANBufFSE* BufferToRemove);

/********************************************************************************************************************************************/

class CDIL_CAN_RUSOKU : public CBaseDIL_CAN_Controller
{
public:
    /* STARTS IMPLEMENTATION OF THE INTERFACE FUNCTIONS... */
    HRESULT CAN_PerformInitOperations(void);
    HRESULT CAN_PerformClosureOperations(void);
    HRESULT CAN_GetTimeModeMapping(SYSTEMTIME& CurrSysTime, UINT64& TimeStamp, LARGE_INTEGER& QueryTickCount);
    HRESULT CAN_ListHwInterfaces(INTERFACE_HW_LIST& sSelHwInterface, INT& nCount, PSCONTROLLER_DETAILS);
    HRESULT CAN_SelectHwInterface(const INTERFACE_HW_LIST& sSelHwInterface, INT nCount);
    HRESULT CAN_DeselectHwInterface(void);
    HRESULT CAN_SetConfigData(PSCONTROLLER_DETAILS ConfigFile, int Length);
    HRESULT CAN_StartHardware(void);
    HRESULT CAN_StopHardware(void);
    HRESULT CAN_GetCurrStatus(STATUSMSG& StatusData);
    HRESULT CAN_GetTxMsgBuffer(BYTE*& pouFlxTxMsgBuffer);
    HRESULT CAN_SendMsg(DWORD dwClientID, const STCAN_MSG& sCanTxMsg);
    HRESULT CAN_GetBusConfigInfo(BYTE* BusInfo);
    HRESULT CAN_GetLastErrorString(std::string& acErrorStr);
    HRESULT CAN_GetControllerParams(LONG& lParam, UINT nChannel, ECONTR_PARAM eContrParam);
    HRESULT CAN_SetControllerParams(int nValue, ECONTR_PARAM eContrparam);
    HRESULT CAN_GetErrorCount(SERROR_CNT& sErrorCnt, UINT nChannel, ECONTR_PARAM eContrParam);

    // Specific function set
    HRESULT CAN_SetAppParams(HWND hWndOwner);
    HRESULT CAN_ManageMsgBuf(BYTE bAction, DWORD ClientID, CBaseCANBufFSE* pBufObj);
    HRESULT CAN_RegisterClient(BOOL bRegister, DWORD& ClientID, char* pacClientName);
    HRESULT CAN_GetCntrlStatus(const HANDLE& hEvent, UINT& unCntrlStatus);
    HRESULT CAN_LoadDriverLibrary(void);
    HRESULT CAN_UnloadDriverLibrary(void);
    HRESULT CAN_SetHardwareChannel(PSCONTROLLER_DETAILS, DWORD dwDriverId, bool bIsHardwareListed, unsigned int unChannelCount);
};

/**
 * Starts code for the state machine
 */
enum
{
    STATE_DRIVER_SELECTED = 0x0,
    STATE_HW_INTERFACE_LISTED,
    STATE_HW_INTERFACE_SELECTED,
    STATE_CONNECTED
};

static BYTE sg_bCurrState = STATE_DRIVER_SELECTED;

static FILE* fp; //GS
static HWND sg_hOwnerWnd = nullptr;

// Timestamps
static SYSTEMTIME sg_CurrSysTime;
static UINT64 sg_TimeStamp = 0;
/**
 * Query Tick Count
 */
static LARGE_INTEGER sg_QueryTickCount;
static LARGE_INTEGER sg_lnFrequency;

enum
{
    CREATE_MAP_TIMESTAMP = 0x1,
    CALC_TIMESTAMP_READY = 0x2,
};

/**
 * Current state machine
 */
static BYTE sg_byCurrState = CREATE_MAP_TIMESTAMP;

BOOL CCANRUSOKUApp::InitInstance()
{
	CWinApp::InitInstance();

//    AllocConsole();
    //freopen_s(&fp, "CONIN$", "r", stdin);
//    freopen_s(&fp, "CONOUT$", "w", stdout);
    //freopen_s(&fp, "CONOUT$", "w", stderr);

	return TRUE;
}

/**
 * CCANRUSOKUApp deinitialization
 */
BOOL CCANRUSOKUApp::ExitInstance()
{
    CWinApp::ExitInstance();

//    fclose(fp);
//    FreeConsole();

    return TRUE;
}

CDIL_CAN_RUSOKU* g_pouDIL_CAN_RUSOKU = nullptr;

/**
 * \return S_OK for success, S_FALSE for failure
 *
 * Returns the interface to controller
 */
HRESULT GetIDIL_CAN_Controller(void** ppvInterface)
{
    HRESULT hResult;

    hResult = S_OK;
    if (!g_pouDIL_CAN_RUSOKU)
    {
        g_pouDIL_CAN_RUSOKU = new CDIL_CAN_RUSOKU;
        if (!(g_pouDIL_CAN_RUSOKU))
        {
            hResult = S_FALSE;
        }
    }
    *ppvInterface = (void*)g_pouDIL_CAN_RUSOKU;  /* Doesn't matter even if g_pouDIL_CAN_RUSOKU is null */

    return hResult;
}

// global var
static CRITICAL_SECTION sg_DIL_CriticalSection;

/**
* \brief         Performs intial operations.
*                Initializes filter, queue, controller config with default values.
* \param         void
* \return        S_OK if the open driver call successfull otherwise S_FALSE
*/
HRESULT CDIL_CAN_RUSOKU::CAN_PerformInitOperations(void)
{
    printf("CDIL_CAN_RUSOKU::CAN_PerformInitOperations()\n");

    /* Create critical section for ensuring thread
    safeness of read message function */
    //InitializeCriticalSection(&sg_DIL_CriticalSection);
    /* Register Monitor client */
    DWORD dwClientID = 0;

    printf("call---->CDIL_CAN_RUSOKU::CAN_RegisterClient(REGISTER_CLIENT, dwClientID = 0, CAN_MONITOR)\n");
    HRESULT hResult = S_FALSE;

    if (CAN_RegisterClient(TRUE, dwClientID, CAN_MONITOR_NODE) == S_OK)
    {
        //Initialize the selected channel items array to -1
        for (UINT i = 0; i < CHANNEL_ALLOWED; i++)
        {
            sg_anSelectedItems[i] = -1;
        }

        hResult = S_OK;
    }

    return hResult;
}

/**
* \brief         Performs closure operations.
* \param         void
* \return        S_OK if the CAN_StopHardware call successfull otherwise S_FALSE
*/
HRESULT CDIL_CAN_RUSOKU::CAN_PerformClosureOperations(void)
{
    printf("CDIL_CAN_RUSOKU::CAN_PerformClosureOperations()\n");

    HRESULT hResult = S_OK;

    hResult = CAN_StopHardware();

    UINT ClientIndex = 0;
    while (sg_unClientCnt > 0)
    {
        bRemoveClient(sg_asClientToBufMap[ClientIndex].dwClientID);
    }

    if (hResult == S_OK)
    {
        sg_bCurrState = STATE_DRIVER_SELECTED;
    }

    return hResult;
}

/**
* \brief         Gets the time mode mapping of the hardware. CurrSysTime
*                will be updated with the system time ref.
*                TimeStamp will be updated with the corresponding timestamp.
* \param[out]    CurrSysTime, is SYSTEMTIME structure
* \param[out]    TimeStamp, is UINT64
* \param[out]    QueryTickCount, is LARGE_INTEGER
* \return        S_OK for success
*/
HRESULT CDIL_CAN_RUSOKU::CAN_GetTimeModeMapping(SYSTEMTIME& CurrSysTime, UINT64& TimeStamp, LARGE_INTEGER& QueryTickCount)
{
    //(void)CurrSysTime;

    printf("CDIL_CAN_RUSOKU::CAN_GetTimeModeMapping()\n");

    CurrSysTime = sg_CurrSysTime;
    TimeStamp = sg_TimeStamp;
    QueryTickCount = sg_QueryTickCount;

    return S_OK;
}

/**
* \brief         Lists the hardware interface available.
* \param[out]    asSelHwInterface, is INTERFACE_HW_LIST structure
* \param[out]    nCount , is INT contains the selected channel count.
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_ListHwInterfaces(INTERFACE_HW_LIST& asSelHwInterface, INT& nCount, PSCONTROLLER_DETAILS InitData)
{
    USES_CONVERSION;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    printf("CDIL_CAN_RUSOKU::CAN_ListHwInterfaces\n");

    char buff[256];
    char serialNr[256];
    static BOOL bInit = 1;
    std::string chBuffer;
    INT32 dll_version;
   
    if (CANAL_ERROR_SUCCESS != CanalGetDeviceList(&sg_nCanDevList, 8))    
        return HW_INTERFACE_NO_SEL;
    
    nCount = sg_nCanDevList.canDevCount;
    
    // Get Hardware Network Map
    for (int nIndex = 0; nIndex < nCount; nIndex++)
    {
        chBuffer.append("RUSOKU TouCAN s/n:");
        sg_HardwareIntr[nIndex].m_dwIdInterface = nIndex; //1   Interface number
        chBuffer.append(sg_nCanDevList.canDevInfo[nIndex].SerialNumber);
        sg_HardwareIntr[nIndex].m_acDescription = chBuffer.c_str(); //2   Description
        chBuffer.clear();
        dll_version = CanalGetDllVersion();
        sprintf_s(buff,sizeof(buff)/sizeof(buff[0]),"v.%d.%d.%d", (char)dll_version, (char)(dll_version >>8), (char)(dll_version >>16));
        sg_HardwareIntr[nIndex].m_acDeviceName = buff; //3  Firmware version
        sg_HardwareIntr[nIndex].m_acAdditionalInfo = sg_nCanDevList.canDevInfo[nIndex].SerialNumber; //4  Serial number GS
    }

    CWnd objMainWnd;
    objMainWnd.Attach(sg_hOwnerWnd);

    IChangeRegisters* pAdvancedSettings = new _RCAN_cfg();
    CHardwareListingCAN HwList(sg_HardwareIntr, nCount, sg_anSelectedItems, CAN, CHANNEL_ALLOWED, &objMainWnd, InitData, pAdvancedSettings);

    INT nRet = HwList.DoModal();
    objMainWnd.Detach();

    if (nRet == IDOK)
    {
        nCount = sg_nNoOfChannels;
        nCount = HwList.nGetSelectedList(sg_anSelectedItems);

        sg_nNoOfChannels = nCount;
        sg_ucNoOfHardware = nCount;        

        //Reorder hardware interface as per the user selection
        for (int nCount = 0; nCount < sg_ucNoOfHardware; nCount++)
        {
            if (sg_anSelectedItems[nCount] != -1)
            {
                sg_aodChannels[nCount].m_nChannel = sg_HardwareIntr[sg_anSelectedItems[nCount]].m_dwIdInterface;
                strcpy(sg_aodChannels[nCount].m_strSerialNumber, sg_HardwareIntr[sg_anSelectedItems[nCount]].m_acAdditionalInfo.c_str()); //GS kopijuojam serial number
            }
        }

        for (unsigned int unChannel = 0; unChannel < nCount; unChannel++)        
        {
            sprintf(sg_aodChannels[unChannel].m_strName, sg_HardwareIntr[unChannel].m_acDescription.c_str());
            asSelHwInterface[unChannel].m_acNameInterface = sg_HardwareIntr[unChannel].m_acDescription;
        }

        sg_bCurrState = STATE_HW_INTERFACE_LISTED;
        return S_OK;
    }
    else
    {
        return HW_INTERFACE_NO_SEL;
    }
}

/**
* \brief         Selects the hardware interface selected by the user.
* \param[out]    asSelHwInterface, is INTERFACE_HW_LIST structure
* \param[out]    nCount , is INT contains the selected channel count.
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_SelectHwInterface(const INTERFACE_HW_LIST& asSelHwInterface, INT /*nCount*/)
{
    USES_CONVERSION;
    VALIDATE_VALUE_RETURN_VAL(sg_bCurrState, STATE_HW_INTERFACE_LISTED, ERR_IMPROPER_STATE);

    printf("CDIL_CAN_RUSOKU::CAN_SelectHwInterface: sg_ucNoOfHardware %d)\n", sg_ucNoOfHardware);

    /* Check for the success */
    sg_bCurrState = STATE_HW_INTERFACE_SELECTED;
    for (UINT nCount = 0; nCount < sg_ucNoOfHardware; nCount++)
    {
        sg_ControllerDetails[nCount].m_omHardwareDesc = asSelHwInterface[nCount].m_acNameInterface;
    }

    return S_OK;
}

/**
* \brief         Deselects the selected hardware interface.
* \param         void
* \return        S_OK if CAN_ResetHardware call is success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_DeselectHwInterface(void)
{
    printf("CDIL_CAN_VSCOM::CAN_DeselectHwInterface()\n");

    sg_bCurrState = STATE_HW_INTERFACE_LISTED;

    return S_OK;
}

/**
* \brief         Sets the controller configuration data supplied by ConfigFile.
* \param[in]     ConfigFile, is SCONTROLLER_DETAILS structure
* \param[in]     Length , is INT
* \return        S_OK for success
*/
HRESULT CDIL_CAN_RUSOKU::CAN_SetConfigData(PSCONTROLLER_DETAILS ConfigFile, int Length)
{
    printf("CDIL_CAN_RUSOKU::CAN_SetConfigData\n");

    VALIDATE_VALUE_RETURN_VAL(sg_bCurrState, STATE_HW_INTERFACE_SELECTED, ERR_IMPROPER_STATE);

    USES_CONVERSION;

    /* Fill the hardware description details */
    for (UINT nCount = 0; nCount < sg_ucNoOfHardware; nCount++)
    {
        ((PSCONTROLLER_DETAILS)ConfigFile)[sg_anSelectedItems[nCount]].m_omHardwareDesc = sg_aodChannels[nCount].m_strName;
    }

    for (int i = 0; i < Length; i++)
    {
        sg_ControllerDetails[i] = ConfigFile[sg_anSelectedItems[i]];
    }

    return S_OK;    
}

/**
* \brief         connects to the channels and initiates read thread.
* \param         void
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_StartHardware(void)
{
    std::string chInitStr;
    ULONG   res;
    HRESULT hResult = S_OK;

    USES_CONVERSION;

    printf("CDIL_CAN_RUSOKU::CAN_StartHardware()\n");

    for (UINT i = 0; i < sg_nNoOfChannels; i++)
    {
        chInitStr.append("0;");
        chInitStr.append(sg_aodChannels[i].m_strSerialNumber);
        chInitStr.append(";");
        chInitStr.append(sg_ControllerDetails[i].m_omStrBaudrate.c_str());
        chInitStr.erase(chInitStr.end()-3, chInitStr.end());

        //res = CanalOpen(chInitStr.c_str(), (0x00000100U | 0x00000010U)); // enable status messages
        //res = CanalOpen(chInitStr.c_str(), 0x00000100U); // enable status messages
        res = CanalOpen(chInitStr.c_str(), 0);

        if (res <= 0){
            hResult = ERR_LOAD_HW_INTERFACE;
            return hResult;
        }

        sg_aodChannels[i].m_hnd = res;        
        chInitStr.clear();
    }

    //If everything is ok start the read thread
    if (hResult == S_OK)
    {
        if (sg_sParmRThread.bStartThread(CanMsgReadThreadProc_CAN_Rusoku_CAN))
        {
            hResult = S_OK;            
            sg_bCurrState = STATE_CONNECTED;
            InitializeCriticalSection(&sg_CritSectForAckBuf);

            //TimeModeMapping
            GetLocalTime(&sg_CurrSysTime);  

            sg_byCurrState = CREATE_MAP_TIMESTAMP;

            QueryPerformanceCounter(&sg_QueryTickCount);
            // Get frequency of the performance counter
            QueryPerformanceFrequency(&sg_lnFrequency);
            // Convert it to time stamp with the granularity of hundreds of microsecond
            if ((sg_QueryTickCount.QuadPart * 10000) > sg_lnFrequency.QuadPart)
            {
                sg_TimeStamp = (sg_QueryTickCount.QuadPart * 10000) / sg_lnFrequency.QuadPart;
            }
            else
            {
                sg_TimeStamp = (sg_QueryTickCount.QuadPart / sg_lnFrequency.QuadPart) * 10000;
            }
        }
    }

    return hResult;
}

/**
* \brief         Stops the controller.
* \param         void
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_StopHardware(void)
{
    printf("CDIL_CAN_RUSOKU::CAN_StopHardware\n");

    sg_sParmRThread.bTerminateThread();

    for (UINT i = 0; i < sg_nNoOfChannels; i++)
    {
        if (sg_aodChannels[i].m_hnd != NULL) {
            CanalClose(sg_aodChannels[i].m_hnd); 
            sg_aodChannels[i].m_hnd = NULL;
        }                   
    }

    DeleteCriticalSection(&sg_CritSectForAckBuf);

    return S_OK;
}

/**
* \brief         Function to get Controller status
* \param[out]    StatusData, is s_STATUSMSG structure
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_GetCurrStatus(STATUSMSG& StatusData)
{
    return S_OK;
}

/**
* \brief         Gets the Tx queue configured.
* \param[out]    pouFlxTxMsgBuffer, is BYTE*
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_GetTxMsgBuffer(BYTE*& /*pouFlxTxMsgBuffer*/)
{
    return S_OK;
}

/**
* \brief         Sends STCAN_MSG structure from the client dwClientID.
* \param[in]     dwClientID is the client ID
* \param[in]     sMessage is the application specific CAN message structure
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_SendMsg(DWORD dwClientID, const STCAN_MSG& sCanTxMsg)
{
    VALIDATE_VALUE_RETURN_VAL(sg_bCurrState, STATE_CONNECTED, ERR_IMPROPER_STATE);

    printf("CDIL_CAN_RUSOKU::CAN_SendMsg()\n");

    EnterCriticalSection(&sg_CritSectForAckBuf); // Lock the buffer
    static SACK_MAP sAckMap;
    HRESULT hResult = S_FALSE;
    if (bClientIdExist(dwClientID))
    {
        if (sCanTxMsg.m_ucChannel <= sg_nNoOfChannels)
        {
            sAckMap.m_ClientID = dwClientID;
            sAckMap.m_MsgID = sCanTxMsg.m_unMsgID;
            sAckMap.m_Channel = sCanTxMsg.m_ucChannel;

            /* Mark an entry in Map. This is helpful to identify
               which client has been sent this message in later stage */
            vMarkEntryIntoMap(sAckMap);  /*sg_asAckMapBuf.push_back(RefObj);*/
            if (nWriteMessage(sCanTxMsg, dwClientID) == S_OK)
            {
                hResult = S_OK;
            }
        }
        else
        {
            hResult = ERR_INVALID_CHANNEL;
        }
    }
    else
    {
        hResult = ERR_NO_CLIENT_EXIST;
    }
    LeaveCriticalSection(&sg_CritSectForAckBuf); // Unlock the buffer

    return hResult;
}

/**
* \brief         This will send a CAN message to the driver.
* \param[in]     sMessage Message to Transmit
* \return        Operation Result. 0 incase of no errors. Failure Error codes otherwise.
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static int nWriteMessage(STCAN_MSG sMessage, DWORD /*dwClientID*/)
{
    int    status = -1;
    canalMsg CanalMsg = {0};

    if ((sMessage.m_ucChannel > 0) &&
        (sMessage.m_ucChannel <= sg_nNoOfChannels) &&
        (sg_nNoOfChannels <= defNO_OF_CHANNELS))
    {
        /* if it is an extended frame */
        if (sMessage.m_ucEXTENDED == 1)
        {
            CanalMsg.flags |= CANAL_IDFLAG_EXTENDED;
        }
        /* in case of remote frame */
        if (sMessage.m_ucRTR == 1)
        {
            CanalMsg.flags |= CANAL_IDFLAG_RTR;
        }

        CanalMsg.id = sMessage.m_unMsgID;
        CanalMsg.sizeData = sMessage.m_ucDataLen;
        memcpy(CanalMsg.data, sMessage.m_ucData, 8);

        //Transmit message
        status = CanalSend(sg_aodChannels[sMessage.m_ucChannel - 1].m_hnd, &CanalMsg);
    }

    return status;
}


/**
* \brief         Function to store the Tx message entry into sg_asAckMapBuf list.
* \param[in]     RefObj, is SACK_MAP entry
* \return        void
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
void vMarkEntryIntoMap(const SACK_MAP& RefObj)
{
    //EnterCriticalSection(&sg_CritSectForAckBuf); // Lock the buffer
    sg_asAckMapBuf.push_back(RefObj);
    //LeaveCriticalSection(&sg_CritSectForAckBuf); // Unlock the buffer
}

/**
* \brief         Function to retreive the Tx message entry from sg_asAckMapBuf list and delete.
*                Also returns the respective client ID.
* \param[in]     RefObj, is SACK_MAP entry to find and delete
* \param[out]    ClientID, is client ID of the RefObj found
* \return        TRUE if RefObj is found, else FALSE
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
BOOL bRemoveMapEntry(const SACK_MAP& RefObj, UINT& ClientID)
{
    EnterCriticalSection(&sg_CritSectForAckBuf); // Lock the buffer
    BOOL bResult = FALSE;

    
    CACK_MAP_LIST::iterator  iResult = std::find(sg_asAckMapBuf.begin(), sg_asAckMapBuf.end(), RefObj);

    if (iResult != sg_asAckMapBuf.end())
    {
        bResult = TRUE;
        ClientID = (*iResult).m_ClientID;
        sg_asAckMapBuf.erase(iResult);
    }
    
    LeaveCriticalSection(&sg_CritSectForAckBuf); // Unlock the buffer
    return bResult;
}

/**
* \brief         Writes the message 'sCanData' to the corresponding clients buffer
* \param[out]    sCanData, is STCANDATA structure
* \return        void
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static void vWriteIntoClientsBuffer(STCANDATA& sCanData)
{
    //Write into the client's buffer and Increment message Count
    static SACK_MAP sAckMap;
    UINT ClientId = 0;
    static UINT Index = (UINT)-1;
    sAckMap.m_Channel = sCanData.m_uDataInfo.m_sCANMsg.m_ucChannel;
    sAckMap.m_MsgID = sCanData.m_uDataInfo.m_sCANMsg.m_unMsgID;

    //Check if it is an acknowledgement message
    if (bRemoveMapEntry(sAckMap, ClientId))
    {
        BOOL bClientExists = bGetClientObj(ClientId, Index);

        for (UINT i = 0; i < sg_unClientCnt; i++)
        {
            //Tx for sender node
            if (/*(i == CAN_MONITOR_NODE_INDEX)  ||*/ (bClientExists && (i == Index)))
            {
                sCanData.m_ucDataType = TX_FLAG;
                for (UINT j = 0; j < sg_asClientToBufMap[i].unBufCount; j++)
                {
                    sg_asClientToBufMap[i].pClientBuf[j]->WriteIntoBuffer(&sCanData);
                }
            }
            else
            {
                //Send the other nodes as Rx.
                for (UINT j = 0; j < sg_asClientToBufMap[i].unBufCount; j++)
                {
                    static STCANDATA sTempCanData;
                    sTempCanData = sCanData;
                    sTempCanData.m_ucDataType = RX_FLAG;
                    sg_asClientToBufMap[i].pClientBuf[j]->WriteIntoBuffer(&sTempCanData);
                }
            }
        }
    }
    else // provide it to everybody
    {        
        for (UINT i = 0; i < sg_unClientCnt; i++)
        {
            for (UINT j = 0; j < sg_asClientToBufMap[i].unBufCount; j++)
            {
                sg_asClientToBufMap[i].pClientBuf[j]->WriteIntoBuffer(&sCanData);
            }
        }
    }
}

/**
* \brief         Gets bus config info.
* \param[out]    BusInfo, is BYTE
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_GetBusConfigInfo(BYTE* /*BusInfo*/)
{
    return S_OK;
}

/**
* \brief         Gets last occured error and puts inside acErrorStr.
* \param[out]    acErrorStr, is CHAR contains error string
* \param[in]     nLength, is INT
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_GetLastErrorString(std::string& /* acErrorStr */)
{
    return WARN_DUMMY_API;
}

/**
* \brief         Gets the controller parametes of the channel based on the request.
* \param[out]    lParam, the value of the controller parameter requested.
* \param[in]     nChannel, indicates channel ID
* \param[in]     eContrParam, indicates controller parameter
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_GetControllerParams(LONG& lParam, UINT nChannel, ECONTR_PARAM eContrParam)
{
    HRESULT hResult = S_OK;

    if ((sg_bCurrState == STATE_HW_INTERFACE_SELECTED) || (sg_bCurrState == STATE_CONNECTED))
    {
        switch (eContrParam)
        {
        case NUMBER_HW:
        {
            lParam = sg_nNoOfChannels;
        }
        break;
        case NUMBER_CONNECTED_HW:
        {
            lParam = sg_nNoOfChannels;
        }
        break;
        case DRIVER_STATUS:
        {
            lParam = true;
        }
        break;
        default:
        {
            hResult = S_FALSE;
        }
        break;
        }
    }
    return hResult;
}

/**
* \brief         Set the controller parametes of the channel based on the request.
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_SetControllerParams(int /* nValue */, ECONTR_PARAM /* eContrparam */)
{
    return S_OK;
}

/**
* \brief         Gets the error counter for corresponding channel.
* \param[out]    sErrorCnt, is SERROR_CNT structure
* \param[in]     nChannel, indicates channel ID
* \param[in]     eContrParam, indicates controller parameter
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_RUSOKU::CAN_GetErrorCount(SERROR_CNT& sErrorCnt, UINT nChannel, ECONTR_PARAM eContrParam)
{
    HRESULT hResult = S_OK;
    if ((sg_bCurrState == STATE_CONNECTED) || (sg_bCurrState == STATE_HW_INTERFACE_SELECTED))
    {
        if (nChannel <= sg_nNoOfChannels)
        {
            if (eContrParam == ERR_CNT)
            {
                sErrorCnt.m_ucTxErrCount = sg_aodChannels[nChannel - 1].m_ucTxErrorCounter;
                sErrorCnt.m_ucRxErrCount = sg_aodChannels[nChannel - 1].m_ucRxErrorCounter;
            }
        }
        else
        {
            hResult = ERR_INVALID_CHANNEL;
        }
    }
    else
    {
        hResult = ERR_IMPROPER_STATE;
    }
    return hResult;
}

//Specific function set

/**
 * \return S_OK for success, S_FALSE for failure
 *
 * Sets the application params.
 */
HRESULT CDIL_CAN_RUSOKU::CAN_SetAppParams(HWND hWndOwner)
{
    printf("CDIL_CAN_RUSOKU::CAN_SetAppParams(hWndOwner = 08%X)\n", hWndOwner);

    sg_hOwnerWnd = hWndOwner;

    printf("     call: CDIL_CAN_RUSOKU::CAN_ManageMsgBuf(MSGBUF_CLEAR, 0, nullptr);\n");

    /* Initialise both the time parameters */
    GetLocalTime(&sg_CurrSysTime);
    sg_TimeStamp = 0x0;

    //Query Tick Count
    sg_QueryTickCount.QuadPart = 0;

    CDIL_CAN_RUSOKU::CAN_ManageMsgBuf(MSGBUF_CLEAR, 0, nullptr);
    return S_OK;
}

/**
 * \return S_OK for success, S_FALSE for failure
 *
 * Registers the buffer pBufObj to the client ClientID
 * 
 */
HRESULT CDIL_CAN_RUSOKU::CAN_ManageMsgBuf(BYTE bAction, DWORD ClientID, CBaseCANBufFSE* pBufObj)
{
    if (bAction == MSGBUF_ADD)
        printf("CDIL_CAN_RUSOKU::CAN_ManageMsgBuf(MSGBUF_ADD, ClientID=%d, pBufObj=0x%04X)\n", ClientID, pBufObj);
    else if (bAction == MSGBUF_CLEAR)
        printf("CDIL_CAN_RUSOKU::CAN_ManageMsgBuf(MSGBUF_CLEAR, ClientID=%d, pBufObj=0x%04X)\n", ClientID, pBufObj);

    HRESULT hResult = S_FALSE;
    if (ClientID != 0)
    {
        UINT unClientIndex;
        if (bGetClientObj(ClientID, unClientIndex))
        {
            SCLIENTBUFMAP& sClientObj = sg_asClientToBufMap[unClientIndex];
            if (bAction == MSGBUF_ADD)
            {
                /* Add msg buffer */
                if (pBufObj != nullptr)
                {
                    if (sClientObj.unBufCount < MAX_BUFF_ALLOWED)
                    {
                        if (bIsBufferExists(sClientObj, pBufObj) == FALSE)
                        {
                            sClientObj.pClientBuf[sClientObj.unBufCount++] = pBufObj;
                            hResult = S_OK;
                        }
                        else
                        {
                            hResult = ERR_BUFFER_EXISTS;
                        }
                    }
                }
            }
            else if (bAction == MSGBUF_CLEAR)
            {
                /* clear msg buffer */
                if (pBufObj != nullptr)
                {
                    /* Remove only buffer mentioned */
                    bRemoveClientBuffer(sClientObj.pClientBuf, sClientObj.unBufCount, pBufObj);
                }
                else
                {
                    /* Remove all */
                    for (UINT i = 0; i < sClientObj.unBufCount; i++)
                    {
                        sClientObj.pClientBuf[i] = nullptr;
                    }
                    sClientObj.unBufCount = 0;
                }
                hResult = S_OK;
            }
        }
        else
        {
            hResult = ERR_NO_CLIENT_EXIST;
        }
    }
    else
    {
        if (bAction == MSGBUF_CLEAR)
        {
            /* clear msg buffer */
            for (UINT i = 0; i < sg_unClientCnt; i++)
            {
                CAN_ManageMsgBuf(MSGBUF_CLEAR, sg_asClientToBufMap[i].dwClientID, nullptr);
            }
            hResult = S_OK;
        }
    }

    if(hResult == S_OK)
        printf("     hResult = S_OK;\n");
    else if(hResult == ERR_NO_CLIENT_EXIST)
        printf("     hResult = ERR_NO_CLIENT_EXIST;\n");
    else if(hResult == ERR_BUFFER_EXISTS)
        printf("     hResult = ERR_BUFFER_EXISTS;\n");
    else 
        printf("     hResult = S_FALSE;\n");

    return hResult;
}


/**
 * \return S_OK for success, S_FALSE for failure
 *
 * Registers a client to the DIL. ClientID will have client id
 * which will be used for further client related calls
 */
HRESULT CDIL_CAN_RUSOKU::CAN_RegisterClient(BOOL bRegister, DWORD& ClientID, char* pacClientName)
{
    if (bRegister == 1)
        printf("CDIL_CAN_RUSOKU::CAN_RegisterClient(REGISTER_CLIENT, ClientID=%d, pacClientName=%s\n", ClientID, pacClientName);
    else
        printf("CDIL_CAN_RUSOKU::CAN_RegisterClient(REMOVE_CLIENT, ClientID=%d, pacClientName=%s\n", ClientID, pacClientName);

    //return S_OK;

    USES_CONVERSION;
    HRESULT hResult = S_FALSE;

    if (bRegister)
    {
        if (sg_unClientCnt < MAX_CLIENT_ALLOWED)
        {
            INT Index = 0;
            if (!bClientExist(pacClientName, Index))
            {
                /* Currently store the client information */
                if (_tcscmp(pacClientName, CAN_MONITOR_NODE) == 0)
                {
                    /* First slot is reserved to monitor node */
                    ClientID = 1;
                    _tcscpy(sg_asClientToBufMap[0].pacClientName, pacClientName);
                    sg_asClientToBufMap[0].dwClientID = ClientID;
                    sg_asClientToBufMap[0].unBufCount = 0;
                }
                else
                {
                    /*if (!bClientExist(CAN_MONITOR_NODE, Index))
                    {
                        Index = sg_unClientCnt + 1;
                    }
                    else
                    {
                        Index = sg_unClientCnt;
                    }*/
                    Index = sg_unClientCnt;
                    ClientID = dwGetAvailableClientSlot();
                    _tcscpy(sg_asClientToBufMap[Index].pacClientName, pacClientName);

                    sg_asClientToBufMap[Index].dwClientID = ClientID;
                    sg_asClientToBufMap[Index].unBufCount = 0;
                }
                sg_unClientCnt++;
                hResult = S_OK;
            }
            else
            {
                ClientID = sg_asClientToBufMap[Index].dwClientID;
                hResult = ERR_CLIENT_EXISTS;
            }
        }
        else
        {
            hResult = ERR_NO_MORE_CLIENT_ALLOWED;
        }
    }
    else
    {
        if (bRemoveClient(ClientID))
        {
            hResult = S_OK;
        }
        else
        {
            hResult = ERR_NO_CLIENT_EXIST;
        }
    }

    return hResult;
}

/**
 * \return S_OK for success, S_FALSE for failure
 *
 * Returns the controller status. hEvent will be registered
 * and will be set whenever there is change in the controller
 * status.
 */
HRESULT CDIL_CAN_RUSOKU::CAN_GetCntrlStatus(const HANDLE& hEvent, UINT& unCntrlStatus)
{
    return S_OK;
}

/**
 * \return S_OK for success, S_FALSE for failure
 *
 * Loads BOA related libraries. Updates BOA API pointers
 */
HRESULT CDIL_CAN_RUSOKU::CAN_LoadDriverLibrary(void)
{
    printf("CDIL_CAN_RUSOKU::CAN_LoadDriverLibrary()\n");

    return S_OK;
}

/**
 * \return S_OK for success, S_FALSE for failure
 *
 * Unloads the driver library.
 */
HRESULT CDIL_CAN_RUSOKU::CAN_UnloadDriverLibrary(void)
{
    printf("CDIL_CAN_RUSOKU::CAN_UnloadDriverLibrary()\n");

    return S_OK;
}

HRESULT CDIL_CAN_RUSOKU::CAN_SetHardwareChannel(PSCONTROLLER_DETAILS ouControllerDetails, DWORD dwDriverId, bool bIsHardwareListed, unsigned int unChannelCount)
{
    //nenaudojamas

    printf("CDIL_CAN_RUSOKU::CAN_SetHardwareChannel()\n");

    for (UINT i = 0; i < CHANNEL_ALLOWED; i++)
    {
        sg_anSelectedItems[i] = -1;
    }

    return S_OK;
}


/**
* \brief         This function will remove the existing client ID
* \param[in]     dwClientId, client ID to be removed
* \return        Returns TRUE if client ID removal is success, else FALSE
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static BOOL bRemoveClient(DWORD dwClientId)
{
    BOOL bResult = FALSE;
    if (sg_unClientCnt > 0)
    {
        UINT unClientIndex = (UINT)-1;
        if (bGetClientObj(dwClientId, unClientIndex))
        {
            /* clear the client first */
            if (sg_asClientToBufMap[unClientIndex].hClientHandle != 0)
            {
                HRESULT hResult = S_OK;//(*pfCAN_RemoveClient)(sg_asClientToBufMap[unClientIndex].hClientHandle);
                if (hResult == S_OK)
                {
                    sg_asClientToBufMap[unClientIndex].dwClientID = 0;
                    sg_asClientToBufMap[unClientIndex].hClientHandle = 0;
                    memset(sg_asClientToBufMap[unClientIndex].pacClientName, 0, sizeof(char) * MAX_PATH);
                    for (int i = 0; i < MAX_BUFF_ALLOWED; i++)
                    {
                        sg_asClientToBufMap[unClientIndex].pClientBuf[i] = nullptr;
                    }
                    sg_asClientToBufMap[unClientIndex].unBufCount = 0;
                    bResult = TRUE;
                }
                else
                {
                    vRetrieveAndLog(hResult, __FILE__, __LINE__);
                }
            }
            else
            {
                sg_asClientToBufMap[unClientIndex].dwClientID = 0;
                memset(sg_asClientToBufMap[unClientIndex].pacClientName, 0, sizeof(char) * MAX_PATH);
                for (int i = 0; i < MAX_BUFF_ALLOWED; i++)
                {
                    sg_asClientToBufMap[unClientIndex].pClientBuf[i] = nullptr;
                }
                sg_asClientToBufMap[unClientIndex].unBufCount = 0;
                bResult = TRUE;

            }
            if (bResult == TRUE)
            {
                if ((unClientIndex + 1) < sg_unClientCnt)
                {
                    sg_asClientToBufMap[unClientIndex] = sg_asClientToBufMap[sg_unClientCnt - 1];
                }
                sg_unClientCnt--;
            }
        }
    }
    return bResult;
}

/**
* \brief         This function will check if the client ID exists
* \param[in]     dwClientId, client ID to be checked for existance
* \return        Returns TRUE if client ID existance is success, else FALSE
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static BOOL bClientIdExist(const DWORD& dwClientId)
{
    BOOL bReturn = FALSE;
    for (UINT i = 0; i < sg_unClientCnt; i++)
    {
        if (sg_asClientToBufMap[i].dwClientID == dwClientId)
        {
            bReturn = TRUE;
            i = sg_unClientCnt; // break the loop
        }
    }
    return bReturn;
}

/**
* \brief         This function will return the client index based on clientID
* \param[in]     dwClientId, client ID whose client index is needed
* \param[out]    unClientIndex, client index to be returned
* \return        Returns TRUE if client ID existance is success, else FALSE
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static BOOL bGetClientObj(DWORD dwClientID, UINT& unClientIndex)
{
    BOOL bResult = FALSE;
    for (UINT i = 0; i < sg_unClientCnt; i++)
    {
        if (sg_asClientToBufMap[i].dwClientID == dwClientID)
        {
            unClientIndex = i;
            i = sg_unClientCnt; // break the loop
            bResult = TRUE;
        }
    }
    return bResult;
}

/**
* \brief         Function to retreive error occurred and log it
* \param[in]     File, pointer to log file
* \param[in]     Line, indicates line number in log file
* \return        void
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static void vRetrieveAndLog(DWORD /*dwErrorCode*/, char* /*File*/, int /*Line*/)
{
    USES_CONVERSION;

    char acErrText[MAX_PATH] = { '\0' };

    sg_acErrStr = acErrText;
}

/**
* \brief         Function to check if client buffer exists
* \param[in]     sClientObj, alias to SCLIENTBUFMAP object
* \param[in]     pBuf, pointer to CBaseCANBufFSE object
* \return        TRUE if buffer exists, else FALSE
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static BOOL bIsBufferExists(const SCLIENTBUFMAP& sClientObj, const CBaseCANBufFSE* pBuf)
{
    BOOL bExist = FALSE;
    for (UINT i = 0; i < sClientObj.unBufCount; i++)
    {
        if (pBuf == sClientObj.pClientBuf[i])
        {
            bExist = TRUE;
            i = sClientObj.unBufCount; // break the loop
        }
    }

    return bExist;
}

/**
* \brief         Function to remove exissting client buffer
* \param[in]     RootBufferArray, pointer to CBaseCANBufFSE class array
* \param[out]    unCount, indicates buffer count which will get reduced
* \param[in]     BufferToRemove, pointer to the buffer to be removed
* \return        TRUE if removed
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static BOOL bRemoveClientBuffer(CBaseCANBufFSE* RootBufferArray[MAX_BUFF_ALLOWED], UINT& unCount, CBaseCANBufFSE* BufferToRemove)
{
    BOOL bReturn = TRUE;
    for (UINT i = 0; i < unCount; i++)
    {
        if (RootBufferArray[i] == BufferToRemove)
        {
            if (i < (unCount - 1)) /* If not the last bufffer */
            {
                RootBufferArray[i] = RootBufferArray[unCount - 1];
            }
            unCount--;
        }
    }
    return bReturn;
}

/**
* \brief         This function will check if the client exists and gives back the client index.
* \param[in]     pcClientName, client name as TCHAR*
* \param[out]    Index, client index if found
* \return        TRUE if client name is found, else FALSE
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static BOOL bClientExist(std::string pcClientName, INT& Index)
{
    for (UINT i = 0; i < sg_unClientCnt; i++)
    {
        if (!_tcscmp(pcClientName.c_str(), sg_asClientToBufMap[i].pacClientName))
        {
            Index = i;
            return TRUE;
        }
    }
    return FALSE;
}

/**
* \brief         This function will get available client slot
* \param         void
* \return        Returns the available client ID
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
static DWORD dwGetAvailableClientSlot()
{
    DWORD nClientId = 2;
    for (int i = 0; i < MAX_CLIENT_ALLOWED; i++)
    {
        if (bClientIdExist(nClientId))
        {
            nClientId += 1;
        }
        else
        {
            i = MAX_CLIENT_ALLOWED; // break the loop
        }
    }

    return nClientId;
}

int _RCAN_cfg::InvokeAdavancedSettings(PSCONTROLLER_DETAILS pControllerDetails, UINT nCount, UINT)
{
    return INFO_INITDAT_CONFIRM_CONFIG;
}

DOUBLE _RCAN_cfg::vValidateBaudRate(DOUBLE dBaudRate, int, UINT)
{
    CString omStrEditBaudRate;
    long nBaudRate = (long)dBaudRate;
    if (nBaudRate == 10000 || nBaudRate == 20000 || nBaudRate == 50000 || nBaudRate == 100000 || nBaudRate == 125000 || nBaudRate == 250000 || nBaudRate == 500000 || nBaudRate == 800000)
    {
        return nBaudRate;
    }
    else
    {
        return 1000000;
    }
}

/**
* \brief         Callback function for configuration dialog
* \param[in]     pDatStream, contains SCONTROLLER_DETAILS structure
* \return        TRUE if CAN_SetConfigData call succeeds, else FALSE
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
BOOL Callback_DILTZM(BYTE /*Argument*/, PSCONTROLLER_DETAILS pDatStream, int /*Length*/)
{
    printf("Callback_DILTZM()\n");

    return S_OK;
}

/**
* \brief         Helper function to display configuration dialog
* \param[in]     pControllerDetails, is SCONTROLLER_DETAILS structure
* \param[in]     nCount , is the channel count
* \return        returns configuration confirmation status
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
int DisplayConfigurationDlg(HWND hParent, PSCONTROLLER_DETAILS pControllerDetails, UINT nCount)
{
    printf("DisplayConfigurationDlg()\n");

    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    return 0;
}


/**
* \brief         Read thread procedure
* \param[in]     pVoid contains the CPARAM_THREADPROC class object
* \return        0
* \authors       Arunkumar Karri
* \date          12.10.2011 Created
*/
DWORD WINAPI CanMsgReadThreadProc_CAN_Rusoku_CAN(LPVOID pVoid)
{
    USES_CONVERSION;

//    static STCANDATA sg_asCANMsg;
//    static STCAN_MSG sg_ReadMsg;

    canalMsg    canMsg = { 0 };
    int         dataAvailable = 0;
    //static      LONGLONG QuadPartRef = 0;

    CPARAM_THREADPROC* pThreadParam = (CPARAM_THREADPROC*)pVoid;

    /* Validate certain required pointers */
    VALIDATE_POINTER_RETURN_VAL(pThreadParam, (DWORD)-1);
    /* Assign thread action to CREATE_TIME_MAP */
    pThreadParam->m_unActionCode = CREATE_TIME_MAP;
    pThreadParam->m_hActionEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    bool bLoopON = true;

    while (bLoopON)
    {
        switch (pThreadParam->m_unActionCode)
        { 
            case INVOKE_FUNCTION:
            {
                Sleep(0);
                sg_ReadMsg = { 0 };

                for (int nChannelIndex = 0; nChannelIndex < sg_nNoOfChannels; nChannelIndex++)
                {
                    if (dataAvailable = CanalDataAvailable(sg_aodChannels[nChannelIndex].m_hnd))
                    {
                        for (int dataIndex = 0; dataIndex < dataAvailable; dataIndex++)
                        {
                            if (CANAL_ERROR_SUCCESS == CanalReceive(sg_aodChannels[nChannelIndex].m_hnd, &canMsg))
                            {                                   
                                if (!(canMsg.flags & CANAL_IDFLAG_STATUS))
                                {
                                    printf("RX thread: RXDATA\n");

                                    if (CREATE_MAP_TIMESTAMP == sg_byCurrState)
                                    {
                                        sg_byCurrState = CALC_TIMESTAMP_READY;

                                        LARGE_INTEGER g_QueryTickCount;
                                        QueryPerformanceCounter(&g_QueryTickCount);
                                        UINT64 unConnectionTime;
                                        unConnectionTime = ((g_QueryTickCount.QuadPart * 10000) / sg_lnFrequency.QuadPart) - sg_TimeStamp;

                                        //Time difference should be +ve value
                                        if ((canMsg.timestamp / 100) >= unConnectionTime)
                                        {
                                            sg_TimeStamp = (LONGLONG)((canMsg.timestamp / 100) - unConnectionTime);
                                        }
                                        else
                                        {
                                            sg_TimeStamp = (LONGLONG)(unConnectionTime - (canMsg.timestamp / 100));
                                        }
                                    }

                                    sg_asCANMsg.m_lTickCount.QuadPart = canMsg.timestamp / 100;

                                    sg_ReadMsg.m_unMsgID = canMsg.id;
                                    sg_ReadMsg.m_ucDataLen = canMsg.sizeData;

                                    if (canMsg.flags & CANAL_IDFLAG_EXTENDED)
                                    {
                                        sg_ReadMsg.m_ucEXTENDED = TRUE;
                                    }
                                    else
                                    {
                                        sg_ReadMsg.m_ucEXTENDED = FALSE;
                                    }

                                    if (canMsg.flags & CANAL_IDFLAG_RTR)
                                    {
                                        sg_ReadMsg.m_ucRTR = TRUE;
                                    }
                                    else
                                    {
                                        sg_ReadMsg.m_ucRTR = FALSE;
                                    }

                                    memcpy(sg_ReadMsg.m_ucData, canMsg.data, 8);

                                    sg_ReadMsg.m_ucChannel = nChannelIndex + 1;

                                    sg_asCANMsg.m_uDataInfo.m_sCANMsg.m_bCANFD = false;
                                    sg_asCANMsg.m_ucDataType = RX_FLAG;
                                    /* Copy STCAN_MSG */
                                    sg_asCANMsg.m_uDataInfo.m_sCANMsg = sg_ReadMsg;
                                }
                                else if (canMsg.flags & CANAL_IDFLAG_STATUS)
                                {
                                    printf("RX thread: ERROR\n");

                                    if (canMsg.data[0] & CANAL_STATUSMSG_BIT0)
                                    {
                                        sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucReg_ErrCap = BIT_ERROR_RX;
                                    }
                                    else if (canMsg.data[0] & CANAL_STATUSMSG_BIT1)
                                    {
                                        sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucReg_ErrCap = BIT_ERROR_RX;
                                    }
                                    else if (canMsg.data[0] & CANAL_STATUSMSG_FORM)
                                    {
                                        sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucReg_ErrCap = FORM_ERROR_RX;
                                    }
                                    else if (canMsg.data[0] & CANAL_STATUSMSG_ACK)
                                    {
                                        sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucReg_ErrCap = ACK_ERROR_RX;
                                    }
                                    else if (canMsg.data[0] & CANAL_STATUSMSG_STUFF)
                                    {
                                        sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucReg_ErrCap = STUFF_ERROR_RX;
                                    }
                                    else if (canMsg.data[0] & CANAL_STATUSMSG_CRC)
                                    {
                                        sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucReg_ErrCap = CRC_ERROR_TX;
                                    }
                                    else 
                                        sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucReg_ErrCap = OTHER_ERROR_RX;
                                    
                                    sg_asCANMsg.m_ucDataType = ERR_FLAG;
                                    sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucErrType = ERROR_BUS;
                                    // Assign the channel number
                                    sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_ucChannel = (UCHAR)nChannelIndex + 1;
                                    sg_asCANMsg.m_uDataInfo.m_sCANMsg.m_ucChannel = (UCHAR)nChannelIndex + 1;

                                    //explaination of error bit
                                    sg_asCANMsg.m_uDataInfo.m_sErrInfo.m_nSubError = 0;

                                    //sg_aodChannels[nChannelIndex].m_ucTxErrorCounter = CanalStatus.channel_status & 0xFF;
                                    //sg_aodChannels[nChannelIndex].m_ucRxErrorCounter = (CanalStatus.channel_status >> 8) & 0x3F;
                                }

                                //Write into client buffer.
                                vWriteIntoClientsBuffer(sg_asCANMsg);
                            }
                        }
                    }
                }
            }
            break;
            case EXIT_THREAD:
            {
                bLoopON = false;
            }
            break;
            case CREATE_TIME_MAP:
            {
                //SetEvent(pThreadParam->m_hActionEvent);
                pThreadParam->m_unActionCode = INVOKE_FUNCTION;
            }
            break;
            case INACTION:
            {
            }
            break;
        }
    }

    printf("---------EXIT from Thread!!!!\n");
    SetEvent(pThreadParam->hGetExitNotifyEvent()); // Signal the owner that the thread
    //pThreadParam->m_hActionEvent = nullptr;
    Sleep(0);

    return 0;
}
