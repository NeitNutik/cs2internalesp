#include "visuals.h"
#include "../vector/math.h"
#include <cstdint>

void V::PlayerESP()
{
	uintptr_t client = (uintptr_t)GetModuleHandle("client.dll");

	float(*ViewMatrix)[4][4] = (float(*)[4][4])(client + O::dwViewMatrix);

	auto localpawn = *(uintptr_t*)(client + O::dwLocalPlayerPawn);

	if (!localpawn)
		return;

	auto localTeam = *(int*)(localpawn + O::m_iTeamNum);

	auto entitylist = *(uintptr_t*)(client + O::dwEntityList);

	if (!entitylist)
		return;
	
	for (int i = 1; i < 64; i++)
	{
		uintptr_t list_entry1 = *(uintptr_t*)(entitylist + (8 * (i & 0x7FFF) >> 9) + 16);
		if (!list_entry1)
			continue;
		uintptr_t playerController = *(uintptr_t*)(list_entry1 + 120 * (i & 0x1FF)); 
		if (!playerController)
			continue;
		uint32_t playerPawn = *(uint32_t*)(playerController + O::m_hPlayerPawn);
		if (!playerPawn)
			continue;
		uintptr_t list_entry2 = *(uintptr_t*)(entitylist + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
		if (!list_entry2)
			continue;
		uintptr_t pCSPlayerPawnPtr = *(uintptr_t*)(list_entry2 + 120 * (playerPawn & 0x1FF));
		if (!pCSPlayerPawnPtr)
			continue;

		int health = *(int*)(pCSPlayerPawnPtr + O::m_iHealth);

		if (!health || health > 100)
			continue;

		int team = *(int*)(pCSPlayerPawnPtr + O::m_iTeamNum);

		if (team == localTeam)
			continue;

		Vec3 feetpos = *(Vec3*)(pCSPlayerPawnPtr + O::m_vOldOrigin);
		Vec3 headpos = { feetpos.x + 0.0f, feetpos.y + 0.0f, feetpos.z + 70.0f };

		Vec2 feet, head;

		if (feetpos.WorldToScreen(feet, ViewMatrix) && headpos.WorldToScreen(head, ViewMatrix))
		{
			float height = (feet.y - head.y) / 1.5f;
			float width = height / 1.5f;

			float x = feet.x - width / 2;
			ImGui::GetBackgroundDrawList()->AddRect({ x, head.y }, { x + width, head.y + height }, ImColor(255, 255, 255));
		}

	}
}
