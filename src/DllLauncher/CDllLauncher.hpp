#pragma once

#include <mutex>
#include <string>
#include <Windows.h>

class CDllLauncher final {
public:
	auto OnDllMain( const void* lpReserved, HINSTANCE hInstace ) -> void;
	auto OnDestroy() -> void;

	[[nodiscard]] auto GetDllImage() const -> HINSTANCE {
		return m_hDllImage;
	}

	[[nodiscard]] auto GetSizeOfImage() const -> DWORD {
		return m_SizeofImage;
	}

	friend auto GetGMODDir()->std::string;
	friend auto GetDllDir()->std::string&;

private:
	static auto WINAPI StartCheatThread( LPVOID lpThreadParameter )->DWORD;

	HINSTANCE m_hDllImage = nullptr;
	DWORD m_SizeofImage = 0;

	std::string m_DllDir;
	std::string m_GMODDir;

	std::once_flag m_bDestroyed;
};

auto GetDllDir() -> std::string&;
auto GetGMODDir() -> std::string;
auto GetDllLauncher() -> CDllLauncher*;
