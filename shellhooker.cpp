// shellhooker.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "shellhooker.h"

namespace ShellHooker
{
    static HWINEVENTHOOK hHook = nullptr;
    static WINEVENTPROC Proc = nullptr;

    // ����́A�G�N�X�|�[�g���ꂽ�ϐ��ł��B
    SHELLHOOKER_API HMODULE hModule = nullptr;

    VOID CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime);
}

// ����́A�G�N�X�|�[�g���ꂽ�֐��ł��B
SHELLHOOKER_API BOOL CALLBACK ShellHooker::ReleaseHook(HWND hwnd)
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

// ����́A�G�N�X�|�[�g���ꂽ�֐��ł��B
SHELLHOOKER_API BOOL CALLBACK ShellHooker::SetHook(DWORD eventMin, DWORD eventMax, WINEVENTPROC hookProc)
{
    if (hHook)
    {
        return FALSE;
    }

    Proc = hookProc;
    hHook = SetWinEventHook(eventMin, eventMax, ShellHooker::hModule, WinEventProc, 0, 0, (WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS));

    if (!hHook)
    {
        return FALSE;
    }

    return TRUE;
}

VOID CALLBACK ShellHooker::WinEventProc(
    HWINEVENTHOOK hWinEventHook,
    DWORD         event,
    HWND          hwnd,
    LONG          idObject,
    LONG          idChild,
    DWORD         idEventThread,
    DWORD         dwmsEventTime)
{
    Proc(hWinEventHook, event, hwnd, idObject, idChild, idEventThread, dwmsEventTime);
}
