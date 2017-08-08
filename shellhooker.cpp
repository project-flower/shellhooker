// shellhooker.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "shellhooker.h"

static HWINEVENTHOOK hHook;
static WINEVENTPROC __ShellProc;

VOID CALLBACK _ShellProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime);

// これは、エクスポートされた変数の例です。
SHELLHOOKER_API int nshellhooker=0;
SHELLHOOKER_API HMODULE hModule = nullptr;

// これは、エクスポートされた関数の例です。
SHELLHOOKER_API int fnshellhooker(void)
{
    return 42;
}

// これは、エクスポートされたクラスのコンストラクターです。
// クラス定義に関しては shellhooker.h を参照してください。
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
