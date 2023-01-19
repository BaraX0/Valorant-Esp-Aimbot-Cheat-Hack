#pragma once
namespace VALROM {
	inline std::wstring s2ws(const std::string& str) {
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}
	inline bool AimSortCrossHair(const Target& pf1, const Target& pf2)
	{
		return pf1.fovDist <= pf2.fovDist;
	}
}