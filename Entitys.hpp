#pragma once
namespace VALROM {
	typedef struct {
		uintptr_t actor_ptr;
		uintptr_t damage_handler_ptr;
		uintptr_t player_state_ptr;
		uintptr_t root_component_ptr;
		uintptr_t mesh_ptr;
		uintptr_t bone_array_ptr;
		int bone_count;
		bool is_visible;
	} Enemy;

	struct FText
	{
		char _padding_[0x28];
		PWCHAR Name;
		DWORD Length;
	};

#pragma pack(push, 1)
	struct Target
	{
		Enemy entity;
		Vector3 headPos;
		float fovDist;

		Target(Enemy e, Vector3 hp, float fd) : entity(e), headPos(hp), fovDist(fd) {}
	};
#pragma pack(pop)

	inline uintptr_t g_local_player_controller;
	inline uintptr_t g_local_player_pawn;
	inline uintptr_t g_local_damage_handler;
	inline uintptr_t g_camera_manager;
	inline int g_local_team_id;

	// Window / Process values
	inline HWND valorant_window{};
	inline GLFWwindow* g_window{};
	inline int g_pid{};
	inline uintptr_t g_base_address{};

	// Enemy list
	inline std::vector<Enemy> enemy_collection{};
	__forceinline __int64 decrypt_uworld(const uint32_t key, const uintptr_t* state)
	{

		unsigned __int64 v19; // r11
		unsigned __int64 v20; // r8
		unsigned __int64 v21; // r9
		unsigned int v22; // er10
		unsigned __int64 v23; // rcx
		unsigned __int64 v24; // rdx
		unsigned __int64 v25; // rcx
		int v26; // ebx
		unsigned int v27; // ecx
		__int64 v28; // rax
		unsigned __int64 v29; // r8
		unsigned __int64 v30; // r8
		unsigned __int64 v31; // rcx
		unsigned __int64 v32; // rdx
		unsigned __int64 v33; // rcx

		v19 = 2685821657736338717i64
			* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))
			% 7;
		v20 = state[v19];
		v21 = (2685821657736338717i64
			* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))) >> 32;
		v22 = (unsigned int)v19 % 7;
		if (!((unsigned int)v19 % 7))
		{
			v23 = (2 * (v20 - (unsigned int)(v21 - 1))) ^ ((2 * (v20 - (unsigned int)(v21 - 1))) ^ ((v20
				- (unsigned int)(v21 - 1)) >> 1)) & 0x5555555555555555i64;
			v24 = (4 * v23) ^ ((4 * v23) ^ (v23 >> 2)) & 0x3333333333333333i64;
			v25 = (16 * v24) ^ ((16 * v24) ^ (v24 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
			v20 = __ROL8__((v25 << 8) ^ ((v25 << 8) ^ (v25 >> 8)) & 0xFF00FF00FF00FFi64, 32);
		LABEL_26:
			v26 = 2 * v19;
			goto LABEL_27;
		}
		if (v22 != 1)
			goto LABEL_26;
		v26 = 2 * v19;
		v20 = __ROL8__(v20 - (unsigned int)(2 * v19 + v21), (unsigned __int8)(((int)v21 + (int)v19) % 0x3Fu) + 1);
	LABEL_27:
		v27 = v26 + v21;
		if (v22 == 2)
			v20 = ~(v20 - v27);
		switch (v22)
		{
		case 3u:
			v28 = 2 * ((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64);
			v20 = v28 ^ (v28 ^ (((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64) >> 1)) & 0x5555555555555555i64;
			break;
		case 4u:
			v29 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
			v20 = (2 * v29) ^ ((2 * v29) ^ (v29 >> 1)) & 0x5555555555555555i64;
			break;
		case 5u:
			v30 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
			v31 = (2 * v30) ^ ((2 * v30) ^ (v30 >> 1)) & 0x5555555555555555i64;
			v32 = (4 * v31) ^ ((4 * v31) ^ (v31 >> 2)) & 0x3333333333333333i64;
			v33 = (16 * v32) ^ ((16 * v32) ^ (v32 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
			v20 = __ROL8__((v33 << 8) ^ ((v33 << 8) ^ (v33 >> 8)) & 0xFF00FF00FF00FFi64, 32);
			break;
		case 6u:
			v20 = ~v20 - (unsigned int)(v21 + v19);
			break;
		}
		return v20 ^ (unsigned int)key;
	}
	inline D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}
#define M_PI 3.1415926535
	inline D3DMATRIX toMatrix(Vector3 Rotation, Vector3 origin = Vector3(0, 0, 0));
	inline D3DMATRIX toMatrix(Vector3 Rotation, Vector3 origin)
	{
		float Pitch = (Rotation.x * float(M_PI) / 180.f);
		float Yaw = (Rotation.y * float(M_PI) / 180.f);
		float Roll = (Rotation.z * float(M_PI) / 180.f);

		float SP = sinf(Pitch);
		float CP = cosf(Pitch);
		float SY = sinf(Yaw);
		float CY = cosf(Yaw);
		float SR = sinf(Roll);
		float CR = cosf(Roll);

		D3DMATRIX Matrix;
		Matrix._11 = CP * CY;
		Matrix._12 = CP * SY;
		Matrix._13 = SP;
		Matrix._14 = 0.f;

		Matrix._21 = SR * SP * CY - CR * SY;
		Matrix._22 = SR * SP * SY + CR * CY;
		Matrix._23 = -SR * CP;
		Matrix._24 = 0.f;

		Matrix._31 = -(CR * SP * CY + SR * SY);
		Matrix._32 = CY * SR - CR * SP * SY;
		Matrix._33 = CR * CP;
		Matrix._34 = 0.f;

		Matrix._41 = origin.x;
		Matrix._42 = origin.y;
		Matrix._43 = origin.z;
		Matrix._44 = 1.f;

		return Matrix;
	}

	inline Vector2 worldToScreen(Vector3 world_location, Vector3 position, Vector3 rotation, float fov)
	{
		Vector2 screen_location = Vector2(0, 0);

		D3DMATRIX tempMatrix = toMatrix(rotation);

		Vector3 vAxisX, vAxisY, vAxisZ;

		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 vDelta = world_location - position;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 0.001f)
			vTransformed.z = 0.001f;

		float FovAngle = fov;
		float ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2.0f;
		float ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2.0f;

		screen_location.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		screen_location.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

		return screen_location;
	}
}