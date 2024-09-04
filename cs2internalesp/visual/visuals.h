#pragma once
#include "math.h"
#include <cstddef>
#include <cstdint>
#include "../imgui/imgui.h"

namespace O
{
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x17D37F0;
	constexpr std::ptrdiff_t dwEntityList = 0x19684F8;
	constexpr std::ptrdiff_t dwViewMatrix = 0x19CA480;
	constexpr std::ptrdiff_t dwLocalPlayerController = 0x19B8158;

	constexpr std::ptrdiff_t m_hPlayerPawn = 0x7EC;
	
	constexpr std::ptrdiff_t m_iHealth = 0x324;
	constexpr std::ptrdiff_t m_iTeamNum = 0x3C3;
	constexpr std::ptrdiff_t m_vOldOrigin = 0x1274;
}

namespace V
{
	void PlayerESP();
}
