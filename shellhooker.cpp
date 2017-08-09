// shellhooker.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "shellhooker.h"

static HWINEVENTHOOK hHook = nullptr;
static WINEVENTPROC __ShellProc = nullptr;

VOID CALLBACK _ShellProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime);

// これは、エクスポートされた変数です。
SHELLHOOKER_API HMODULE hModule = nullptr;

// これは、エクスポートされた関数です。
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

// これは、エクスポートされた関数です。
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
