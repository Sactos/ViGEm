// {96E42B22-F5E9-42F8-B043-ED0F932F014F}
DEFINE_GUID(GUID_DEVINTERFACE_BUSENUM_VIGEM,
    0x96E42B22, 0xF5E9, 0x42F8, 0xB0, 0x43, 0xED, 0x0F, 0x93, 0x2F, 0x01, 0x4F);

// {02098E80-3C81-4CF0-A2C5-CD4D3B318902}
DEFINE_GUID(GUID_DEVINTERFACE_VIGEM,
    0x02098E80, 0x3C81, 0x4CF0, 0xA2, 0xC5, 0xCD, 0x4D, 0x3B, 0x31, 0x89, 0x02);

// {A8BA2D1F-894F-464A-B0CE-7A0C8FD65DF1}
DEFINE_GUID(GUID_DEVCLASS_VIGEM_RAWPDO,
    0xA8BA2D1F, 0x894F, 0x464A, 0xB0, 0xCE, 0x7A, 0x0C, 0x8F, 0xD6, 0x5D, 0xF1);

#pragma once

#define FILE_DEVICE_BUSENUM             FILE_DEVICE_BUS_EXTENDER
#define BUSENUM_IOCTL(_index_)          CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_READ_DATA)
#define BUSENUM_W_IOCTL(_index_)        CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_WRITE_DATA)
#define BUSENUM_R_IOCTL(_index_)        CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_READ_DATA)
#define BUSENUM_RW_IOCTL(_index_)       CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_WRITE_DATA | FILE_READ_DATA)

#define IOCTL_VIGEM_BASE 0x801

// 
// IO control codes
// 
#define IOCTL_VIGEM_PLUGIN_TARGET       BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x000)
#define IOCTL_VIGEM_UNPLUG_TARGET       BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x001)
#define IOCTL_VIGEM_EJECT_TARGET        BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x002)

#define IOCTL_XUSB_REQUEST_NOTIFICATION BUSENUM_RW_IOCTL(IOCTL_VIGEM_BASE + 0x200)
#define IOCTL_XUSB_SUBMIT_REPORT        BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x201)
#define IOCTL_DS4_SUBMIT_REPORT         BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x202)


//
//  Data structure used in PlugIn and UnPlug ioctls
//

//
// Represents the desired target type for the emulated device.
//  
typedef enum _VIGEM_TARGET_TYPE
{
    // 
    // Microsoft Xbox 360 Controller (wired)
    // 
    Xbox360Wired,
    //
    // Sony DualShock 4 (wired)
    // 
    DualShock4Wired
} VIGEM_TARGET_TYPE, *PVIGEM_TARGET_TYPE;

//
// Data structure used in IOCTL_VIGEM_PLUGIN_TARGET requests.
// 
typedef struct _VIGEM_PLUGIN_TARGET
{
    //
    // sizeof (struct _BUSENUM_HARDWARE)
    //
    IN ULONG Size;

    //
    // Serial number of target device.
    // 
    IN ULONG SerialNo;

    // 
    // Type of the target device to emulate.
    // 
    VIGEM_TARGET_TYPE TargetType;
} VIGEM_PLUGIN_TARGET, *PVIGEM_PLUGIN_TARGET;

//
// Data structure used in IOCTL_VIGEM_UNPLUG_TARGET requests.
// 
typedef struct _VIGEM_UNPLUG_TARGET
{
    //
    // sizeof (struct _REMOVE_HARDWARE)
    //
    IN ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

} VIGEM_UNPLUG_TARGET, *PVIGEM_UNPLUG_TARGET;

//
// Data structure used in IOCTL_VIGEM_EJECT_TARGET requests.
// 
typedef struct _VIGEM_EJECT_TARGET
{
    //
    // sizeof (struct _EJECT_HARDWARE)
    //
    IN ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

} VIGEM_EJECT_TARGET, *PVIGEM_EJECT_TARGET;

//
// Data structure used in IOCTL_XUSB_REQUEST_NOTIFICATION requests.
// 
typedef struct _XUSB_REQUEST_NOTIFICATION
{
    //
    // sizeof(struct _XUSB_REQUEST_NOTIFICATION)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // Vibration intensity value of the large motor (0-255).
    // 
    UCHAR LargeMotor;

    //
    // Vibration intensity value of the small motor (0-255).
    // 
    UCHAR SmallMotor;

    //
    // Index number of the slot/LED that XUSB.sys has assigned.
    // 
    UCHAR LedNumber;
} XUSB_REQUEST_NOTIFICATION, *PXUSB_REQUEST_NOTIFICATION;

//
// Represents an XINPUT_GAMEPAD-compatible report structure.
// 
typedef struct _XUSB_REPORT
{
    WORD wButtons;
    BYTE bLeftTrigger;
    BYTE bRightTrigger;
    SHORT sThumbLX;
    SHORT sThumbLY;
    SHORT sThumbRX;
    SHORT sThumbRY;
} XUSB_REPORT, *PXUSB_REPORT;

//
// Data structure used in IOCTL_XUSB_SUBMIT_REPORT requests.
// 
typedef struct _XUSB_SUBMIT_REPORT
{
    //
    // sizeof(struct _XUSB_SUBMIT_REPORT)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // Report to submit to the target device.
    // 
    XUSB_REPORT Report;
} XUSB_SUBMIT_REPORT, *PXUSB_SUBMIT_REPORT;

//
// DualShock 4 HID Input report
// 
typedef struct _DS4_REPORT
{
    BYTE bThumbLX;
    BYTE bThumbLY;
    BYTE bThumbRX;
    BYTE bThumbRY;
    WORD wButtons;
    BYTE bSpecial;
    BYTE bTriggerL;
    BYTE bTriggerR;
} DS4_REPORT, *PDS4_REPORT;

//
// DualShock 4 digital buttons
// 
typedef enum _DS4_BUTTONS
{
    Ds4ThumbR = 1 << 15,
    Ds4ThumbL = 1 << 14,
    Ds4Options = 1 << 13,
    Ds4Share = 1 << 12,
    Ds4TriggerR = 1 << 11,
    Ds4TriggerL = 1 << 10,
    Ds4ShoulderR = 1 << 9,
    Ds4ShoulderL = 1 << 8,
    Ds4Triangle = 1 << 7,
    Ds4Circle = 1 << 6,
    Ds4Cross = 1 << 5,
    Ds4Square = 1 << 4
} DS4_BUTTONS, *PDS4_BUTTONS;

//
// DualShock 4 special buttons
// 
typedef enum _DS4_SPECIAL_BUTTONS
{
    Ds4Ps = 1 << 0,
    Ds4Touchpad = 1 << 1
} DS4_SPECIAL_BUTTONS, *PDS4_SPECIAL_BUTTONS;

//
// DualShock 4 directional pad values
// 
typedef enum _DS4_DPAD_DIRECTIONS
{
    Ds4DpadNone = 0x8,
    Ds4DpadNW = 0x7,
    Ds4DpadW = 0x6,
    Ds4DpadSW = 0x5,
    Ds4DpadS = 0x4,
    Ds4DpadSE = 0x3,
    Ds4DpadE = 0x2,
    Ds4DpadNE = 0x1,
    Ds4DpadN = 0x0
} DS4_DPAD_DIRECTIONS, *PDS4_DPAD_DIRECTIONS;

//
// DualShock 4 request data
// 
typedef struct _DS4_SUBMIT_REPORT
{
    //
    // sizeof(struct _DS4_SUBMIT_REPORT)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // HID Input report
    // 
    DS4_REPORT HidReport;
} DS4_SUBMIT_REPORT, *PDS4_SUBMIT_REPORT;

VOID FORCEINLINE DS4_SET_DPAD(
    _Out_ PDS4_SUBMIT_REPORT Report,
    _In_ DS4_DPAD_DIRECTIONS Dpad
)
{
    Report->HidReport.wButtons &= ~0xF;
    Report->HidReport.wButtons |= (WORD)Dpad;
}

VOID FORCEINLINE DS4_SUBMIT_REPORT_INIT(
    _Out_ PDS4_SUBMIT_REPORT Report,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Report, sizeof(DS4_SUBMIT_REPORT));

    Report->Size = sizeof(DS4_SUBMIT_REPORT);
    Report->SerialNo = SerialNo;

    Report->HidReport.bThumbLX = 0x80;
    Report->HidReport.bThumbLY = 0x80;
    Report->HidReport.bThumbRX = 0x80;
    Report->HidReport.bThumbRY = 0x80;

    DS4_SET_DPAD(Report, Ds4DpadNone);
}

