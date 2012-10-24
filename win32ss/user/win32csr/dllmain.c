/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS system libraries
 * FILE:            subsys/csrss/win32csr/dllmain.c
 * PURPOSE:         Initialization
 * PROGRAMMERS:     Dmitry Philippov (shedon@mail.ru)
 */

/* INCLUDES ******************************************************************/

#include "w32csr.h"

#define NDEBUG
#include <debug.h>


/* GLOBALS *******************************************************************/

HANDLE Win32CsrApiHeap;
HINSTANCE Win32CsrDllHandle = NULL;

PCSR_API_ROUTINE Win32CsrApiDefinitions[] =
{
    CsrGetHandle,
    CsrGetHandle,
    CsrCloseHandle,
    CsrVerifyHandle,
    CsrDuplicateHandle,
    CsrGetInputWaitHandle,
    CsrFillOutputChar,
    CsrReadInputEvent,
    CsrWriteConsoleOutputChar,
    CsrWriteConsoleOutputAttrib,
    CsrFillOutputAttrib,
    CsrSetTextAttrib,
    CsrWriteConsoleOutput,
    CsrFlushInputBuffer,
    CsrReadConsoleOutputChar,
    CsrReadConsoleOutputAttrib,
    CsrExitReactos,
    CsrHardwareStateProperty,
    CsrCreateDesktop,
    CsrShowDesktop,
    CsrHideDesktop,
    CsrSetLogonNotifyWindow,
    CsrRegisterLogonProcess,
    CsrGenerateCtrlEvent,
};


/*
static CSRSS_API_DEFINITION Win32CsrApiDefinitions[] =
{
    CSRSS_DEFINE_API(GET_INPUT_HANDLE,             CsrGetHandle),
    CSRSS_DEFINE_API(GET_OUTPUT_HANDLE,            CsrGetHandle),
    CSRSS_DEFINE_API(CLOSE_HANDLE,                 CsrCloseHandle),
    CSRSS_DEFINE_API(VERIFY_HANDLE,                CsrVerifyHandle),
    CSRSS_DEFINE_API(DUPLICATE_HANDLE,             CsrDuplicateHandle),
    CSRSS_DEFINE_API(GET_INPUT_WAIT_HANDLE,        CsrGetInputWaitHandle),
    CSRSS_DEFINE_API(WRITE_CONSOLE,                CsrWriteConsole),
    CSRSS_DEFINE_API(READ_CONSOLE,                 CsrReadConsole),
    CSRSS_DEFINE_API(ALLOC_CONSOLE,                CsrAllocConsole),
    CSRSS_DEFINE_API(FREE_CONSOLE,                 CsrFreeConsole),
    CSRSS_DEFINE_API(SCREEN_BUFFER_INFO,           CsrGetScreenBufferInfo),
    CSRSS_DEFINE_API(SET_CURSOR,                   CsrSetCursor),
    CSRSS_DEFINE_API(FILL_OUTPUT,                  CsrFillOutputChar),
    CSRSS_DEFINE_API(READ_INPUT,                   CsrReadInputEvent),
    CSRSS_DEFINE_API(WRITE_CONSOLE_OUTPUT_CHAR,    CsrWriteConsoleOutputChar),
    CSRSS_DEFINE_API(WRITE_CONSOLE_OUTPUT_ATTRIB,  CsrWriteConsoleOutputAttrib),
    CSRSS_DEFINE_API(FILL_OUTPUT_ATTRIB,           CsrFillOutputAttrib),
    CSRSS_DEFINE_API(GET_CURSOR_INFO,              CsrGetCursorInfo),
    CSRSS_DEFINE_API(SET_CURSOR_INFO,              CsrSetCursorInfo),
    CSRSS_DEFINE_API(SET_ATTRIB,                   CsrSetTextAttrib),
    CSRSS_DEFINE_API(GET_CONSOLE_MODE,             CsrGetConsoleMode),
    CSRSS_DEFINE_API(SET_CONSOLE_MODE,             CsrSetConsoleMode),
    CSRSS_DEFINE_API(CREATE_SCREEN_BUFFER,         CsrCreateScreenBuffer),
    CSRSS_DEFINE_API(SET_SCREEN_BUFFER,            CsrSetScreenBuffer),
    CSRSS_DEFINE_API(SET_TITLE,                    CsrSetTitle),
    CSRSS_DEFINE_API(GET_TITLE,                    CsrGetTitle),
    CSRSS_DEFINE_API(WRITE_CONSOLE_OUTPUT,         CsrWriteConsoleOutput),
    CSRSS_DEFINE_API(FLUSH_INPUT_BUFFER,           CsrFlushInputBuffer),
    CSRSS_DEFINE_API(SCROLL_CONSOLE_SCREEN_BUFFER, CsrScrollConsoleScreenBuffer),
    CSRSS_DEFINE_API(READ_CONSOLE_OUTPUT_CHAR,     CsrReadConsoleOutputChar),
    CSRSS_DEFINE_API(READ_CONSOLE_OUTPUT_ATTRIB,   CsrReadConsoleOutputAttrib),
    CSRSS_DEFINE_API(GET_NUM_INPUT_EVENTS,         CsrGetNumberOfConsoleInputEvents),
    CSRSS_DEFINE_API(EXIT_REACTOS,                 CsrExitReactos),
    CSRSS_DEFINE_API(PEEK_CONSOLE_INPUT,           CsrPeekConsoleInput),
    CSRSS_DEFINE_API(READ_CONSOLE_OUTPUT,          CsrReadConsoleOutput),
    CSRSS_DEFINE_API(WRITE_CONSOLE_INPUT,          CsrWriteConsoleInput),
    CSRSS_DEFINE_API(SETGET_CONSOLE_HW_STATE,      CsrHardwareStateProperty),
    CSRSS_DEFINE_API(GET_CONSOLE_WINDOW,           CsrGetConsoleWindow),
    CSRSS_DEFINE_API(CREATE_DESKTOP,               CsrCreateDesktop),
    CSRSS_DEFINE_API(SHOW_DESKTOP,                 CsrShowDesktop),
    CSRSS_DEFINE_API(HIDE_DESKTOP,                 CsrHideDesktop),
    CSRSS_DEFINE_API(SET_CONSOLE_ICON,             CsrSetConsoleIcon),
    CSRSS_DEFINE_API(SET_LOGON_NOTIFY_WINDOW,      CsrSetLogonNotifyWindow),
    CSRSS_DEFINE_API(REGISTER_LOGON_PROCESS,       CsrRegisterLogonProcess),
    CSRSS_DEFINE_API(GET_CONSOLE_CP,               CsrGetConsoleCodePage),
    CSRSS_DEFINE_API(SET_CONSOLE_CP,               CsrSetConsoleCodePage),
    CSRSS_DEFINE_API(GET_CONSOLE_OUTPUT_CP,        CsrGetConsoleOutputCodePage),
    CSRSS_DEFINE_API(SET_CONSOLE_OUTPUT_CP,        CsrSetConsoleOutputCodePage),
    CSRSS_DEFINE_API(GET_PROCESS_LIST,             CsrGetProcessList),
    CSRSS_DEFINE_API(ADD_CONSOLE_ALIAS,      CsrAddConsoleAlias),
    CSRSS_DEFINE_API(GET_CONSOLE_ALIAS,      CsrGetConsoleAlias),
    CSRSS_DEFINE_API(GET_ALL_CONSOLE_ALIASES,         CsrGetAllConsoleAliases),
    CSRSS_DEFINE_API(GET_ALL_CONSOLE_ALIASES_LENGTH,  CsrGetAllConsoleAliasesLength),
    CSRSS_DEFINE_API(GET_CONSOLE_ALIASES_EXES,        CsrGetConsoleAliasesExes),
    CSRSS_DEFINE_API(GET_CONSOLE_ALIASES_EXES_LENGTH, CsrGetConsoleAliasesExesLength),
    CSRSS_DEFINE_API(GENERATE_CTRL_EVENT,          CsrGenerateCtrlEvent),
    CSRSS_DEFINE_API(SET_SCREEN_BUFFER_SIZE,       CsrSetScreenBufferSize),
    CSRSS_DEFINE_API(GET_CONSOLE_SELECTION_INFO,   CsrGetConsoleSelectionInfo),
    CSRSS_DEFINE_API(GET_COMMAND_HISTORY_LENGTH,   CsrGetCommandHistoryLength),
    CSRSS_DEFINE_API(GET_COMMAND_HISTORY,          CsrGetCommandHistory),
    CSRSS_DEFINE_API(EXPUNGE_COMMAND_HISTORY,      CsrExpungeCommandHistory),
    CSRSS_DEFINE_API(SET_HISTORY_NUMBER_COMMANDS,  CsrSetHistoryNumberCommands),
    CSRSS_DEFINE_API(GET_HISTORY_INFO,             CsrGetHistoryInfo),
    CSRSS_DEFINE_API(SET_HISTORY_INFO,             CsrSetHistoryInfo),
    { 0, 0, NULL }
};
*/

static HHOOK hhk = NULL;

/* FUNCTIONS *****************************************************************/

LRESULT
CALLBACK
KeyboardHookProc(
    int nCode,
    WPARAM wParam,
    LPARAM lParam)
{
   return CallNextHookEx(hhk, nCode, wParam, lParam);
}

ULONG
InitializeVideoAddressSpace(VOID)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING PhysMemName = RTL_CONSTANT_STRING(L"\\Device\\PhysicalMemory");
    NTSTATUS Status;
    HANDLE PhysMemHandle;
    PVOID BaseAddress;
    LARGE_INTEGER Offset;
    SIZE_T ViewSize;
    CHAR IVTAndBda[1024+256];
    
    /* Free the 1MB pre-reserved region. In reality, ReactOS should simply support us mapping the view into the reserved area, but it doesn't. */
    BaseAddress = 0;
    ViewSize = 1024 * 1024;
    Status = ZwFreeVirtualMemory(NtCurrentProcess(), 
                                 &BaseAddress,
                                 &ViewSize,
                                 MEM_RELEASE);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Couldn't unmap reserved memory (%x)\n", Status);
        return 0;
    }
    
    /* Open the physical memory section */
    InitializeObjectAttributes(&ObjectAttributes,
                               &PhysMemName,
                               0,
                               NULL,
                               NULL);
    Status = ZwOpenSection(&PhysMemHandle,
                           SECTION_ALL_ACCESS,
                           &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Couldn't open \\Device\\PhysicalMemory\n");
        return 0;
    }

    /* Map the BIOS and device registers into the address space */
    Offset.QuadPart = 0xa0000;
    ViewSize = 0x100000 - 0xa0000;
    BaseAddress = (PVOID)0xa0000;
    Status = ZwMapViewOfSection(PhysMemHandle,
                                NtCurrentProcess(),
                                &BaseAddress,
                                0,
                                ViewSize,
                                &Offset,
                                &ViewSize,
                                ViewUnmap,
                                0,
                                PAGE_EXECUTE_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Couldn't map physical memory (%x)\n", Status);
        ZwClose(PhysMemHandle);
        return 0;
    }

    /* Close physical memory section handle */
    ZwClose(PhysMemHandle);

    if (BaseAddress != (PVOID)0xa0000)
    {
        DPRINT1("Couldn't map physical memory at the right address (was %x)\n",
                BaseAddress);
        return 0;
    }

    /* Allocate some low memory to use for the non-BIOS
     * parts of the v86 mode address space
     */
    BaseAddress = (PVOID)0x1;
    ViewSize = 0xa0000 - 0x1000;
    Status = ZwAllocateVirtualMemory(NtCurrentProcess(),
                                     &BaseAddress,
                                     0,
                                     &ViewSize,
                                     MEM_RESERVE | MEM_COMMIT,
                                     PAGE_EXECUTE_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to allocate virtual memory (Status %x)\n", Status);
        return 0;
    }
    if (BaseAddress != (PVOID)0x0)
    {
        DPRINT1("Failed to allocate virtual memory at right address (was %x)\n",
                BaseAddress);
        return 0;
    }

    /* Get the real mode IVT and BDA from the kernel */
    Status = NtVdmControl(VdmInitialize, IVTAndBda);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtVdmControl failed (status %x)\n", Status);
        return 0;
    }

    /* Return success */
    return 1;
}

/**********************************************************************
 * CsrpInitVideo/3
 *
 * TODO: we need a virtual device for sessions other than
 * TODO: the console one
 */
NTSTATUS
CsrpInitVideo (VOID)
{
  OBJECT_ATTRIBUTES ObjectAttributes;
  UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\??\\DISPLAY1");
  IO_STATUS_BLOCK Iosb;
  HANDLE VideoHandle = (HANDLE) 0;
  NTSTATUS Status = STATUS_SUCCESS;

  DPRINT("CSR: %s called\n", __FUNCTION__);

  InitializeVideoAddressSpace();

  InitializeObjectAttributes(&ObjectAttributes,
			     &DeviceName,
			     0,
			     NULL,
			     NULL);
  Status = NtOpenFile(&VideoHandle,
		      FILE_ALL_ACCESS,
		      &ObjectAttributes,
		      &Iosb,
		      0,
		      0);
  if (NT_SUCCESS(Status))
    {
      NtClose(VideoHandle);
    }
  return Status;
}

BOOL WINAPI
DllMain(HANDLE hDll,
        DWORD dwReason,
        LPVOID lpReserved)
{
    if (DLL_PROCESS_ATTACH == dwReason)
    {
        Win32CsrDllHandle = hDll;
//
// HACK HACK HACK ReactOS to BOOT! Initialization BUG ALERT! See bug 5655.
//
        hhk = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
// BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT!
//  BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT!
//   BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT! BUG ALERT!
    }

    return TRUE;
}

NTSTATUS FASTCALL
Win32CsrEnumProcesses(CSRSS_ENUM_PROCESS_PROC EnumProc,
                      PVOID Context)
{
    return CsrEnumProcesses(EnumProc, Context);
}

VOID
WINAPI
PrivateCsrssManualGuiCheck(LONG Check)
{
  NtUserCallOneParam(Check, ONEPARAM_ROUTINE_CSRSS_GUICHECK);
}

DWORD
WINAPI
CreateSystemThreads(PVOID pParam)
{
    NtUserCallOneParam((DWORD)pParam, ONEPARAM_ROUTINE_CREATESYSTEMTHREADS);
    DPRINT1("This thread should not terminate!\n");
    return 0;
}

CSR_SERVER_DLL_INIT(Win32CsrInitialization)
{
    HANDLE ServerThread;
    CLIENT_ID ClientId;
    NTSTATUS Status;

    Win32CsrApiHeap = RtlGetProcessHeap();
    
    CsrpInitVideo(); // Must go into winsrv.dll

    NtUserInitialize(0, NULL, NULL);

    PrivateCsrssManualGuiCheck(0);

    /* Setup the DLL Object */
    LoadedServerDll->ApiBase = USERSRV_FIRST_API_NUMBER;
    LoadedServerDll->HighestApiSupported = UserpMaxApiNumber;
    LoadedServerDll->DispatchTable = Win32CsrApiDefinitions;
    // LoadedServerDll->ValidTable = Win32CsrApiServerValidTable;
    // LoadedServerDll->NameTable = Win32CsrApiNameTable;
    // LoadedServerDll->SizeOfProcessData = 0;
    // LoadedServerDll->ConnectCallback = NULL;
    // LoadedServerDll->DisconnectCallback = NULL;
    LoadedServerDll->HardErrorCallback = Win32CsrHardError;
    LoadedServerDll->NewProcessCallback = NULL;
    LoadedServerDll->DisconnectCallback = NULL;

    /* Start Raw Input Threads */
    Status = RtlCreateUserThread(NtCurrentProcess(), NULL, TRUE, 0, 0, 0, (PTHREAD_START_ROUTINE)CreateSystemThreads, (PVOID)0, &ServerThread, &ClientId);
    if (NT_SUCCESS(Status))
    {
        NtResumeThread(ServerThread, NULL);
        NtClose(ServerThread);
    }
    else
        DPRINT1("Cannot start Raw Input Thread!\n");

    return STATUS_SUCCESS;
}

/* EOF */
