#pragma once
namespace VALROM {
	class Config {
	public:
		int g_width{};
		int g_height{};
		float g_AimSmooth = 0.f;
		float g_AimFov = 0.f;
		ImU32 g_esp_color = ImColor(31, 76, 110, 200);
		ImU32 g_color_white = ImColor(255, 255, 255, 255);
		// Cheat toggle values
		bool g_overlay_visible{ false };
		bool g_esp_enabled{ true };
		bool g_Aimbot_enable{ true };
		bool g_Silent_enable{ true };
		bool g_Health_bar{ true };
		bool g_esp_dormantcheck{ false };
		bool g_headesp{ true };
		bool g_boneesp{ true };
		bool g_boxesp{ true };
		bool g_Aimbot{ true };
		bool g_DrawFov{ true };
	};

	inline auto g_Config = std::make_unique<Config>();
}