#ifndef _PH_PHBASE_H
#define _PH_PHBASE_H

#pragma once

#pragma comment(lib, "ntdll.lib")

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "version.lib")

// nonstandard extension used : nameless struct/union
#pragma warning(disable: 4201)
// nonstandard extension used : bit field types other than int
#pragma warning(disable: 4214)
// 'function': attributes not present on previous declaration
#pragma warning(disable: 4985)
// 'function': was declared deprecated
#pragma warning(disable: 4996)

#ifndef UNICODE
#define UNICODE
#endif

#if defined(PHLIB_EXPORT)
#define PHLIBAPI __declspec(dllexport)
#elif defined(PHLIB_IMPORT)
#define PHLIBAPI __declspec(dllimport)
#else
#define PHLIBAPI
#endif

#include <ntwin.h>
#include <ntbasic.h>
#include <phnt.h>
#include <phsup.h>
#include <ntimport.h>
#include <ref.h>
#include <fastlock.h>
#include <queuedlock.h>

#ifndef _PH_GLOBAL_PRIVATE

struct _PH_STRING;
typedef struct _PH_STRING *PPH_STRING;

struct _PH_PROVIDER_THREAD;
typedef struct _PH_PROVIDER_THREAD PH_PROVIDER_THREAD;

struct _PH_STARTUP_PARAMETERS;
typedef struct _PH_STARTUP_PARAMETERS PH_STARTUP_PARAMETERS;

#define __userSet

extern __userSet HFONT PhApplicationFont;
extern __userSet PWSTR PhApplicationName;
extern __userSet HFONT PhBoldListViewFont;
extern __userSet HFONT PhBoldMessageFont;
extern ULONG PhCurrentSessionId;
extern HANDLE PhCurrentTokenQueryHandle;
extern BOOLEAN PhElevated;
extern TOKEN_ELEVATION_TYPE PhElevationType;
extern PVOID PhHeapHandle;
extern __userSet HFONT PhIconTitleFont;
extern HINSTANCE PhInstanceHandle;
extern __userSet HANDLE PhKphHandle;
extern __userSet ULONG PhKphFeatures;
extern RTL_OSVERSIONINFOEXW PhOsVersion;
extern SYSTEM_BASIC_INFORMATION PhSystemBasicInformation;
extern ULONG WindowsVersion;

extern ACCESS_MASK ProcessQueryAccess;
extern ACCESS_MASK ProcessAllAccess;
extern ACCESS_MASK ThreadQueryAccess;
extern ACCESS_MASK ThreadSetAccess;
extern ACCESS_MASK ThreadAllAccess;

#endif

#define WINDOWS_ANCIENT 0
#define WINDOWS_XP 51
#define WINDOWS_SERVER_2003 52
#define WINDOWS_VISTA 60
#define WINDOWS_7 61
#define WINDOWS_NEW MAXLONG

#define WINDOWS_HAS_CONSOLE_HOST (WindowsVersion >= WINDOWS_7)
#define WINDOWS_HAS_CYCLE_TIME (WindowsVersion >= WINDOWS_VISTA)
#define WINDOWS_HAS_IFILEDIALOG (WindowsVersion >= WINDOWS_VISTA)
#define WINDOWS_HAS_IMAGE_FILE_NAME_BY_PROCESS_ID (WindowsVersion >= WINDOWS_VISTA)
#define WINDOWS_HAS_LIMITED_ACCESS (WindowsVersion >= WINDOWS_VISTA)
#define WINDOWS_HAS_PSSUSPENDRESUMEPROCESS (WindowsVersion >= WINDOWS_VISTA)
#define WINDOWS_HAS_SERVICE_TAGS (WindowsVersion >= WINDOWS_VISTA)
#define WINDOWS_HAS_UAC (WindowsVersion >= WINDOWS_VISTA)

// data

#ifndef _PH_DATA_PRIVATE

// SIDs

extern SID PhSeNobodySid;

extern SID PhSeEveryoneSid;

extern SID PhSeLocalSid;

extern SID PhSeCreatorOwnerSid;
extern SID PhSeCreatorGroupSid;

extern SID PhSeDialupSid;
extern SID PhSeNetworkSid;
extern SID PhSeBatchSid;
extern SID PhSeInteractiveSid;
extern SID PhSeServiceSid;
extern SID PhSeAnonymousLogonSid;
extern SID PhSeProxySid;
extern SID PhSeAuthenticatedUserSid;
extern SID PhSeRestrictedCodeSid;
extern SID PhSeTerminalServerUserSid;
extern SID PhSeRemoteInteractiveLogonSid;
extern SID PhSeLocalSystemSid;
extern SID PhSeLocalServiceSid;
extern SID PhSeNetworkServiceSid;

// Characters

extern BOOLEAN PhCharIsPrintable[256];
extern ULONG PhCharToInteger[256];
extern CHAR PhIntegerToChar[69];
extern CHAR PhIntegerToCharUpper[69];

// Enums

extern WCHAR *PhKThreadStateNames[MaximumThreadState];
extern WCHAR *PhKWaitReasonNames[MaximumWaitReason];

#endif

// global

NTSTATUS PhInitializePhLib();

// basesup

struct _PH_OBJECT_TYPE;
typedef struct _PH_OBJECT_TYPE *PPH_OBJECT_TYPE;

BOOLEAN PhInitializeBase();

// threads

#ifdef DEBUG
struct _PH_AUTO_POOL;
typedef struct _PH_AUTO_POOL *PPH_AUTO_POOL;

typedef struct _PHP_BASE_THREAD_DBG
{
    CLIENT_ID ClientId;
    LIST_ENTRY ListEntry;
    PVOID StartAddress;
    PVOID Parameter;

    PPH_AUTO_POOL CurrentAutoPool;
} PHP_BASE_THREAD_DBG, *PPHP_BASE_THREAD_DBG;
#endif

#if !defined(_PH_BASESUP_PRIVATE) && defined(DEBUG)
extern ULONG PhDbgThreadDbgTlsIndex;
extern LIST_ENTRY PhDbgThreadListHead;
extern PH_QUEUED_LOCK PhDbgThreadListLock;
#endif

PHLIBAPI
HANDLE
NTAPI
PhCreateThread(
    __in_opt SIZE_T StackSize,
    __in PUSER_THREAD_START_ROUTINE StartAddress,
    __in_opt PVOID Parameter
    );

// misc. system

PHLIBAPI
PVOID
NTAPI
PhGetProcedureAddress(
    __in PVOID DllHandle,
    __in_opt PSTR ProcedureName,
    __in_opt ULONG ProcedureNumber
    );

PHLIBAPI
VOID
NTAPI
PhQuerySystemTime(
    __out PLARGE_INTEGER SystemTime
    );

PHLIBAPI
VOID
NTAPI
PhQueryTimeZoneBias(
    __out PLARGE_INTEGER TimeZoneBias
    );

PHLIBAPI
VOID
NTAPI
PhSystemTimeToLocalTime(
    __in PLARGE_INTEGER SystemTime,
    __out PLARGE_INTEGER LocalTime
    );

PHLIBAPI
VOID
NTAPI
PhLocalTimeToSystemTime(
    __in PLARGE_INTEGER LocalTime,
    __out PLARGE_INTEGER SystemTime
    );

// heap

__mayRaise
PHLIBAPI
PVOID
NTAPI
PhAllocate(
    __in SIZE_T Size
    );

PHLIBAPI
PVOID
NTAPI
PhAllocateSafe(
    __in SIZE_T Size
    );

PHLIBAPI
PVOID
NTAPI
PhAllocateExSafe(
    __in SIZE_T Size,
    __in ULONG Flags
    );

PHLIBAPI
VOID
NTAPI
PhFree(
    __in __post_invalid PVOID Memory
    );

__mayRaise
PHLIBAPI
PVOID
NTAPI
PhReAllocate(
    __in PVOID Memory,
    __in SIZE_T Size
    );

PHLIBAPI
PVOID
NTAPI
PhReAllocateSafe(
    __in PVOID Memory,
    __in SIZE_T Size
    );

PHLIBAPI
PVOID
NTAPI
PhAllocatePage(
    __in SIZE_T Size,
    __out_opt PSIZE_T NewSize
    );

PHLIBAPI
VOID
NTAPI
PhFreePage(
    __in PVOID Memory
    );

FORCEINLINE PVOID PhAllocateAligned(
    __in SIZE_T Size,
    __in ULONG Align,
    __in SIZE_T AllocationBaseOffset
    )
{
    PVOID memory;
    PVOID allocationBase;

    allocationBase = PhAllocate(Size + Align - 1);
    memory = PTR_ALIGN(allocationBase, Align);
    *(PPVOID)PTR_ADD_OFFSET(memory, AllocationBaseOffset) = allocationBase;

    return memory;
}

FORCEINLINE VOID PhFreeAligned(
    __in __post_invalid PVOID Memory,
    __in SIZE_T AllocationBaseOffset
    )
{
    PhFree(*(PPVOID)PTR_ADD_OFFSET(Memory, AllocationBaseOffset));
}

FORCEINLINE PVOID PhAllocateCopy(
    __in PVOID Data,
    __in ULONG Size
    )
{
    PVOID copy;

    copy = PhAllocate(Size);
    memcpy(copy, Data, Size);

    return copy;
}

// event

#define PH_EVENT_SET 0x1
#define PH_EVENT_SET_SHIFT 0
#define PH_EVENT_REFCOUNT_SHIFT 1
#define PH_EVENT_REFCOUNT_INC 0x2

/**
 * A fast event object.
 *
 * \remarks
 * This event object does not use a kernel event object 
 * until necessary, and frees the object automatically 
 * when it is no longer needed.
 */
typedef struct _PH_EVENT
{
    ULONG_PTR Value;
    HANDLE EventHandle;
} PH_EVENT, *PPH_EVENT;

#define PH_EVENT_INIT { PH_EVENT_REFCOUNT_INC, NULL }

PHLIBAPI
VOID
FASTCALL
PhfInitializeEvent(
    __out PPH_EVENT Event
    );

#define PhSetEvent PhfSetEvent
PHLIBAPI
VOID
FASTCALL
PhfSetEvent(
    __inout PPH_EVENT Event
    );

#define PhWaitForEvent PhfWaitForEvent
PHLIBAPI
BOOLEAN
FASTCALL
PhfWaitForEvent(
    __inout PPH_EVENT Event,
    __in_opt PLARGE_INTEGER Timeout
    );

#define PhResetEvent PhfResetEvent
PHLIBAPI
VOID
FASTCALL
PhfResetEvent(
    __inout PPH_EVENT Event
    );

FORCEINLINE VOID PhInitializeEvent(
    __out PPH_EVENT Event
    )
{
    Event->Value = PH_EVENT_REFCOUNT_INC;
    Event->EventHandle = NULL;
}

/**
 * Determines whether an event object is set.
 *
 * \param Event A pointer to an event object.
 *
 * \return TRUE if the event object is set, 
 * otherwise FALSE.
 */
FORCEINLINE BOOLEAN PhTestEvent(
    __in PPH_EVENT Event
    )
{
    return !!(Event->Value & PH_EVENT_SET);
}

// barrier

#define PH_BARRIER_COUNT_SHIFT 0
#define PH_BARRIER_COUNT_MASK (((LONG_PTR)1 << (sizeof(ULONG_PTR) * 8 / 2 - 1)) - 1)
#define PH_BARRIER_COUNT_INC ((LONG_PTR)1 << PH_BARRIER_COUNT_SHIFT)
#define PH_BARRIER_TARGET_SHIFT (sizeof(ULONG_PTR) * 8 / 2)
#define PH_BARRIER_TARGET_MASK (((LONG_PTR)1 << (sizeof(ULONG_PTR) * 8 / 2 - 1)) - 1)
#define PH_BARRIER_TARGET_INC ((LONG_PTR)1 << PH_BARRIER_TARGET_SHIFT)
#define PH_BARRIER_WAKING ((LONG_PTR)1 << (sizeof(ULONG_PTR) * 8 - 1))

#define PH_BARRIER_MASTER 1
#define PH_BARRIER_SLAVE 2
#define PH_BARRIER_OBSERVER 3

typedef struct _PH_BARRIER
{
    ULONG_PTR Value;
    PH_QUEUED_LOCK WakeEvent;
} PH_BARRIER, *PPH_BARRIER;

#define PH_BARRIER_INIT(Target) { (Target) << PH_BARRIER_TARGET_SHIFT, PH_QUEUED_LOCK_INIT }

PHLIBAPI
VOID
FASTCALL
PhfInitializeBarrier(
    __out PPH_BARRIER Barrier,
    __in ULONG_PTR Target
    );

#define PhWaitForBarrier PhfWaitForBarrier
PHLIBAPI
BOOLEAN
FASTCALL
PhfWaitForBarrier(
    __inout PPH_BARRIER Barrier,
    __in BOOLEAN Spin
    );

FORCEINLINE VOID PhInitializeBarrier(
    __out PPH_BARRIER Barrier,
    __in ULONG_PTR Target
    )
{
    Barrier->Value = Target << PH_BARRIER_TARGET_SHIFT;
    PhInitializeQueuedLock(&Barrier->WakeEvent);
}

// rundown protection

#define PH_RUNDOWN_ACTIVE 0x1
#define PH_RUNDOWN_REF_SHIFT 1
#define PH_RUNDOWN_REF_INC 0x2

typedef struct _PH_RUNDOWN_PROTECT
{
    ULONG_PTR Value;
} PH_RUNDOWN_PROTECT, *PPH_RUNDOWN_PROTECT;

#define PH_RUNDOWN_PROTECT_INIT { 0 }

typedef struct _PH_RUNDOWN_WAIT_BLOCK
{
    ULONG_PTR Count;
    PH_EVENT WakeEvent;
} PH_RUNDOWN_WAIT_BLOCK, *PPH_RUNDOWN_WAIT_BLOCK;

PHLIBAPI
VOID
FASTCALL
PhfInitializeRundownProtection(
    __out PPH_RUNDOWN_PROTECT Protection
    );

PHLIBAPI
BOOLEAN
FASTCALL
PhfAcquireRundownProtection(
    __inout PPH_RUNDOWN_PROTECT Protection
    );

PHLIBAPI
VOID
FASTCALL
PhfReleaseRundownProtection(
    __inout PPH_RUNDOWN_PROTECT Protection
    );

PHLIBAPI
VOID
FASTCALL
PhfWaitForRundownProtection(
    __inout PPH_RUNDOWN_PROTECT Protection
    );

FORCEINLINE VOID PhInitializeRundownProtection(
    __out PPH_RUNDOWN_PROTECT Protection
    )
{
    Protection->Value = 0;
}

FORCEINLINE BOOLEAN PhAcquireRundownProtection(
    __inout PPH_RUNDOWN_PROTECT Protection
    )
{
    ULONG_PTR value;

    value = Protection->Value & ~PH_RUNDOWN_ACTIVE; // fail fast path when rundown is active

    if ((ULONG_PTR)_InterlockedCompareExchangePointer(
        (PPVOID)&Protection->Value,
        (PVOID)(value + PH_RUNDOWN_REF_INC),
        (PVOID)value
        ) == value)
    {
        return TRUE;
    }
    else
    {
        return PhfAcquireRundownProtection(Protection);
    }
}

FORCEINLINE VOID PhReleaseRundownProtection(
    __inout PPH_RUNDOWN_PROTECT Protection
    )
{
    ULONG_PTR value;

    value = Protection->Value & ~PH_RUNDOWN_ACTIVE; // fail fast path when rundown is active

    if ((ULONG_PTR)_InterlockedCompareExchangePointer(
        (PPVOID)&Protection->Value,
        (PVOID)(value - PH_RUNDOWN_REF_INC),
        (PVOID)value
        ) != value)
    {
        PhfReleaseRundownProtection(Protection);
    }
}

FORCEINLINE VOID PhWaitForRundownProtection(
    __inout PPH_RUNDOWN_PROTECT Protection
    )
{
    ULONG_PTR value;

    value = (ULONG_PTR)_InterlockedCompareExchangePointer(
        (PPVOID)&Protection->Value,
        (PVOID)PH_RUNDOWN_ACTIVE,
        (PVOID)0
        );

    if (value != 0 && value != PH_RUNDOWN_ACTIVE)
        PhfWaitForRundownProtection(Protection);
}

// one-time initialization

#define PH_INITONCE_UNINITIALIZED 0
#define PH_INITONCE_INITIALIZED 1
#define PH_INITONCE_INITIALIZING 2

typedef struct _PH_INITONCE
{
    LONG State;
    PH_EVENT WakeEvent;
} PH_INITONCE, *PPH_INITONCE;

#define PH_INITONCE_INIT { PH_INITONCE_UNINITIALIZED, PH_EVENT_INIT }

#define PhInitializeInitOnce PhfInitializeInitOnce
PHLIBAPI
VOID
FASTCALL
PhfInitializeInitOnce(
    __out PPH_INITONCE InitOnce
    );

PHLIBAPI
BOOLEAN
FASTCALL
PhfBeginInitOnce(
    __inout PPH_INITONCE InitOnce
    );

#define PhEndInitOnce PhfEndInitOnce
PHLIBAPI
VOID
FASTCALL
PhfEndInitOnce(
    __inout PPH_INITONCE InitOnce
    );

FORCEINLINE BOOLEAN PhBeginInitOnce(
    __inout PPH_INITONCE InitOnce
    )
{
    if (InitOnce->State == PH_INITONCE_INITIALIZED)
        return FALSE;
    else
        return PhfBeginInitOnce(InitOnce);
}

FORCEINLINE BOOLEAN PhTestInitOnce(
    __in PPH_INITONCE InitOnce
    )
{
    return InitOnce->State == PH_INITONCE_INITIALIZED;
}

// string

#ifndef _PH_BASESUP_PRIVATE
extern PPH_OBJECT_TYPE PhStringType;
#endif

PHLIBAPI
PSTR
NTAPI
PhDuplicateAnsiStringZ(
    __in PSTR String
    );

PHLIBAPI
PSTR
NTAPI
PhDuplicateAnsiStringZSafe(
    __in PSTR String
    );

PHLIBAPI
BOOLEAN
NTAPI
PhCopyAnsiStringZ(
    __in PSTR InputBuffer,
    __in ULONG InputCount,
    __out_ecount_z_opt(OutputCount) PSTR OutputBuffer,
    __in ULONG OutputCount,
    __out_opt PULONG ReturnCount
    );

PHLIBAPI
BOOLEAN
NTAPI
PhCopyUnicodeStringZ(
    __in PWSTR InputBuffer,
    __in ULONG InputCount,
    __out_ecount_z_opt(OutputCount) PWSTR OutputBuffer,
    __in ULONG OutputCount,
    __out_opt PULONG ReturnCount
    );

PHLIBAPI
BOOLEAN
NTAPI
PhCopyUnicodeStringZFromAnsi(
    __in PSTR InputBuffer,
    __in ULONG InputCount,
    __out_ecount_z_opt(OutputCount) PWSTR OutputBuffer,
    __in ULONG OutputCount,
    __out_opt PULONG ReturnCount
    );

PHLIBAPI
LONG
NTAPI
PhCompareUnicodeStringZNatural(
    __in PWSTR A,
    __in PWSTR B,
    __in BOOLEAN IgnoreCase
    );

#define PH_STRING_MAXLEN MAXUINT16

typedef struct _PH_STRINGREF
{
    union
    {
        struct
        {
            /** The length, in bytes, of the string. */
            USHORT Length;
            /** Unused and of an undefined value. */
            USHORT Reserved;
            /** The buffer containing the contents of the string. */
            PWSTR Buffer;
        };
        UNICODE_STRING us;
    };
} PH_STRINGREF, *PPH_STRINGREF;

typedef struct _PH_RELATIVE_STRINGREF
{
    /** The length, in bytes, of the string. */
    ULONG Length;
    /** A user-defined offset. */
    ULONG Offset;
} PH_RELATIVE_STRINGREF, *PPH_RELATIVE_STRINGREF;

#define PH_STRINGREF_INIT(String) { (USHORT)(sizeof(String) - sizeof(WCHAR)), (USHORT)sizeof(String), (String) }

FORCEINLINE VOID PhInitializeStringRef(
    __out PPH_STRINGREF String,
    __in PWSTR Buffer
    )
{
    String->Length = (USHORT)(wcslen(Buffer) * sizeof(WCHAR));
    String->Buffer = Buffer;
}

FORCEINLINE VOID PhInitializeEmptyStringRef(
    __out PPH_STRINGREF String
    )
{
    String->Length = 0;
    String->Buffer = NULL;
}

FORCEINLINE BOOLEAN PhIsNullOrEmptyStringRef(
    __in_opt PPH_STRINGREF String
    )
{
    return !String || String->Length == 0;
}

FORCEINLINE LONG PhCompareStringRef(
    __in PPH_STRINGREF String1,
    __in PPH_STRINGREF String2,
    __in BOOLEAN IgnoreCase
    )
{
    return RtlCompareUnicodeString(&String1->us, &String2->us, IgnoreCase);
}

FORCEINLINE LONG PhCompareStringRef2(
    __in PPH_STRINGREF String1,
    __in PWSTR String2,
    __in BOOLEAN IgnoreCase
    )
{
    INT result;

    if (!IgnoreCase)
        result = wcsncmp(String1->Buffer, String2, String1->Length / sizeof(WCHAR));
    else
        result = wcsnicmp(String1->Buffer, String2, String1->Length / sizeof(WCHAR));

    // The above operation is essentially a "starts with" test, which means that we 
    // must do additional processing.
    if (result == 0)
    {
        return (INT)String1->Length / sizeof(WCHAR) - (INT)wcslen(String2);
    }
    else
    {
        return result;
    }
}

FORCEINLINE BOOLEAN PhEqualStringRef(
    __in PPH_STRINGREF String1,
    __in PPH_STRINGREF String2,
    __in BOOLEAN IgnoreCase
    )
{
    return RtlEqualUnicodeString(&String1->us, &String2->us, IgnoreCase);
}

FORCEINLINE BOOLEAN PhEqualStringRef2(
    __in PPH_STRINGREF String1,
    __in PWSTR String2,
    __in BOOLEAN IgnoreCase
    )
{
    return PhCompareStringRef2(String1, String2, IgnoreCase) == 0;
}

FORCEINLINE BOOLEAN PhStartsWithStringRef(
    __in PPH_STRINGREF String1,
    __in PPH_STRINGREF String2,
    __in BOOLEAN IgnoreCase
    )
{
    return RtlPrefixUnicodeString(&String2->us, &String1->us, IgnoreCase);
}

FORCEINLINE VOID PhReverseStringRef(
    __in PPH_STRINGREF String
    )
{
    ULONG i;
    ULONG j;
    WCHAR t;

    for (i = 0, j = String->Length / sizeof(WCHAR) - 1; i <= j; i++, j--)
    {
        t = String->Buffer[i];
        String->Buffer[i] = String->Buffer[j];
        String->Buffer[j] = t;
    }
}

/**
 * A Unicode string object.
 *
 * \remarks The \a Length never includes the null terminator. Every 
 * string must have a null terminator at the end, for compatibility 
 * reasons. Thus the invariant is:
 * \code Buffer[Length / sizeof(WCHAR)] = 0 \endcode
 */
typedef struct _PH_STRING
{
    union
    {
        /** An embedded UNICODE_STRING structure. */
        UNICODE_STRING us;
        PH_STRINGREF sr;
        struct
        {
            /** The length, in bytes, of the string. */
            USHORT Length;
            /** Unused and always equal to \ref Length. */
            USHORT MaximumLength;
            /** Unused and always a pointer to \ref Buffer. */
            PWSTR Pointer;
        };
    };
    /** The buffer containing the contents of the string. */
    WCHAR Buffer[1];
} PH_STRING, *PPH_STRING;

PHLIBAPI
PPH_STRING
NTAPI
PhCreateString(
    __in PWSTR Buffer
    );

PHLIBAPI
PPH_STRING
NTAPI
PhCreateStringEx(
    __in_opt PWSTR Buffer,
    __in SIZE_T Length
    );

PHLIBAPI
PPH_STRING
NTAPI
PhCreateStringFromAnsi(
    __in PSTR Buffer
    );

PHLIBAPI
PPH_STRING
NTAPI
PhCreateStringFromAnsiEx(
    __in PSTR Buffer,
    __in SIZE_T Length
    );

PHLIBAPI
PPH_STRING
NTAPI
PhReferenceEmptyString();

PHLIBAPI
PPH_STRING
NTAPI
PhConcatStrings(
    __in ULONG Count,
    ...
    );

#define PH_CONCAT_STRINGS_LENGTH_CACHE_SIZE 16

PHLIBAPI
PPH_STRING
NTAPI
PhConcatStrings_V(
    __in ULONG Count,
    __in va_list ArgPtr
    );

PHLIBAPI
PPH_STRING
NTAPI
PhConcatStrings2(
    __in PWSTR String1,
    __in PWSTR String2
    );

PHLIBAPI
PPH_STRING
NTAPI
PhFormatString(
    __in __format_string PWSTR Format,
    ...
    );

PHLIBAPI
PPH_STRING
NTAPI
PhFormatString_V(
    __in __format_string PWSTR Format,
    __in va_list ArgPtr
    );

/**
 * Retrieves a pointer to a string object's buffer 
 * or returns NULL.
 *
 * \param String A pointer to a string object.
 *
 * \return A pointer to the string object's buffer 
 * if the supplied pointer is non-NULL, otherwise 
 * NULL.
 */
FORCEINLINE PWSTR PhGetString(
    __in_opt PPH_STRING String
    )
{
    if (String)
        return String->Buffer;
    else
        return NULL;
}

FORCEINLINE PH_STRINGREF PhGetStringRef(
    __in_opt PPH_STRING String
    )
{
    PH_STRINGREF sr;

    if (String)
    {
        sr = String->sr;
    }
    else
    {
        PhInitializeEmptyStringRef(&sr);
    }

    return sr;
}

/**
 * Retrieves a pointer to a string object's buffer 
 * or returns an empty string.
 *
 * \param String A pointer to a string object.
 *
 * \return A pointer to the string object's buffer 
 * if the supplied pointer is non-NULL, otherwise 
 * an empty string.
 */
FORCEINLINE PWSTR PhGetStringOrEmpty(
    __in_opt PPH_STRING String
    )
{
    if (String)
        return String->Buffer;
    else
        return L"";
}

FORCEINLINE PH_STRINGREF PhGetStringRefOrEmpty(
    __in_opt PPH_STRING String
    )
{
    PH_STRINGREF sr;

    if (String)
    {
        sr = String->sr;
    }
    else
    {
        sr.Length = 0;
        sr.Buffer = L"";
    }

    return sr;
}

/**
 * Retrieves a pointer to a string object's buffer 
 * or returns the specified alternative string.
 *
 * \param String A pointer to a string object.
 * \param DefaultString The alternative string.
 *
 * \return A pointer to the string object's buffer 
 * if the supplied pointer is non-NULL, otherwise 
 * the specified alternative string.
 */
FORCEINLINE PWSTR PhGetStringOrDefault(
    __in_opt PPH_STRING String,
    __in PWSTR DefaultString
    )
{
    if (String)
        return String->Buffer;
    else
        return DefaultString;
}

/**
 * Determines whether a string is null or empty.
 *
 * \param String A pointer to a string object.
 */
FORCEINLINE BOOLEAN PhIsNullOrEmptyString(
    __in_opt PPH_STRING String
    )
{
    return !String || String->Length == 0;
}

/**
 * Duplicates a string.
 *
 * \param String A string to duplicate.
 */
FORCEINLINE PPH_STRING PhDuplicateString(
    __in PPH_STRING String
    )
{
    return PhCreateStringEx(String->Buffer, String->Length);
}

/**
 * Compares two strings.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 */
FORCEINLINE LONG PhCompareString(
    __in PPH_STRING String1,
    __in PPH_STRING String2,
    __in BOOLEAN IgnoreCase
    )
{
    if (!IgnoreCase)
        return wcscmp(String1->Buffer, String2->Buffer);
    else
        return RtlCompareUnicodeString(&String1->us, &String2->us, TRUE); // faster than wcsicmp
}

/**
 * Compares two strings.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 */
FORCEINLINE LONG PhCompareString2(
    __in PPH_STRING String1,
    __in PWSTR String2,
    __in BOOLEAN IgnoreCase
    )
{
    if (!IgnoreCase)
    {
        return wcscmp(String1->Buffer, String2);
    }
    else
    {
        PH_STRINGREF sr2;

        PhInitializeStringRef(&sr2, String2);

        return RtlCompareUnicodeString(&String1->us, &sr2.us, TRUE);
    }
}

/**
 * Compares two strings, handling NULL strings.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 */
FORCEINLINE LONG PhCompareStringWithNull(
    __in_opt PPH_STRING String1,
    __in_opt PPH_STRING String2,
    __in BOOLEAN IgnoreCase
    )
{
    if (String1 && String2)
    {
        return PhCompareString(String1, String2, IgnoreCase);
    }
    else if (!String1)
    {
        return !String2 ? 0 : -1;
    }
    else
    {
        return 1;
    }
}

/**
 * Determines whether two strings are equal.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 */
FORCEINLINE BOOLEAN PhEqualString(
    __in PPH_STRING String1,
    __in PPH_STRING String2,
    __in BOOLEAN IgnoreCase
    )
{
    if (!IgnoreCase)
        return wcscmp(String1->Buffer, String2->Buffer) == 0;
    else
        return RtlEqualUnicodeString(&String1->us, &String2->us, TRUE);
}

/**
 * Determines whether two strings are equal.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 */
FORCEINLINE BOOLEAN PhEqualString2(
    __in PPH_STRING String1,
    __in PWSTR String2,
    __in BOOLEAN IgnoreCase
    )
{
    if (!IgnoreCase)
    {
        return wcscmp(String1->Buffer, String2) == 0;
    }
    else
    {
        PH_STRINGREF sr2;

        PhInitializeStringRef(&sr2, String2);

        return RtlEqualUnicodeString(&String1->us, &sr2.us, TRUE);
    }
}

/**
 * Determines whether a string starts with another.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 *
 * \return TRUE if \a String1 starts with \a String2, 
 * otherwise FALSE.
 */
FORCEINLINE BOOLEAN PhStartsWithString(
    __in PPH_STRING String1,
    __in PPH_STRING String2,
    __in BOOLEAN IgnoreCase
    )
{
    return RtlPrefixUnicodeString(&String2->us, &String1->us, IgnoreCase);
}

/**
 * Determines whether a string starts with another.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 *
 * \return TRUE if \a String1 starts with \a String2, 
 * otherwise FALSE.
 */
FORCEINLINE BOOLEAN PhStartsWithString2(
    __in PPH_STRING String1,
    __in PWSTR String2,
    __in BOOLEAN IgnoreCase
    )
{
    PH_STRINGREF sr2;

    PhInitializeStringRef(&sr2, String2);

    return RtlPrefixUnicodeString(&sr2.us, &String1->us, IgnoreCase);
}

/**
 * Determines whether a string ends with another.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 *
 * \return TRUE if \a String1 ends with \a String2, 
 * otherwise FALSE.
 */
FORCEINLINE BOOLEAN PhEndsWithString(
    __in PPH_STRING String1,
    __in PPH_STRING String2,
    __in BOOLEAN IgnoreCase
    )
{
    PH_STRINGREF sr1;

    if (String2->Length > String1->Length)
        return FALSE;

    sr1.Buffer = &String1->Buffer[(String1->Length - String2->Length) / sizeof(WCHAR)];
    sr1.Length = String2->Length;

    return RtlEqualUnicodeString(&sr1.us, &String2->us, IgnoreCase);
}

/**
 * Determines whether a string ends with another.
 *
 * \param String1 The first string.
 * \param String2 The second string.
 * \param IgnoreCase Whether to ignore character cases.
 *
 * \return TRUE if \a String1 ends with \a String2, 
 * otherwise FALSE.
 */
FORCEINLINE BOOLEAN PhEndsWithString2(
    __in PPH_STRING String1,
    __in PWSTR String2,
    __in BOOLEAN IgnoreCase
    )
{
    PH_STRINGREF sr1;
    PH_STRINGREF sr2;

    PhInitializeStringRef(&sr2, String2);

    if (sr2.Length > String1->Length)
        return FALSE;

    sr1.Buffer = &String1->Buffer[(String1->Length - sr2.Length) / sizeof(WCHAR)];
    sr1.Length = sr2.Length;

    return RtlEqualUnicodeString(&sr1.us, &sr2.us, IgnoreCase);
}

/**
 * Locates a character in a string.
 *
 * \param String The string to search.
 * \param StartIndex The index, in characters, to start searching at.
 * \param Char The character to search for.
 *
 * \return The index, in characters, of the first occurrence of 
 * \a Char in \a String after \a StartIndex. If \a Char was not 
 * found, -1 is returned.
 */
FORCEINLINE ULONG PhFindCharInString(
    __in PPH_STRING String,
    __in ULONG StartIndex,
    __in WCHAR Char
    )
{
    PWSTR location;

    location = wcschr(&String->Buffer[StartIndex], Char);

    if (location)
        return (ULONG)(location - String->Buffer);
    else
        return -1;
}

/**
 * Locates a character in a string, backwards.
 *
 * \param String The string to search.
 * \param StartIndex The index, in characters, to start searching at.
 * \param Char The character to search for.
 *
 * \return The index, in characters, of the last occurrence of 
 * \a Char in \a String after \a StartIndex. If \a Char was not 
 * found, -1 is returned.
 */
FORCEINLINE ULONG PhFindLastCharInString(
    __in PPH_STRING String,
    __in ULONG StartIndex,
    __in WCHAR Char
    )
{
    PWSTR location;

    location = wcsrchr(&String->Buffer[StartIndex], Char);

    if (location)
        return (ULONG)(location - String->Buffer);
    else
        return -1;
}

/**
 * Locates a string in a string.
 *
 * \param String1 The string to search.
 * \param StartIndex The index, in characters, to start searching at.
 * \param String2 The string to search for.
 *
 * \return The index, in characters, of the first occurrence of 
 * \a String2 in \a String1 after \a StartIndex. If \a String2 was not 
 * found, -1 is returned.
 */
FORCEINLINE ULONG PhFindStringInString(
    __in PPH_STRING String1,
    __in ULONG StartIndex,
    __in PWSTR String2
    )
{
    PWSTR location;

    location = wcsstr(&String1->Buffer[StartIndex], String2);

    if (location)
        return (ULONG)(location - String1->Buffer);
    else
        return -1;
}

/**
 * Converts a string to lowercase in-place.
 *
 * \param String The string to convert.
 */
FORCEINLINE VOID PhLowerString(
    __inout PPH_STRING String
    )
{
    _wcslwr(String->Buffer);
}

/**
 * Converts a string to uppercase in-place.
 *
 * \param String The string to convert.
 */
FORCEINLINE VOID PhUpperString(
    __inout PPH_STRING String
    )
{
    _wcsupr(String->Buffer);
}

/**
 * Creates a substring of a string.
 *
 * \param String The original string.
 * \param StartIndex The start index, in characters.
 * \param Count The number of characters to use.
 */
FORCEINLINE PPH_STRING PhSubstring(
    __in PPH_STRING String,
    __in ULONG StartIndex,
    __in ULONG Count
    )
{
    return PhCreateStringEx(&String->Buffer[StartIndex], Count * sizeof(WCHAR));
}

/**
 * Updates a string object's length with 
 * its true length as determined by an 
 * embedded null terminator.
 *
 * \param String The string to modify.
 *
 * \remarks Use this function after modifying a string 
 * object's buffer manually.
 */
FORCEINLINE VOID PhTrimToNullTerminatorString(
    __inout PPH_STRING String
    )
{
    String->Length = String->MaximumLength = (USHORT)(wcslen(String->Buffer) * sizeof(WCHAR));
}

// ansi string

#ifndef _PH_BASESUP_PRIVATE
extern PPH_OBJECT_TYPE PhAnsiStringType;
#endif

/**
 * An ANSI string structure.
 */
typedef struct _PH_ANSI_STRING
{
    union
    {
        /** An embedded ANSI_STRING structure. */
        ANSI_STRING as;
        struct
        {
            /** The length, in bytes, of the string. */
            USHORT Length;
            /** Unused and always equal to \ref Length. */
            USHORT MaximumLength;
            /** Unused and always a pointer to \ref Buffer. */
            PSTR Pointer;
        };
    };
    /** The buffer containing the contents of the string. */
    CHAR Buffer[1];
} PH_ANSI_STRING, *PPH_ANSI_STRING;

PHLIBAPI
PPH_ANSI_STRING
NTAPI
PhCreateAnsiString(
    __in PSTR Buffer
    );

PHLIBAPI
PPH_ANSI_STRING
NTAPI
PhCreateAnsiStringEx(
    __in_opt PSTR Buffer,
    __in SIZE_T Length
    );

PHLIBAPI
PPH_ANSI_STRING
NTAPI
PhCreateAnsiStringFromUnicode(
    __in PWSTR Buffer
    );

PHLIBAPI
PPH_ANSI_STRING
NTAPI
PhCreateAnsiStringFromUnicodeEx(
    __in PWSTR Buffer,
    __in SIZE_T Length
    );

// full string

#ifndef _PH_BASESUP_PRIVATE
extern PPH_OBJECT_TYPE PhFullStringType;
#endif

/**
 * A full Unicode string object.
 *
 * \remarks This string object is similar to PH_STRING except 
 * that the length is not restricted to 16 bits. Unlike 
 * PH_STRING and PH_ANSI_STRING, this object is mutable.
 */
typedef struct _PH_FULL_STRING
{
    /** The length, in bytes, of the string. */
    SIZE_T Length;
    /** The allocated length of the string, in bytes, not including the null terminator. */
    SIZE_T AllocatedLength;
    /** The buffer containing the contents of the string. */
    PWSTR Buffer;
} PH_FULL_STRING, *PPH_FULL_STRING;

PHLIBAPI
PPH_FULL_STRING
NTAPI
PhCreateFullString(
    __in PWSTR Buffer
    );

PHLIBAPI
PPH_FULL_STRING
NTAPI
PhCreateFullString2(
    __in SIZE_T InitialCapacity
    );

PHLIBAPI
PPH_FULL_STRING
NTAPI
PhCreateFullStringEx(
    __in_opt PWSTR Buffer,
    __in SIZE_T Length,
    __in_opt SIZE_T InitialCapacity
    );

PHLIBAPI
VOID
NTAPI
PhResizeFullString(
    __inout PPH_FULL_STRING String,
    __in SIZE_T NewLength,
    __in BOOLEAN Growing
    );

PHLIBAPI
VOID
NTAPI
PhAppendFullString(
    __inout PPH_FULL_STRING String,
    __in PPH_STRING ShortString
    );

PHLIBAPI
VOID
NTAPI
PhAppendFullString2(
    __inout PPH_FULL_STRING String,
    __in PWSTR StringZ
    );

PHLIBAPI
VOID
NTAPI
PhAppendFullStringEx(
    __inout PPH_FULL_STRING String,
    __in_opt PWSTR Buffer,
    __in SIZE_T Length
    );

PHLIBAPI
VOID
NTAPI
PhAppendCharFullString(
    __inout PPH_FULL_STRING String,
    __in WCHAR Character
    );

PHLIBAPI
VOID
NTAPI
PhAppendCharFullString2(
    __inout PPH_FULL_STRING String,
    __in WCHAR Character,
    __in SIZE_T Count
    );

PHLIBAPI
VOID
NTAPI
PhAppendFormatFullString(
    __inout PPH_FULL_STRING String,
    __in __format_string PWSTR Format,
    ...
    );

PHLIBAPI
VOID
NTAPI
PhInsertFullString(
    __inout PPH_FULL_STRING String,
    __in SIZE_T Index,
    __in PPH_STRING ShortString
    );

PHLIBAPI
VOID
NTAPI
PhInsertFullString2(
    __inout PPH_FULL_STRING String,
    __in SIZE_T Index,
    __in PWSTR StringZ
    );

PHLIBAPI
VOID
NTAPI
PhInsertFullStringEx(
    __inout PPH_FULL_STRING String,
    __in SIZE_T Index,
    __in_opt PWSTR Buffer,
    __in SIZE_T Length
    );

PHLIBAPI
VOID
NTAPI
PhRemoveFullString(
    __inout PPH_FULL_STRING String,
    __in SIZE_T StartIndex,
    __in SIZE_T Count
    );

// stringbuilder

/**
 * A string builder structure.
 * The string builder object allows you to easily
 * construct complex strings without allocating 
 * a great number of strings in the process.
 */
typedef struct _PH_STRING_BUILDER
{
    /** Allocated length of the string, not including the null terminator. */
    ULONG AllocatedLength;
    /**
     * The constructed string.
     * \a String will be allocated for \a AllocatedLength, 
     * but we will modify the \a Length field to be the 
     * correct length.
     */
    PPH_STRING String;
} PH_STRING_BUILDER, *PPH_STRING_BUILDER;

PHLIBAPI
VOID
NTAPI
PhInitializeStringBuilder(
    __out PPH_STRING_BUILDER StringBuilder,
    __in ULONG InitialCapacity
    );

PHLIBAPI
VOID
NTAPI
PhDeleteStringBuilder(
    __inout PPH_STRING_BUILDER StringBuilder
    );

PHLIBAPI
PPH_STRING
NTAPI
PhReferenceStringBuilderString(
    __in PPH_STRING_BUILDER StringBuilder
    );

PHLIBAPI
PPH_STRING
NTAPI
PhFinalStringBuilderString(
    __inout PPH_STRING_BUILDER StringBuilder
    );

PHLIBAPI
VOID
NTAPI
PhAppendStringBuilder(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in PPH_STRING String
    );

PHLIBAPI
VOID
NTAPI
PhAppendStringBuilder2(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in PWSTR String
    );

PHLIBAPI
VOID
NTAPI
PhAppendStringBuilderEx(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in_opt PWSTR String,
    __in ULONG Length
    );

PHLIBAPI
VOID
NTAPI
PhAppendCharStringBuilder(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in WCHAR Character
    );

PHLIBAPI
VOID
NTAPI
PhAppendCharStringBuilder2(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in WCHAR Character,
    __in ULONG Count
    );

PHLIBAPI
VOID
NTAPI
PhAppendFormatStringBuilder(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in __format_string PWSTR Format,
    ...
    );

PHLIBAPI
VOID
NTAPI
PhInsertStringBuilder(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in ULONG Index,
    __in PPH_STRING String
    );

PHLIBAPI
VOID
NTAPI
PhInsertStringBuilder2(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in ULONG Index,
    __in PWSTR String
    );

PHLIBAPI
VOID
NTAPI
PhInsertStringBuilderEx(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in ULONG Index,
    __in_opt PWSTR String,
    __in ULONG Length
    );

PHLIBAPI
VOID
NTAPI
PhRemoveStringBuilder(
    __inout PPH_STRING_BUILDER StringBuilder,
    __in ULONG StartIndex,
    __in ULONG Count
    );

// list

#ifndef _PH_BASESUP_PRIVATE
extern PPH_OBJECT_TYPE PhListType;
#endif

/**
 * A list structure.
 * Storage is automatically allocated for new 
 * elements.
 */
typedef struct _PH_LIST
{
    /** The number of items in the list. */
    ULONG Count;
    /** The number of items for which storage is allocated. */
    ULONG AllocatedCount;
    /** The array of list items. */
    PPVOID Items;
} PH_LIST, *PPH_LIST;

PHLIBAPI
PPH_LIST
NTAPI
PhCreateList(
    __in ULONG InitialCapacity
    );

PHLIBAPI
VOID
NTAPI
PhResizeList(
    __inout PPH_LIST List,
    __in ULONG NewCapacity
    );

PHLIBAPI
VOID
NTAPI
PhAddItemList(
    __inout PPH_LIST List,
    __in PVOID Item
    );

PHLIBAPI
VOID
NTAPI
PhAddItemsList(
    __inout PPH_LIST List,
    __in PPVOID Items,
    __in ULONG Count
    );

PHLIBAPI
VOID
NTAPI
PhClearList(
    __inout PPH_LIST List
    );

__success(return != -1)
PHLIBAPI
ULONG
NTAPI
PhFindItemList(
    __in PPH_LIST List,
    __in PVOID Item
    );

PHLIBAPI
VOID
NTAPI
PhInsertItemList(
    __inout PPH_LIST List,
    __in ULONG Index,
    __in PVOID Item
    );

PHLIBAPI
VOID
NTAPI
PhInsertItemsList(
    __inout PPH_LIST List,
    __in ULONG Index,
    __in PPVOID Items,
    __in ULONG Count
    );

PHLIBAPI
VOID
NTAPI
PhRemoveItemList(
    __inout PPH_LIST List,
    __in ULONG Index
    );

PHLIBAPI
VOID
NTAPI
PhRemoveItemsList(
    __inout PPH_LIST List,
    __in ULONG StartIndex,
    __in ULONG Count
    );

/**
 * A comparison function.
 *
 * \param Item1 The first item.
 * \param Item2 The second item.
 * \param Context A user-defined value.
 *
 * \return
 * \li A positive value if \a Item1 > \a Item2,
 * \li A negative value if \a Item1 < \a Item2, and
 * \li 0 if \a Item1 = \a Item2.
 */
typedef INT (NTAPI *PPH_COMPARE_FUNCTION)(
    __in PVOID Item1,
    __in PVOID Item2,
    __in_opt PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhSortList(
    __in PPH_LIST List,
    __in PPH_COMPARE_FUNCTION CompareFunction,
    __in_opt PVOID Context
    );

// pointer list

#ifndef _PH_BASESUP_PRIVATE
extern PPH_OBJECT_TYPE PhPointerListType;
#endif

/**
 * A pointer list structure.
 * The pointer list is similar to the normal list 
 * structure, but both insertions and deletions 
 * occur in constant time. The list is not ordered.
 */
typedef struct _PH_POINTER_LIST
{
    /** The number of pointers in the list. */
    ULONG Count;
    /** The number of pointers for which storage is allocated. */
    ULONG AllocatedCount;
    /** Index into pointer array for free list. */
    ULONG FreeEntry;
    /** Index of next usable index into pointer array. */
    ULONG NextEntry;
    /** The array of pointers. */
    PPVOID Items;
} PH_POINTER_LIST, *PPH_POINTER_LIST;

#define PH_IS_LIST_POINTER_VALID(Pointer) (!((ULONG_PTR)(Pointer) & 0x1))

PHLIBAPI
PPH_POINTER_LIST
NTAPI
PhCreatePointerList(
    __in ULONG InitialCapacity
    );

PHLIBAPI
HANDLE
NTAPI
PhAddItemPointerList(
    __inout PPH_POINTER_LIST PointerList,
    __in PVOID Pointer
    );

PHLIBAPI
BOOLEAN
NTAPI
PhEnumPointerListEx(
    __in PPH_POINTER_LIST PointerList,
    __inout PULONG EnumerationKey,
    __out PPVOID Pointer,
    __out PHANDLE PointerHandle
    );

PHLIBAPI
HANDLE
NTAPI
PhFindItemPointerList(
    __in PPH_POINTER_LIST PointerList,
    __in PVOID Pointer
    );

PHLIBAPI
VOID
NTAPI
PhRemoveItemPointerList(
    __inout PPH_POINTER_LIST PointerList,
    __in HANDLE PointerHandle
    );

FORCEINLINE BOOLEAN PhEnumPointerList(
    __in PPH_POINTER_LIST PointerList,
    __inout PULONG EnumerationKey,
    __out PPVOID Pointer
    )
{
    while (*EnumerationKey < PointerList->NextEntry)
    {
        PVOID pointer = PointerList->Items[*EnumerationKey];

        (*EnumerationKey)++;

        if (PH_IS_LIST_POINTER_VALID(pointer))
        {
            *Pointer = pointer;
            return TRUE;
        }
    }

    return FALSE;
}

// queue

#ifndef _PH_BASESUP_PRIVATE
extern PPH_OBJECT_TYPE PhQueueType;
#endif

/**
 * A queue structure.
 * Storage is automatically allocated for new 
 * elements.
 */
typedef struct _PH_QUEUE
{
    /** The number of items in the queue. */
    ULONG Count;
    /** The number of items for which storage is allocated. */
    ULONG AllocatedCount;
    /** The array of queue items. */
    PPVOID Items;
    /** The index of the first slot in the queue. */
    ULONG Head;
    /** The index of the last available slot in the queue. */
    ULONG Tail;
} PH_QUEUE, *PPH_QUEUE;

PHLIBAPI
PPH_QUEUE
NTAPI
PhCreateQueue(
    __in ULONG InitialCapacity
    );

PHLIBAPI
VOID
NTAPI
PhEnqueueItemQueue(
    __inout PPH_QUEUE Queue,
    __in PVOID Item
    );

PHLIBAPI
BOOLEAN
NTAPI
PhDequeueItemQueue(
    __inout PPH_QUEUE Queue,
    __out PPVOID Item
    );

PHLIBAPI
BOOLEAN
NTAPI
PhPeekItemQueue(
    __in PPH_QUEUE Queue,
    __out PPVOID Item
    );

// hashtable

#ifndef _PH_BASESUP_PRIVATE
extern PPH_OBJECT_TYPE PhHashtableType;
#endif

typedef struct _PH_HASHTABLE_ENTRY
{
    /** Hash code of the entry. -1 if entry is unused. */
    ULONG HashCode;
    /** Either the index of the next entry in the bucket, 
     * the index of the next free entry, or -1 for invalid.
     */
    ULONG Next;
    /** The beginning of user data. */
    QUAD Body;
} PH_HASHTABLE_ENTRY, *PPH_HASHTABLE_ENTRY;

/**
 * A comparison function used by a hashtable.
 *
 * \param Entry1 The first entry.
 * \param Entry2 The second entry.
 *
 * \return TRUE if the entries are equal, otherwise 
 * FALSE.
 */
typedef BOOLEAN (NTAPI *PPH_HASHTABLE_COMPARE_FUNCTION)(
    __in PVOID Entry1,
    __in PVOID Entry2
    );

/**
 * A hash function used by a hashtable.
 *
 * \param Entry The entry.
 *
 * \return A hash code for the entry.
 *
 * \remarks
 * \li Two entries which are considered to be equal 
 * by the comparison function must be given the same 
 * hash code.
 * \li Two different entries do not have to be given 
 * different hash codes.
 */
typedef ULONG (NTAPI *PPH_HASHTABLE_HASH_FUNCTION)(
    __in PVOID Entry
    );

// Use power-of-two sizes instead of primes
#define PH_HASHTABLE_POWER_OF_TWO_SIZE

// Enables 2^32-1 possible hash codes instead of only 2^31
//#define PH_HASHTABLE_FULL_HASH

/**
 * A hashtable structure.
 */
typedef struct _PH_HASHTABLE
{
    /** Size of user data in each entry. */
    ULONG EntrySize;
    /** The comparison function. */
    PPH_HASHTABLE_COMPARE_FUNCTION CompareFunction;
    /** The hash function. */
    PPH_HASHTABLE_HASH_FUNCTION HashFunction;

    /** The number of allocated buckets. */
    ULONG AllocatedBuckets;
    /** The bucket array. */
    PULONG Buckets;
    /** The number of allocated entries. */
    ULONG AllocatedEntries;
    /** The entry array. */
    PVOID Entries;

    /** Number of entries in the hashtable. */
    ULONG Count;
    /** Index into entry array for free list. */
    ULONG FreeEntry;
    /** Index of next usable index into entry array, a.k.a. the 
     * count of entries that were ever allocated.
     */
    ULONG NextEntry;
} PH_HASHTABLE, *PPH_HASHTABLE;

#define PH_HASHTABLE_ENTRY_SIZE(InnerSize) (FIELD_OFFSET(PH_HASHTABLE_ENTRY, Body) + (InnerSize))
#define PH_HASHTABLE_GET_ENTRY(Hashtable, Index) \
    ((PPH_HASHTABLE_ENTRY)PTR_ADD_OFFSET((Hashtable)->Entries, \
    PH_HASHTABLE_ENTRY_SIZE((Hashtable)->EntrySize) * (Index)))
#define PH_HASHTABLE_GET_ENTRY_INDEX(Hashtable, Entry) \
    ((ULONG)(PTR_ADD_OFFSET(Entry, -(Hashtable)->Entries) / \
    PH_HASHTABLE_ENTRY_SIZE((Hashtable)->EntrySize)))

PHLIBAPI
PPH_HASHTABLE
NTAPI
PhCreateHashtable(
    __in ULONG EntrySize,
    __in PPH_HASHTABLE_COMPARE_FUNCTION CompareFunction,
    __in PPH_HASHTABLE_HASH_FUNCTION HashFunction,
    __in ULONG InitialCapacity
    );

PHLIBAPI
PVOID
NTAPI
PhAddEntryHashtable(
    __inout PPH_HASHTABLE Hashtable,
    __in PVOID Entry
    );

PHLIBAPI
PVOID
NTAPI
PhAddEntryHashtableEx(
    __inout PPH_HASHTABLE Hashtable,
    __in PVOID Entry,
    __out_opt PBOOLEAN Added
    );

PHLIBAPI
VOID
NTAPI
PhClearHashtable(
    __inout PPH_HASHTABLE Hashtable
    );

PHLIBAPI
BOOLEAN
NTAPI
PhEnumHashtable(
    __in PPH_HASHTABLE Hashtable,
    __out PPVOID Entry,
    __inout PULONG EnumerationKey
    );

PHLIBAPI
PVOID
NTAPI
PhFindEntryHashtable(
    __in PPH_HASHTABLE Hashtable,
    __in PVOID Entry
    );

PHLIBAPI
BOOLEAN
NTAPI
PhRemoveEntryHashtable(
    __inout PPH_HASHTABLE Hashtable,
    __in PVOID Entry
    );

#define PhHashBytes PhHashBytesSdbm

#define PhHashBytesHsieh PhfHashBytesHsieh
PHLIBAPI
ULONG
FASTCALL
PhfHashBytesHsieh(
    __in PUCHAR Bytes,
    __in ULONG Length
    );

#define PhHashBytesMurmur PhfHashBytesMurmur
PHLIBAPI
ULONG
FASTCALL
PhfHashBytesMurmur(
    __in PUCHAR Bytes,
    __in ULONG Length
    );

#define PhHashBytesSdbm PhfHashBytesSdbm
PHLIBAPI
ULONG
FASTCALL
PhfHashBytesSdbm(
    __in PUCHAR Bytes,
    __in ULONG Length
    );

FORCEINLINE ULONG PhHashInt32(
    __in ULONG Value
    )
{
    // Java style.
    Value ^= (Value >> 20) ^ (Value >> 12);
    return Value ^ (Value >> 7) ^ (Value >> 4);
}

FORCEINLINE ULONG PhHashInt64(
    __in ULONG64 Value
    )
{
    // http://www.concentric.net/~Ttwang/tech/inthash.htm

    Value = ~Value + (Value << 18);
    Value ^= Value >> 31;
    Value *= 21;
    Value ^= Value >> 11;
    Value += Value << 6;
    Value ^= Value >> 22;

    return (ULONG)Value;
}

// simple hashtable

typedef struct _PH_KEY_VALUE_PAIR
{
    PVOID Key;
    PVOID Value;
} PH_KEY_VALUE_PAIR, *PPH_KEY_VALUE_PAIR;

PHLIBAPI
PPH_HASHTABLE
NTAPI
PhCreateSimpleHashtable(
    __in ULONG InitialCapacity
    );

PHLIBAPI
PVOID
NTAPI
PhAddItemSimpleHashtable(
    __inout PPH_HASHTABLE SimpleHashtable,
    __in_opt PVOID Key,
    __in_opt PVOID Value
    );

PHLIBAPI
PPVOID
NTAPI
PhFindItemSimpleHashtable(
    __in PPH_HASHTABLE SimpleHashtable,
    __in_opt PVOID Key
    );

PHLIBAPI
BOOLEAN
NTAPI
PhRemoveItemSimpleHashtable(
    __inout PPH_HASHTABLE SimpleHashtable,
    __in_opt PVOID Key
    );

// free list

typedef struct _PH_FREE_LIST
{
    SLIST_HEADER ListHead;

    ULONG Count;
    ULONG MaximumCount;
    SIZE_T Size;
} PH_FREE_LIST, *PPH_FREE_LIST;

typedef struct _PH_FREE_LIST_ENTRY
{
    SLIST_ENTRY ListEntry;
    QUAD_PTR Body;
} PH_FREE_LIST_ENTRY, *PPH_FREE_LIST_ENTRY;

#ifdef _M_IX86
C_ASSERT(FIELD_OFFSET(PH_FREE_LIST_ENTRY, ListEntry) == 0x0);
C_ASSERT(FIELD_OFFSET(PH_FREE_LIST_ENTRY, Body) == 0x8);
#else
C_ASSERT(FIELD_OFFSET(PH_FREE_LIST_ENTRY, ListEntry) == 0x0);
C_ASSERT(FIELD_OFFSET(PH_FREE_LIST_ENTRY, Body) == 0x10);
#endif

PHLIBAPI
VOID
NTAPI
PhInitializeFreeList(
    __out PPH_FREE_LIST FreeList,
    __in SIZE_T Size,
    __in ULONG MaximumCount
    );

PHLIBAPI
VOID
NTAPI
PhDeleteFreeList(
    __inout PPH_FREE_LIST FreeList
    );

PHLIBAPI
PVOID
NTAPI
PhAllocateFromFreeList(
    __inout PPH_FREE_LIST FreeList
    );

PHLIBAPI
VOID
NTAPI
PhFreeToFreeList(
    __inout PPH_FREE_LIST FreeList,
    __in PVOID Memory
    );

// callback

/**
 * A callback function.
 *
 * \param Parameter A value given to all callback 
 * functions being notified.
 * \param Context A user-defined value passed 
 * to PhRegisterCallback().
 */
typedef VOID (NTAPI *PPH_CALLBACK_FUNCTION)(
    __in_opt PVOID Parameter,
    __in_opt PVOID Context
    );

/**
 * A callback registration structure.
 */
typedef struct _PH_CALLBACK_REGISTRATION
{
    /** The list entry in the callbacks list. */
    LIST_ENTRY ListEntry;
    /** The callback function. */
    PPH_CALLBACK_FUNCTION Function;
    /** A user-defined value to be passed to the 
     * callback function. */
    PVOID Context;
    /** A value indicating whether the registration 
     * structure is being used. */
    LONG Busy;
    /** Whether the registration structure is being 
     * removed. */
    BOOLEAN Unregistering;
    BOOLEAN Reserved;
    /** Flags controlling the callback. */
    USHORT Flags;
} PH_CALLBACK_REGISTRATION, *PPH_CALLBACK_REGISTRATION;

/**
 * A callback structure.
 * The callback object allows multiple callback 
 * functions to be registered and notified in a 
 * thread-safe way.
 */
typedef struct _PH_CALLBACK
{
    /** The list of registered callbacks. */
    LIST_ENTRY ListHead;
    /** A lock protecting the callbacks list. */
    PH_QUEUED_LOCK ListLock;
    /** A condition variable pulsed when 
     * the callback becomes free. */
    PH_QUEUED_LOCK BusyCondition;
} PH_CALLBACK, *PPH_CALLBACK;

PHLIBAPI
VOID
NTAPI
PhInitializeCallback(
    __out PPH_CALLBACK Callback
    );

PHLIBAPI
VOID
NTAPI
PhDeleteCallback(
    __inout PPH_CALLBACK Callback
    );

PHLIBAPI
VOID
NTAPI
PhRegisterCallback(
    __inout PPH_CALLBACK Callback,
    __in PPH_CALLBACK_FUNCTION Function,
    __in_opt PVOID Context,
    __out PPH_CALLBACK_REGISTRATION Registration
    );

PHLIBAPI
VOID
NTAPI
PhRegisterCallbackEx(
    __inout PPH_CALLBACK Callback,
    __in PPH_CALLBACK_FUNCTION Function,
    __in_opt PVOID Context,
    __in USHORT Flags,
    __out PPH_CALLBACK_REGISTRATION Registration
    );

PHLIBAPI
VOID
NTAPI
PhUnregisterCallback(
    __inout PPH_CALLBACK Callback,
    __inout PPH_CALLBACK_REGISTRATION Registration
    );

PHLIBAPI
VOID
NTAPI
PhInvokeCallback(
    __in PPH_CALLBACK Callback,
    __in_opt PVOID Parameter
    );

// callbacksync

typedef struct _PH_CALLBACK_SYNC
{
    PH_CALLBACK Callback;
    ULONG Target;
    PVOID Parameter;
    ULONG Value;
} PH_CALLBACK_SYNC, *PPH_CALLBACK_SYNC;

FORCEINLINE VOID PhInitializeCallbackSync(
    __out PPH_CALLBACK_SYNC CallbackSync,
    __in ULONG Target,
    __in_opt PVOID Parameter
    )
{
    PhInitializeCallback(&CallbackSync->Callback);
    CallbackSync->Target = Target;
    CallbackSync->Parameter = Parameter;
    CallbackSync->Value = 0;
}

FORCEINLINE VOID PhIncrementCallbackSync(
    __in PPH_CALLBACK_SYNC CallbackSync
    )
{
    if ((ULONG)_InterlockedIncrement(&CallbackSync->Value) == CallbackSync->Target)
        PhInvokeCallback(&CallbackSync->Callback, CallbackSync->Parameter); 
}

FORCEINLINE VOID PhIncrementMultipleCallbackSync(
    __in PPH_CALLBACK_SYNC CallbackSync
    )
{
    if ((ULONG)_InterlockedIncrement(&CallbackSync->Value) >= CallbackSync->Target)
        PhInvokeCallback(&CallbackSync->Callback, CallbackSync->Parameter); 
}

// general

PHLIBAPI
ULONG
NTAPI
PhGetPrimeNumber(
    __in ULONG Minimum
    );

PHLIBAPI
ULONG
NTAPI
PhRoundUpToPowerOfTwo(
    __in ULONG Number
    );

PHLIBAPI
ULONG
NTAPI
PhExponentiate(
    __in ULONG Base,
    __in ULONG Exponent
    );

PHLIBAPI
ULONG64
NTAPI
PhExponentiate64(
    __in ULONG64 Base,
    __in ULONG Exponent
    );

PHLIBAPI
ULONG
NTAPI
PhLog2(
    __in ULONG Exponent
    );

PHLIBAPI
BOOLEAN
NTAPI
PhHexStringToBuffer(
    __in PPH_STRINGREF String,
    __out_bcount(String->Length / sizeof(WCHAR) / 2) PUCHAR Buffer
    );

PHLIBAPI
PPH_STRING
NTAPI
PhBufferToHexString(
    __in PUCHAR Buffer,
    __in ULONG Length
    );

PHLIBAPI
BOOLEAN
NTAPI
PhStringToInteger64(
    __in PPH_STRINGREF String,
    __in_opt ULONG Base,
    __out PLONG64 Integer
    );

PHLIBAPI
PPH_STRING
NTAPI
PhIntegerToString64(
    __in LONG64 Integer,
    __in_opt ULONG Base,
    __in BOOLEAN Signed
    );

#define PH_TIMESPAN_STR_LEN 30
#define PH_TIMESPAN_STR_LEN_1 (PH_TIMESPAN_STR_LEN + 1)

#define PH_TIMESPAN_HMS 0
#define PH_TIMESPAN_HMSM 1
#define PH_TIMESPAN_DHMS 2

PHLIBAPI
VOID
NTAPI
PhPrintTimeSpan(
    __out_ecount(PH_TIMESPAN_STR_LEN_1) PWSTR Destination,
    __in ULONG64 Ticks,
    __in_opt ULONG Mode
    );

// basesupa

PHLIBAPI
PPH_STRING
NTAPI
PhaCreateString(
    __in PWSTR Buffer
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaCreateStringEx(
    __in PWSTR Buffer,
    __in SIZE_T Length
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaDuplicateString(
    __in PPH_STRING String
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaConcatStrings(
    __in ULONG Count,
    ...
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaConcatStrings2(
    __in PWSTR String1,
    __in PWSTR String2
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaFormatString(
    __in __format_string PWSTR Format,
    ...
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaLowerString(
    __in PPH_STRING String
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaUpperString(
    __in PPH_STRING String
    );

PHLIBAPI
PPH_STRING
NTAPI
PhaSubstring(
    __in PPH_STRING String,
    __in ULONG StartIndex,
    __in ULONG Count
    );

// basesupx

PHLIBAPI
VOID
FASTCALL
PhxfAddInt32(
    __inout __needsAlign(16) PLONG A,
    __in __needsAlign(16) PLONG B,
    __in ULONG Count
    );

PHLIBAPI
VOID
FASTCALL
PhxfAddInt32U(
    __inout PLONG A,
    __in PLONG B,
    __in ULONG Count
    );

PHLIBAPI
VOID
FASTCALL
PhxfDivideSingleU(
    __inout PFLOAT A,
    __in PFLOAT B,
    __in ULONG Count
    );

PHLIBAPI
VOID
FASTCALL
PhxfDivideSingle2U(
    __inout PFLOAT A,
    __in FLOAT B,
    __in ULONG Count
    );

// error

PHLIBAPI
NTSTATUS
NTAPI
PhDosErrorToNtStatus(
    __in ULONG DosError
    );

PHLIBAPI
BOOLEAN
NTAPI
PhNtStatusFileNotFound(
    __in NTSTATUS Status
    );

// bintree

// Generic definitions

typedef enum _PH_TREE_ENUMERATION_ORDER
{
    TreeEnumerateInOrder,
    TreeEnumerateInReverseOrder
} PH_TREE_ENUMERATION_ORDER;

#define PhIsLeftChildElement(Links) ((Links)->Parent->Left == (Links))
#define PhIsRightChildElement(Links) ((Links)->Parent->Right == (Links))

// AVL trees

typedef struct _PH_AVL_LINKS
{
    struct _PH_AVL_LINKS *Parent;
    struct _PH_AVL_LINKS *Left;
    struct _PH_AVL_LINKS *Right;
    LONG Balance;
} PH_AVL_LINKS, *PPH_AVL_LINKS;

struct _PH_AVL_TREE;

typedef INT (NTAPI *PPH_AVL_TREE_COMPARE_FUNCTION)(
    __in PPH_AVL_LINKS Links1,
    __in PPH_AVL_LINKS Links2
    );

typedef struct _PH_AVL_TREE
{
    PH_AVL_LINKS Root; // Right contains real root
    ULONG Count;

    PPH_AVL_TREE_COMPARE_FUNCTION CompareFunction;
} PH_AVL_TREE, *PPH_AVL_TREE;

#define PH_AVL_TREE_INIT(CompareFunction) { { NULL, NULL, NULL, 0 }, 0, CompareFunction }

#define PhRootElementAvlTree(Tree) ((Tree)->Root.Right)

PHLIBAPI
VOID
NTAPI
PhInitializeAvlTree(
    __out PPH_AVL_TREE Tree,
    __in PPH_AVL_TREE_COMPARE_FUNCTION CompareFunction
    );

PHLIBAPI
PPH_AVL_LINKS
NTAPI
PhAddElementAvlTree(
    __inout PPH_AVL_TREE Tree,
    __out PPH_AVL_LINKS Element
    );

PHLIBAPI
VOID
NTAPI
PhRemoveElementAvlTree(
    __inout PPH_AVL_TREE Tree,
    __inout PPH_AVL_LINKS Element
    );

PHLIBAPI
PPH_AVL_LINKS
NTAPI
PhFindElementAvlTree(
    __in PPH_AVL_TREE Tree,
    __in PPH_AVL_LINKS Element
    );

PHLIBAPI
PPH_AVL_LINKS
NTAPI
PhMinimumElementAvlTree(
    __in PPH_AVL_TREE Tree
    );

PHLIBAPI
PPH_AVL_LINKS
NTAPI
PhMaximumElementAvlTree(
    __in PPH_AVL_TREE Tree
    );

PHLIBAPI
PPH_AVL_LINKS
NTAPI
PhSuccessorElementAvlTree(
    __in PPH_AVL_LINKS Element
    );

PHLIBAPI
PPH_AVL_LINKS
NTAPI
PhPredecessorElementAvlTree(
    __in PPH_AVL_LINKS Element
    );

typedef BOOLEAN (NTAPI *PPH_ENUM_AVL_TREE_CALLBACK)(
    __in PPH_AVL_TREE Tree,
    __in PPH_AVL_LINKS Element,
    __in_opt PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhEnumAvlTree(
    __in PPH_AVL_TREE Tree,
    __in PH_TREE_ENUMERATION_ORDER Order,
    __in PPH_ENUM_AVL_TREE_CALLBACK Callback,
    __in_opt PVOID Context
    );

// handle

struct _PH_HANDLE_TABLE;
typedef struct _PH_HANDLE_TABLE *PPH_HANDLE_TABLE;

typedef struct _PH_HANDLE_TABLE_ENTRY
{
    union
    {
        PVOID Object;
        ULONG_PTR Value;
        struct
        {
            /** The type of the entry; 1 if the entry is free, 
             * otherwise 0 if the entry is in use.
             */
            ULONG_PTR Type : 1;
            /** Whether the entry is not locked; 1 if the entry 
             * is not locked, otherwise 0 if the entry is locked. 
             */
            ULONG_PTR Locked : 1;
            ULONG_PTR Value : sizeof(ULONG_PTR) * 8 - 2;
        } TypeAndValue;
    };
    union
    {
        ACCESS_MASK GrantedAccess;
        ULONG NextFreeValue;
        ULONG_PTR Value2;
    };
} PH_HANDLE_TABLE_ENTRY, *PPH_HANDLE_TABLE_ENTRY;

#define PH_HANDLE_TABLE_SAFE
#define PH_HANDLE_TABLE_FREE_COUNT 64

#define PH_HANDLE_TABLE_STRICT_FIFO 0x1
#define PH_HANDLE_TABLE_VALID_FLAGS 0x1

VOID PhHandleTableInitialization();

PHLIBAPI
PPH_HANDLE_TABLE
NTAPI
PhCreateHandleTable();

PHLIBAPI
VOID
NTAPI
PhDestroyHandleTable(
    __in __post_invalid PPH_HANDLE_TABLE HandleTable
    );

PHLIBAPI
BOOLEAN
NTAPI
PhLockHandleTableEntry(
    __inout PPH_HANDLE_TABLE HandleTable,
    __inout PPH_HANDLE_TABLE_ENTRY HandleTableEntry
    );

PHLIBAPI
VOID
NTAPI
PhUnlockHandleTableEntry(
    __inout PPH_HANDLE_TABLE HandleTable,
    __inout PPH_HANDLE_TABLE_ENTRY HandleTableEntry
    );

PHLIBAPI
HANDLE
NTAPI
PhCreateHandle(
    __inout PPH_HANDLE_TABLE HandleTable,
    __in PPH_HANDLE_TABLE_ENTRY HandleTableEntry
    );

PHLIBAPI
BOOLEAN
NTAPI
PhDestroyHandle(
    __inout PPH_HANDLE_TABLE HandleTable,
    __in HANDLE Handle,
    __in_opt __assumeLocked PPH_HANDLE_TABLE_ENTRY HandleTableEntry
    );

PHLIBAPI
PPH_HANDLE_TABLE_ENTRY
NTAPI
PhLookupHandleTableEntry(
    __in PPH_HANDLE_TABLE HandleTable,
    __in HANDLE Handle
    );

typedef BOOLEAN (NTAPI *PPH_ENUM_HANDLE_TABLE_CALLBACK)(
    __in PPH_HANDLE_TABLE HandleTable,
    __in HANDLE Handle,
    __in PPH_HANDLE_TABLE_ENTRY HandleTableEntry,
    __in_opt PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhEnumHandleTable(
    __in PPH_HANDLE_TABLE HandleTable,
    __in PPH_ENUM_HANDLE_TABLE_CALLBACK Callback,
    __in_opt PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhSweepHandleTable(
    __in PPH_HANDLE_TABLE HandleTable,
    __in PPH_ENUM_HANDLE_TABLE_CALLBACK Callback,
    __in_opt PVOID Context
    );

typedef enum _PH_HANDLE_TABLE_INFORMATION_CLASS
{
    HandleTableBasicInformation,
    HandleTableFlagsInformation,
    MaxHandleTableInfoClass
} PH_HANDLE_TABLE_INFORMATION_CLASS;

typedef struct _PH_HANDLE_TABLE_BASIC_INFORMATION
{
    ULONG Count;
    ULONG Flags;
    ULONG TableLevel;
} PH_HANDLE_TABLE_BASIC_INFORMATION, *PPH_HANDLE_TABLE_BASIC_INFORMATION;

typedef struct _PH_HANDLE_TABLE_FLAGS_INFORMATION
{
    ULONG Flags;
} PH_HANDLE_TABLE_FLAGS_INFORMATION, *PPH_HANDLE_TABLE_FLAGS_INFORMATION;

PHLIBAPI
NTSTATUS
NTAPI
PhQueryInformationHandleTable(
    __in PPH_HANDLE_TABLE HandleTable,
    __in PH_HANDLE_TABLE_INFORMATION_CLASS InformationClass,
    __out_bcount_opt(BufferLength) PVOID Buffer,
    __in ULONG BufferLength,
    __out_opt PULONG ReturnLength
    );

PHLIBAPI
NTSTATUS
NTAPI
PhSetInformationHandleTable(
    __inout PPH_HANDLE_TABLE HandleTable,
    __in PH_HANDLE_TABLE_INFORMATION_CLASS InformationClass,
    __in_bcount(BufferLength) PVOID Buffer,
    __in ULONG BufferLength
    );

// workqueue

#if !defined(_PH_WORKQUEUE_PRIVATE) && defined(DEBUG)
extern LIST_ENTRY PhDbgWorkQueueListHead;
extern PH_QUEUED_LOCK PhDbgWorkQueueListLock;
#endif

typedef struct _PH_WORK_QUEUE
{
#ifdef DEBUG
    LIST_ENTRY DbgListEntry;
#endif
    PH_RUNDOWN_PROTECT RundownProtect;
    BOOLEAN Terminating;

    LIST_ENTRY QueueListHead;
    PH_QUEUED_LOCK QueueLock;

    ULONG MaximumThreads;
    ULONG MinimumThreads;
    ULONG NoWorkTimeout;

    PH_QUEUED_LOCK StateLock;
    HANDLE SemaphoreHandle;
    ULONG CurrentThreads;
    ULONG BusyThreads;
} PH_WORK_QUEUE, *PPH_WORK_QUEUE;

typedef struct _PH_WORK_QUEUE_ITEM
{
    LIST_ENTRY ListEntry;
    PTHREAD_START_ROUTINE Function;
    PVOID Context;
} PH_WORK_QUEUE_ITEM, *PPH_WORK_QUEUE_ITEM;

VOID PhWorkQueueInitialization();

PHLIBAPI
VOID
NTAPI
PhInitializeWorkQueue(
    __out PPH_WORK_QUEUE WorkQueue,
    __in ULONG MinimumThreads,
    __in ULONG MaximumThreads,
    __in ULONG NoWorkTimeout
    );

PHLIBAPI
VOID
NTAPI
PhDeleteWorkQueue(
    __inout PPH_WORK_QUEUE WorkQueue
    );

PHLIBAPI
VOID
NTAPI
PhQueueItemWorkQueue(
    __inout PPH_WORK_QUEUE WorkQueue,
    __in PTHREAD_START_ROUTINE Function,
    __in_opt PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhQueueItemGlobalWorkQueue(
    __in PTHREAD_START_ROUTINE Function,
    __in_opt PVOID Context
    );

#endif