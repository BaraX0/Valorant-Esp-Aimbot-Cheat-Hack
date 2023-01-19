#pragma once
#include <string>
#include <iostream>
#include <random>
#include <urlmon.h>
#include <iostream>
#pragma comment(lib, "urlmon.lib")
#include <stdio.h>
#include <string>
#include <windows.h>
#include <Windows.h>
#include <tchar.h>
#include <Wininet.h>
#include <filesystem>
#pragma comment(lib, "wininet.lib")


int Lgbt(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)
		return -1;

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);

	return rv;
}

int main() {

	using namespace VALROM;
	while (!mem->Init(skCrypt("VALORANT-Win64-Shipping.exe").decrypt()))
		Sleep(1500);
	g_pid = mem->GetPIDByProcessName(skCrypt("VALORANT-Win64-Shipping.exe").decrypt());
	if (!g_pid) {
		std::cout << skCrypt("Could not find val process id.\n");
		system(skCrypt("pause"));
		return 1;
	}
	EnumWindows(retreiveValorantWindow, NULL);
	if (!valorant_window) {
		std::cout << skCrypt("Could not find val window.\n");
		system(skCrypt("pause"));
		return 1;
	}
	g_base_address = mem->ModuleBase;
	if (!g_base_address) {
		std::cout << skCrypt("Could not get base address.\n");
		system(skCrypt("pause"));
		return 1;
	}
	// Create the opengl overlay window and setup imgui
	setupWindow();
	if (!g_window) {
		std::cout << skCrypt("Could not setup window.\n");
		system(skCrypt("pause"));
		return 1;
	}
	_beginthread((_beginthread_proc_type)retreiveData, 0, 0);
	_beginthread((_beginthread_proc_type)Aimbot, 0, 0);
	printf("Success!\n");
	clock_t last_update = 0;
	// Main loop
	while (!glfwWindowShouldClose(g_window))
	{
		handleKeyPresses();
		runRenderTick();
		if (last_update + 1000 < clock()) {
			mem->SetGuardedRegion();
			last_update = clock();
		}
	}

	// Cleanup
	cleanupWindow();
}