#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#pragma warning(disable : 4996)
/* Windows SDK */
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <vector>
#include <tchar.h>
#include <intrin.h>
#include <thread>
#include <algorithm>
/* Overlay */
#include "GL/glew.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
/* String Encrypt */
#include "xor.hpp"
/* Kernel (RPM & WPM) */
#include "Kernel/Memory.h"
/* Misc */
#include "defs.hpp"
#include "offsets.hpp"
#include "vector3.h"
/* Config */
#include "Config.hpp"
/* Entitys */
#include "Entitys.hpp"
namespace VALROM {
	template<typename T>
	inline BOOL Read(DWORD_PTR Address, T* pBuffer, DWORD Size)
	{
		if (!IsWindow(valorant_window))
			exit(-1);

		BOOL bRead = FALSE;
		DWORD_PTR Rsh_x24 = (Address >> 0x24);
		if (Rsh_x24 == 0x8 || Rsh_x24 == 0x10)
			bRead = mem->ReadGuardedRegion(DWORD_PTR(Address & 0xFFFFFF), (PVOID)pBuffer, sizeof(T));
		else
			bRead = mem->Read_Buf(Address, (PVOID)pBuffer, sizeof(T));
		return bRead;
	}
	template <typename T>
	inline T Read(DWORD_PTR Address)
	{
		if (!IsWindow(valorant_window))
			exit(-1);

		T Buffer{};
		Read(Address, &Buffer, sizeof(T));
		return Buffer;
	}
}
/* Utils */
#include "Util.hpp"
/* SDK */
#include "DecryptUWorld.hpp"
#include "Valorant.hpp"
/* Overlay */
#include "Setup.hpp"