#include "includes.h"

void CreateConsole()
{
    if (!AllocConsole()) {
        return;
    }

    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    HANDLE hConOut = CreateFile(("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hConIn = CreateFile(("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
    SetStdHandle(STD_ERROR_HANDLE, hConOut);
    SetStdHandle(STD_INPUT_HANDLE, hConIn);
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();
}

void entry()
{
   // CreateConsole();

    auto world = SDK::UWorld::GetWorld();
    printf("World -> %llx\n", (uintptr_t)world);

    auto ViewportClient = world->OwningGameInstance->LocalPlayers[0]->ViewportClient;
    auto VTable = *reinterpret_cast<void***>(ViewportClient);

    LoadObjects();
    printf("Loaded Objects\n");

    printf("Initialising hooks\n");

    bool WindowFocus = false;
    while (WindowFocus == false)
    {
        DWORD ForegroundWindowProcessID;
        GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
        if (GetCurrentProcessId() == ForegroundWindowProcessID) 
        {
            Process::ID = GetCurrentProcessId();
            Process::Handle = GetCurrentProcess();
            Process::Hwnd = GetForegroundWindow();

            RECT TempRect;
            GetWindowRect(Process::Hwnd, &TempRect);
            Process::WindowWidth = TempRect.right - TempRect.left;
            Process::WindowHeight = TempRect.bottom - TempRect.top;

            WindowFocus = true;
        }
    }

    if (!DirectX12::Init())
    {
        Log("DirectX12 init failed\n");
        return;
    }

    oExecuteCommandLists = reinterpret_cast<ExecuteCommandLists>(MethodsTable[54]);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(reinterpret_cast<PVOID*>(&oExecuteCommandLists), hkExecuteCommandLists);
    DetourTransactionCommit();

    oPresent = reinterpret_cast<Present12>(MethodsTable[140]);
    
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(reinterpret_cast<PVOID*>(&oPresent), hkPresent);
    DetourTransactionCommit();

    process_event_o = reinterpret_cast<process_event_sim>(SDK::InSDKUtils::GetImageBase() + SDK::Offsets::ProcessEvent);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(reinterpret_cast<PVOID*>(&process_event_o), ProcessEventHk);
    DetourTransactionCommit();


    printf("Initialised hooks\n");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved)
{
    if (callReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        Process::Module = hModule;
        std::thread([&]() { Sleep(30000); entry(); }).detach();
    }
    return TRUE;
}