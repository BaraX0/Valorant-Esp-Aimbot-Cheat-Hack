#pragma once
namespace VALROM {
	inline static void glfwErrorCallback(int error, const char* description)
	{
		fprintf(stderr, skCrypt("Glfw Error %d: %s\n"), error, description);
	}
	inline void setupWindow() {
		glfwSetErrorCallback(glfwErrorCallback);
		if (!glfwInit()) {
			std::cout << skCrypt("glfwInit didnt work.\n");
			return;
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (!monitor) {
			fprintf(stderr, skCrypt("Failed to get primary monitor!\n"));
			return;
		}

		g_Config->g_width = glfwGetVideoMode(monitor)->width;
		g_Config->g_height = glfwGetVideoMode(monitor)->height;

		glfwWindowHint(GLFW_FLOATING, true);
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_MAXIMIZED, true);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

		g_window = glfwCreateWindow(g_Config->g_width, g_Config->g_height, skCrypt("Glfw Overlay"), NULL, NULL);
		if (g_window == NULL) {
			std::cout << skCrypt("Could not create window.\n");
			return;
		}

		glfwSetWindowAttrib(g_window, GLFW_DECORATED, false);
		glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, true);
		glfwSetWindowMonitor(g_window, NULL, 0, 0, g_Config->g_width, g_Config->g_height + 1, 0);

		glfwMakeContextCurrent(g_window);
		glfwSwapInterval(1); // Enable vsync

		if (glewInit() != GLEW_OK)
		{
			fprintf(stderr, skCrypt("Failed to initialize OpenGL loader!\n"));
			return;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(g_window, true);
		ImGui_ImplOpenGL3_Init(skCrypt("#version 130"));

		ImFont* font = io.Fonts->AddFontFromFileTTF(skCrypt("Font.ttf"), 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		IM_ASSERT(font != NULL);
	}
	inline void cleanupWindow() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(g_window);
		glfwTerminate();
	}
	inline BOOL CALLBACK retreiveValorantWindow(HWND hwnd, LPARAM lparam) {
		DWORD process_id;
		GetWindowThreadProcessId(hwnd, &process_id);
		if (process_id == g_pid) {
			valorant_window = hwnd;
		}
		return TRUE;
	}
	inline void activateValorantWindow() {
		SetForegroundWindow(valorant_window);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	inline void handleKeyPresses() {
		// Toggle overlay
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			g_Config->g_overlay_visible = !g_Config->g_overlay_visible;
			glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, !g_Config->g_overlay_visible);
			if (g_Config->g_overlay_visible) {
				HWND overlay_window = glfwGetWin32Window(g_window);
				SetForegroundWindow(overlay_window);
			}
			else {
				activateValorantWindow();
			}
		}
	}
}