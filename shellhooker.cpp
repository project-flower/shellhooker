// shellhooker.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "shellhooker.h"

namespace ShellHooker
{
    static HWINEVENTHOOK hHook = nullptr;
    static WINEVENTPROC __ShellProc = nullptr;

    // これは、エクスポートされた変数です。
    SHELLHOOKER_API HMODULE hModule = nullptr;

    VOID CALLBACK _ShellProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime);
}

// これは、エクスポートされた関数です。
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

// これは、エクスポートされた関数です。
SHELLHOOKER_API BOOL CALLBACK ShellHooker::SetHook(DWORD eventMin, DWORD eventMax, WINEVENTPROC hookProc)
{
    if (hHook)
    {
        return FALSE;
    }

    __ShellProc = hookProc;
    hHook = SetWinEventHook(eventMin, eventMax, ShellHooker::hModule, _ShellProc, 0, 0, (WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS));

    if (!hHook)
    {
        return FALSE;
    }

    return TRUE;
}

VOID CALLBACK ShellHooker::_ShellProc(
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
