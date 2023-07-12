// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <processthreadsapi.h>
#include<vector>
#include <cstddef>
#include <stdlib.h> // atof
#include <string>


//void Ammo() {
//    char* dllBase = (char*)reinterpret_cast<std::byte*>(GetModuleHandleW(nullptr)) + 0x2EFB0C;
//    std::cout << "halo.exe + 0x0026CB3C: " << (int*)dllBase << std::hex << std::endl;
//    std::cout << "Points to: " << *(int*)dllBase << std::hex << std::endl;
//
//}



void HealthMod() {

    int userInput = 0;
    float playerHealth = 0.1;
    float fltToRead = 0.1;

    char* dllBase = (char*)reinterpret_cast<std::byte*>(GetModuleHandleW(nullptr)) + 0x0026CB3C;

    std::cout << "halo.exe + 0x0026CB3C: " << (int*)dllBase << std::hex << std::endl;
    std::cout << "Points to: " << *(int*)dllBase << std::hex << std::endl;

    int test = 0x0C;
    int offSet = test + *(int*)dllBase;

    std::cout << "Previous Value + 0x0C: " << offSet << std::hex << std::endl;
    std::cout << "Points To: " << *(int*)offSet << std::hex << std::endl;

    int test1 = 0x24C;
    int test2 = 0x0C;
    int test3 = 0x238;
    int test4 = 0x0C;
    int test5 = 0x534;
    int test6 = 0x624;

    int offSet1 = test1 + *(int*)offSet;
    int offSet2 = test2 + *(int*)offSet1;
    int offSet3 = test3 + *(int*)offSet2;
    int offSet4 = test4 + *(int*)offSet3;
    int offSet5 = test5 + *(int*)offSet4;
    int offSet6 = test6 + *(int*)offSet5;

    std::vector<int> v{ offSet1, offSet2, offSet3, offSet4, offSet5, offSet6 };

    for (int i : v) {
        std::cout << "Address: " << i << std::hex << std::endl;
        std::cout << "Value: " << *(int*)i << std::endl;
    }

    std::cout << "Final Address: " << offSet6 << std::hex << std::endl;
    std::cout << "Value: " << *(int*)offSet6 << std::endl;
    std::cout << "Value in readable format: " << *(float*)offSet6 << std::endl;

    //std::vector<unsigned int> offset{0x0C, 0x24C, 0x0C, 0x238, 0x0C, 0x534, 0x624};

    std::string str;
    std::cout << "Change Health: " << std::endl;
    std::cin >> str;

    int changeVal = std::stoi(str);
    float newVal = (float)(changeVal) / (float)100;

    *(float*)offSet6 = newVal;

    std::cout << "Value changed: " << *(float*)offSet6 << std::endl;
}


void StartMenu() {

    
    AllocConsole();
    FILE* fRead;
    freopen_s(&fRead, "CONIN$", "r", stdin);
    freopen_s(&fRead, "CONOUT$", "w", stdout);
    freopen_s(&fRead, "CONOUT$", "w", stderr);
    std::cout << "Press 0 to Exit | Press 1 for Health Mod | Press 2 for Ammo Mod" << std::endl;

    while (1) {
        Sleep(100);
        if (GetAsyncKeyState(VK_NUMPAD0))
            break;
        if (GetAsyncKeyState(VK_NUMPAD1)) {
            std::cout << "Starting Health Function" << std::endl;
            HealthMod();
        }
        if (GetAsyncKeyState(VK_NUMPAD2)) {
            std::cout << "Starting Ammo Function" << std::endl;
            //Ammo();
        }

    }
    fclose(fRead);
    FreeConsole();
}

void first() {
    std::thread worker(StartMenu);
    worker.detach();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
          first();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}