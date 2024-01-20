/*
* Copyright Robert Bosch Engineering and Business Solutions Private Limited. All Rights Reserved.
*/
#ifndef KERNEL_PROTOCOLDEFINITION_FLEXRAYENUMS_H_
#define KERNEL_PROTOCOLDEFINITION_FLEXRAYENUMS_H_

enum eFlexRayChannel {
    eFlexRayChannelNone,
    eFlexRayChannelA,
    eFlexRayChannelB,
    eFlexRayChannelAB,
    eFlexRayChannelTotal
};

enum eFlexRaySlotType {
    eStatic,
    eDynamic,
};

enum eFlexRayFrameType {
    eFelxRayFrameNone,
    eNormal,
    eSync,
    eStartUp,
    eSyncStartup,
};

enum eFlexRayKeySlotType {
    eSyncType,
    eSyncStartupType,
    eNone
};

#endif // KERNEL_PROTOCOLDEFINITION_FLEXRAYENUMS_H_