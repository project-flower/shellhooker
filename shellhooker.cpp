// shellhooker.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "shellhooker.h"

static HWINEVENTHOOK hHook;
static WINEVENTPROC __ShellProc;

VOID CALLBACK _ShellProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime);

// ����́A�G�N�X�|�[�g���ꂽ�ϐ��̗�ł��B
SHELLHOOKER_API int nshellhooker=0;
SHELLHOOKER_API HMODULE hModule = nullptr;

// ����́A�G�N�X�|�[�g���ꂽ�֐��̗�ł��B
SHELLHOOKER_API int fnshellhooker(void)
{
    return 42;
}

// ����́A�G�N�X�|�[�g���ꂽ�N���X�̃R���X�g���N�^�[�ł��B
// �N���X��`�Ɋւ��Ă� shellhooker.h ���Q�Ƃ��Ă��������B
Cshellhooker::Cshellhooker()
{
    return;
}

SHELLHOOKER_API BOOL CALLBACK ReleaseHook(HWND hwnd)
{
    if (hHook)
    {
        BOOL bResult = UnhookWinEvent(hHook);

        if (bResult)
        {
            hHook = nullptr;
        }

        return bResult;
    }

    return TRUE;
}

SHELLHOOKER_API BOOL CALLBACK SetHook(DWORD eventMin, DWORD eventMax, WINEVENTPROC hookProc)
{
    if (hHook)
    {
        return FALSE;
    }

    __ShellProc = hookProc;
    hHook = SetWinEventHook(eventMin, eventMax, hModule, _ShellProc, 0, 0, (WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS));

    if (!hHook)
    {
        return FALSE;
    }

    return TRUE;
}

VOID CALLBACK _ShellProc(
    HWINEVENTHOOK hWinEventHook,
    DWORD         event,
    HWND          hwnd,
    LONG          idObject,
    LONG          idChild,
    DWORD         idEventThread,
    DWORD         dwmsEventTime)
{
    __ShellProc(hWinEventHook, event, hwnd, idObject, idChild, idEventThread, dwmsEventTime);
}