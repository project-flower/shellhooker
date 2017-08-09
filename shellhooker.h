// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された SHELLHOOKER_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// SHELLHOOKER_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef SHELLHOOKER_EXPORTS
#define SHELLHOOKER_API __declspec(dllexport)
#else
#define SHELLHOOKER_API __declspec(dllimport)
#endif

extern SHELLHOOKER_API HINSTANCE hModule;

SHELLHOOKER_API BOOL CALLBACK ReleaseHook(HWND hwnd);
SHELLHOOKER_API BOOL CALLBACK SetHook(DWORD eventMin, DWORD eventMax, WINEVENTPROC hookProc);
