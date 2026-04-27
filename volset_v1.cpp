#define UNICODE
#define _UNICODE

#include <windows.h>
#include <mmdeviceapi.h>
#include <shellapi.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ole32.lib")
#define WM_TRAYICON (WM_USER + 1)

HMENU hMenu;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_TRAYICON && lParam == WM_RBUTTONDOWN) {
        PostQuitMessage(0);
    }
    
if (msg == WM_COMMAND) {
    switch (LOWORD(wParam)) {

        case 1:
        system("cmd /c \"E:\\Softwares for my laptop\\Utilities\\soundvolumeview-x64\\SoundVolumeView.exe\" /ChangeVolume \"AirPods Pro2\\Device\\Earpods\\Render\" 10");
        break;

    case 2:
        system("cmd /c \"E:\\Softwares for my laptop\\Utilities\\soundvolumeview-x64\\SoundVolumeView.exe\" /ChangeVolume \"AirPods Pro2\\Device\\Earpods\\Render\" -10");
        break;

    case 3:
        PostQuitMessage(0);
        break;

    case 999:
    case 1000:
        break;
    }
}
if (msg == WM_TRAYICON && lParam == WM_RBUTTONUP) {
    POINT p;
    GetCursorPos(&p);

    SetForegroundWindow(hwnd);
    TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, p.x, p.y, 0, hwnd, NULL);
}
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
std::string GetDefaultAudioDeviceId() {
    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    LPWSTR pwszID = NULL;
    std::string deviceId = "";

    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), NULL,
        CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
        (void**)&pEnumerator);

    if (FAILED(hr)) return "";

    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    if (FAILED(hr)) {
        pEnumerator->Release();
        return "";
    }

    hr = pDevice->GetId(&pwszID);
    if (SUCCEEDED(hr)) {
        int len = WideCharToMultiByte(CP_UTF8, 0, pwszID, -1, NULL, 0, NULL, NULL);
        char* buffer = new char[len];
        WideCharToMultiByte(CP_UTF8, 0, pwszID, -1, buffer, len, NULL, NULL);
        deviceId = buffer;
        delete[] buffer;
    }

    CoTaskMemFree(pwszID);
    pDevice->Release();
    pEnumerator->Release();

    return deviceId;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    WNDCLASSW wc = {};
wc.lpfnWndProc = WindowProc;
wc.hInstance = GetModuleHandle(NULL);
wc.lpszClassName = L"TrayClass";

RegisterClassW(&wc);

HWND hwnd = CreateWindowExW(0, L"TrayClass", L"", 0, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
NOTIFYICONDATAW nid = {};
nid.cbSize = sizeof(nid);
nid.hWnd = hwnd;
nid.uID = 1;
nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
nid.uCallbackMessage = WM_TRAYICON;
nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
wcscpy_s(nid.szTip, L"Audio Watcher");

hMenu = CreatePopupMenu();
PostMessage(hwnd, WM_NULL, 0, 0);
AppendMenuW(hMenu, MF_STRING, 1, L"Volume +10%");
AppendMenuW(hMenu, MF_STRING, 2, L"Volume -10%");
AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
AppendMenuW(hMenu, MF_STRING, 3, L"Exit");
AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
AppendMenuW(hMenu, MF_STRING | MF_GRAYED, 999, L"Built by Muhammad Tahmid Ahnaf");
AppendMenuW(hMenu, MF_STRING | MF_GRAYED, 1000, L"Version 1.03");

Shell_NotifyIconW(NIM_ADD, &nid);
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    CoInitialize(NULL);

    std::string lastDevice = GetDefaultAudioDeviceId();

    MSG msg;

while (true) {

    Sleep(1000);

    std::string currentDevice = GetDefaultAudioDeviceId();

    if (!currentDevice.empty() && currentDevice != lastDevice) {
        system("cmd /c \"E:\\Softwares for my laptop\\Utilities\\soundvolumeview-x64\\setvolume.bat\"");
        lastDevice = currentDevice;
    }

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            Shell_NotifyIconW(NIM_DELETE, &nid);
            exit(0);
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
    

    CoUninitialize();
    return 0;
}