using namespace std;
using namespace offsets;
using namespace settings;


glm::mat4x4 view_matrix()
{
	if (!local::camera_instance.load())
		return {};

	return read<glm::mat4x4>(local::camera_instance.load() + 0x2e4);
}

bool world_to_screen(const glm::vec3& world, glm::vec2* screen)
{
	const auto matrix = glm::transpose(view_matrix());

	const auto pos_vec = glm::vec3{ matrix[3][0], matrix[3][1], matrix[3][2] };

	const auto z = glm::dot(pos_vec, world) + matrix[3][3];

	if (z < 0.098f)
		return false;

	const auto x = glm::dot(glm::vec3{ matrix[0][0], matrix[0][1], matrix[0][2] }, world) + matrix[0][3];
	const auto y = glm::dot(glm::vec3{ matrix[1][0], matrix[1][1], matrix[1][2] }, world) + matrix[1][3];

	static const auto screen_center_x = Width * 0.5f;
	static const auto screen_center_y = Height * 0.5f;

	if (screen)
	{
		*screen =
		{
			screen_center_x * (1.f + x / z),
			screen_center_y * (1.f - y / z)
		};
	}

	return true;
}

void safe_memcpy_wrapper(ULONG64 Dst, ULONG64 Src, ULONG Sz)
{
	if ((((ULONG64)Dst) > 0x400000) && (((ULONG64)Dst + Sz) < 0x00007FFFFFFF0000))
	{
		while (true)
		{
			//copy 8 byte
			if (Sz >= 8)
			{
				*(ULONG64*)Dst = read<ULONG64>(Src);
				Dst += 8; Src += 8; Sz -= 8;
			}

			//copy 4 byte
			else if (Sz >= 4)
			{
				*(ULONG*)Dst = read<ULONG>(Src);
				Dst += 4; Src += 4; Sz -= 4;
			}

			//copy 2 byte
			else if (Sz >= 2)
			{
				*(WORD*)Dst = read<WORD>(Src);
				Dst += 2; Src += 2; Sz -= 2;
			}

			//copy last byte
			else if (Sz)
			{
				*(BYTE*)Dst = read<BYTE>(Src);
				break;
			}

			//if(Sz == 0)
			else
				break;
		}
	}
}

#define safe_memcpy(Dst, Src, Size) safe_memcpy_wrapper(((ULONG64)Dst), ((ULONG64)Src), Size);

glm::vec3 GetPosition(ULONG64 transform)
{
	if (!transform) return glm::vec3{ 0.f, 0.f, 0.f };

	struct Matrix34 { BYTE vec0[16]; BYTE vec1[16]; BYTE vec2[16]; };
	const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

	int Index = read<int>(transform + 0x40);// *(PINT)(transform + 0x40);
	ULONG64 pTransformData = read<ULONG64>(transform + 0x38);
	ULONG64 transformData[2];
	//impl::memory->read(&transformData, (PVOID)(pTransformData + 0x18), 16);
	safe_memcpy(&transformData, (PVOID)(pTransformData + 0x18), 16);

	size_t sizeMatriciesBuf = 48 * Index + 48;
	size_t sizeIndicesBuf = 4 * Index + 4;

	PVOID pMatriciesBuf = malloc(sizeMatriciesBuf);
	PVOID pIndicesBuf = malloc(sizeIndicesBuf);

	if (pMatriciesBuf && pIndicesBuf)
	{
		// Read Matricies array into the buffer
		readto(transformData[0], pMatriciesBuf, sizeMatriciesBuf);
		// Read Indices array into the buffer
		readto(transformData[1], pIndicesBuf, sizeIndicesBuf);

		__m128 result = *(__m128*)((ULONGLONG)pMatriciesBuf + 0x30 * Index);
		int transformIndex = *(int*)((ULONGLONG)pIndicesBuf + 0x4 * Index);

		while (transformIndex >= 0)
		{
			Matrix34 matrix34 = *(Matrix34*)((ULONGLONG)pMatriciesBuf + 0x30 * transformIndex);
			__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x00));
			__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x55));
			__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x8E));
			__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xDB));
			__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xAA));
			__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x71));
			__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34.vec2), result);

			result = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
						tmp7)), *(__m128*)(&matrix34.vec0));
			try {
				transformIndex = *(int*)((ULONGLONG)pIndicesBuf + 0x4 * transformIndex);
			}
			catch (...)
			{
				// Do nothing
			}
		}

		return glm::vec3(result.m128_f32[0], result.m128_f32[1], result.m128_f32[2]);
	}
}

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};

std::uint64_t get_base_player(std::uint64_t entity)
{
	const auto unk1 = read<uintptr_t>(entity + 0x18);

	if (!unk1)
		return 0;
	return read<uintptr_t>(unk1 + 0x28);
}

bool is_local_player(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return false;

	const auto player_model = read<uintptr_t>(base_player + base_player::OffsetPlayerModel);

	if (!player_model)
		return false;

	return read<bool>(player_model + 0x251);
}

bool is_visible(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return false;

	const auto player_model = read<uintptr_t>(base_player + base_player::OffsetPlayerModel);

	if (!player_model)
		return false;

	return read<bool>(player_model + 0x240);
}

std::string get_class_name(std::uint64_t class_object)
{
	const auto object_unk = read<uintptr_t>(class_object);

	if (!object_unk)
		return {};

	return read_ascii(read<uintptr_t>(object_unk + 0x10), 11);
}

bool get_player_sleeping(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return 0;

	int flags = read<int>(base_player + 0x5B8);

	return flags & 16;
}

bool get_player_admin(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return 0;

	int flags = read<int>(base_player + 0x5B8);

	return flags & 4;
}

int get_steam_id(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return 0;

	int steam = read<int>(base_player + base_player::OffsetSteamID);

	return steam;
}

std::uint32_t get_player_health(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return 0;

	const auto player_health = read<float>(base_player + 0x1f4);

	if (player_health <= 0.8f)
		return 0;

	return std::lround(player_health);
}

std::wstring get_player_name(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return {};

	const auto player_name_ptr = read<uintptr_t>(base_player + base_player::OffsetUserDisplayName); //[FieldOffset(Offset = "0x4E8")] protected string _displayName;

	if (!player_name_ptr)
		return {};

	return read_unicode(player_name_ptr + 0x14, 32);
}

std::string get_player_name_string(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return {};

	const auto player_name_ptr = read<uintptr_t>(base_player + base_player::OffsetUserDisplayName); //[FieldOffset(Offset = "0x4E8")] protected string _displayName;

	if (!player_name_ptr)
		return {};

	wchar_t PlayerName[64] = { NULL };

	readto(player_name_ptr + 0x14, &PlayerName, sizeof(PlayerName));
	char* result = (char*)malloc(1024);
	sprintf(result, XorString(u8"%S "), PlayerName);

	return result;
}

std::uint64_t get_held_item(std::uint64_t entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return 0;

	const auto active_item_id = read<std::uint32_t>(base_player + 0x530);

	/* not holding anything */
	if (!active_item_id)
		return 0;

	/* now iterate through the player's belt */

	const auto player_inventory = read<uintptr_t>(base_player + base_player::OffsetPlayerInventory); // public global::PlayerInventory inventory;

	if (!player_inventory)
		return 0;

	const auto inventory_belt = read<uintptr_t>(player_inventory + 0x28);

	if (!inventory_belt)
		return 0;

	const auto belt_contents_list = read<uintptr_t>(inventory_belt + 0x38);

	if (!belt_contents_list)
		return 0;

	const auto belt_contents_sz = read<std::uint32_t>(belt_contents_list + 0x14);
	const auto belt_contents = read<uintptr_t>(belt_contents_list + 0x10);

	if (!belt_contents)
		return 0;

	for (auto i = 0u; i <= 6; i++)
	{
		if (belt_contents != 0)
		{
			const auto current_item = read<uintptr_t>(belt_contents + (0x20 + (i * 8)));

			if (!current_item)
				continue;

			if (active_item_id == read<std::uint32_t>(current_item + 0x28))
				return current_item;
		}
	}
}

std::wstring get_player_item_name(std::uint64_t entity)
{
	const auto held_item = get_held_item(entity);

	if (!held_item)
		return {};

	const auto item_definition = read<uintptr_t>(held_item + 0x20);

	if (!item_definition)
		return {};

	const auto display_phrase = read<uintptr_t>(item_definition + 0x20);

	if (!display_phrase)
		return {};

	auto wname = read_unicode(display_phrase + 0x14, 64);

	if (!wname.empty())
		return wname;
	else
		return L"No Item!";
}

std::wstring get_item_name(std::uint64_t item)
{
	const auto item_definition = read<uintptr_t>(item + 0x20);

	if (!item_definition)
		return {};

	const auto display_phrase = read<uintptr_t>(item_definition + 0x20);

	if (!display_phrase)
		return {};

	//const auto english_name = read<uintptr_t>(display_phrase + 0x18);

	//if (!english_name)
	//	return {};
	auto wname = read_unicode(display_phrase + 0x14, 64);

	if (!wname.empty())
		return wname;
	else
		return L"No Item!";
}

glm::vec3 get_obj_pos(std::uint64_t entity)
{
	const auto player_visual = read<uintptr_t>(entity + 0x8);

	if (!player_visual)
		return {};

	const auto visual_state = read<uintptr_t>(player_visual + 0x38);

	if (!visual_state)
		return {};

	return read<glm::vec3>(visual_state + 0x90);
}

bool is_same_team(std::uint64_t entity, std::uint64_t local_entity)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return false;

	const auto base_player_local = get_base_player(local_entity);

	if (!base_player_local)
		return false;

	const auto local_team = read<std::uint32_t>(base_player_local + 0x5a8);
	const auto enemy_team = read<std::uint32_t>(base_player + 0x5a8);

	if (local_team == 0 || enemy_team == 0)
		return false;

	return local_team == enemy_team;
}

glm::vec3 get_bone_position(std::uint64_t entity, int id)
{
	const auto base_player = get_base_player(entity);
	if (!base_player)
		return glm::vec3{ 0,0,0 };

	uintptr_t model = read<uintptr_t>(base_player + 0x118);
	uintptr_t BoneTransforms = read<uintptr_t>(model + 0x48);
	uintptr_t entity_bone = read<uintptr_t>(BoneTransforms + (0x20 + (id * 0x8)));

	return GetPosition(read<DWORD64>(entity_bone + 0x10));
}

glm::vec3 midPoint(glm::vec3 v1, glm::vec3 v2)
{
	return glm::vec3((v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2);
}

glm::vec3 get_player_pos(std::uint64_t entity)
{
	return midPoint(get_bone_position(entity, l_foot), get_bone_position(entity, r_foot));
}

uintptr_t GetPlayerInput(uintptr_t player)
{
	return read<uintptr_t>(player + base_player::OffsetPlayerInput);
}

glm::vec2 GetViewAngles(uintptr_t Input)
{
	return read<glm::vec2>(Input + 0x3C); //bodyAngles
}

glm::vec2 GetRecoilAngle(uintptr_t Input)
{
	return read<glm::vec2>(Input + 0x64); //recoilAngles
}

void SetViewAngles(uintptr_t Input, glm::vec2 angle)
{
	write<glm::vec2>(Input + 0x3C, angle);
}

bool once = false;
void DoSpider(uintptr_t player)
{
	auto BaseMovement = read<uintptr_t>(player + base_player::OffsetPlayerMovement);

	if (!BaseMovement)
		return;


	write<float>(BaseMovement + 0xAC, 0.f); // private float groundAngle; // 0xAC
	write<float>(BaseMovement + 0xB0, 0.f); // private float groundAngleNew; // 0xB0
	//write<float>(BaseMovement + 0x74, 2.3f)
	
}

bool is_weapon(uintptr_t helditem)
{
	auto ItemName = get_item_name(helditem);
	if (ItemName.find(XorString(L"rifle")) != std::string::npos)
	{
		return true;
	}
	if (ItemName.find(XorString(L"pistol")) != std::string::npos)
	{
		return true;
	}
	if (ItemName.find(XorString(L"bow")) != std::string::npos)
	{
		return true;
	}
	if (ItemName.find(XorString(L"lmg")) != std::string::npos)
	{
		return true;
	}
	if (ItemName.find(XorString(L"shotgun")) != std::string::npos)
	{
		return true;
	}
	if (ItemName.find(XorString(L"smg")) != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

float GetRealBulletSpeed(uintptr_t local_player)
{
	const auto current_item = get_held_item(local_player);

	if (!current_item)
		return false;

	const auto base_projectile = read<uintptr_t>(current_item + 0x98);
	float projectile_velocity = read<float>(base_projectile + 0x26C);

	return projectile_velocity;
}

float GetBulletSpeed(uintptr_t local_player)
{
	const auto current_item = get_held_item(local_player);

	if (!current_item)
		return false;

	const auto held_item_name = get_item_name(current_item);

	if (held_item_name.find(XorString(L"rifle.bolt")) != std::string::npos)
		return 656.f;

	if (held_item_name.find(XorString(L"rifle.ak")) != std::string::npos || held_item_name.find(XorString(L"rifle.lr300")) != std::string::npos)
		return 375.f;

	if (held_item_name.find(XorString(L"rifle.l96")) != std::string::npos)
		return 1125.f;

	if (held_item_name.find(XorString(L"rifle.m39")) != std::string::npos)
		return 469.f;

	if (held_item_name.find(XorString(L"rifle.semiauto")) != std::string::npos)
		return 375.f;

	if (held_item_name.find(XorString(L"lmg.m249")) != std::string::npos)
		return 488.f;

	if (held_item_name.find(XorString(L"smg.mp5")) != std::string::npos)
		return 240.f;

	if (held_item_name.find(XorString(L"smg.2")) != std::string::npos)
		return 240.f;

	if (held_item_name.find(XorString(L"smg.thompson")) != std::string::npos)
		return 300.f;

	if (held_item_name.find(XorString(L"pistol.nailgun")) != std::string::npos)
		return 50.f;

	if (held_item_name.find(XorString(L"pistol.eoka")) != std::string::npos)
		return 225.f;

	if (held_item_name.find(XorString(L"pistol.m92")) != std::string::npos)
		return 300.f;

	if (held_item_name.find(XorString(L"pistol.python")) != std::string::npos)
		return 225.f;

	if (held_item_name.find(XorString(L"pistol.revolver")) != std::string::npos)
		return 300.f;

	if (held_item_name.find(XorString(L"pistol.semiauto")) != std::string::npos)
		return 300.f;

	if (held_item_name.find(XorString(L"shotgun.pump")) != std::string::npos)
		return 225.f;

	if (held_item_name.find(XorString(L"shotgun.double")) != std::string::npos)
		return 225.f;

	if (held_item_name.find(XorString(L"shotgun.spas12")) != std::string::npos)
		return 225.f;

	if (held_item_name.find(XorString(L"bow")) != std::string::npos)
		return 50.f;
}

int GetLocalSelectedWeapon()
{
	const auto current_item = get_held_item(local::local_player);

	if (!current_item)
		return false;

	const auto held_item_name = get_item_name(current_item);

	if (held_item_name.find(XorString(L"rifle.bolt")) != std::string::npos || held_item_name.find(XorString(L"rifle.l96")) != std::string::npos)
		return 2;

	if (held_item_name.find(XorString(L"rifle.ak")) != std::string::npos || held_item_name.find(XorString(L"rifle.lr300")) != std::string::npos)
		return 1;

	if (held_item_name.find(XorString(L"rifle.m39")) != std::string::npos)
		return 1;

	if (held_item_name.find(XorString(L"pistol")) != std::string::npos)
	{
		return 3;
	}
	if (held_item_name.find(XorString(L"bow")) != std::string::npos)
	{
		return 7;
	}
	if (held_item_name.find(XorString(L"lmg")) != std::string::npos)
	{
		return 6;
	}
	if (held_item_name.find(XorString(L"shotgun")) != std::string::npos)
	{
		return 4;
	}
	if (held_item_name.find(XorString(L"smg")) != std::string::npos)
	{
		return 5;
	}
}

void FastReload(std::uint64_t entity)
{
	const auto current_item = get_held_item(entity);

	if (!current_item)
		return;

	const auto held_item_name = get_item_name(current_item);

	bool isWeapon = is_weapon(current_item);

	const auto base_projectile = read<uintptr_t>(current_item + 0x98);
	float projectile_velocity = read<float>(base_projectile + 0x26C);


	//printf("%S\n", held_item_name.c_str());


	if (isWeapon) {

		if (aimbot::forceauto)
			write<bool>(base_projectile + 0x270, true);
		else
			write<bool>(base_projectile + 0x270, false);

		if (misc::nospread)
		{
			write<float>(base_projectile + 0x2d0, -1.f);
			write<float>(base_projectile + 0x2d4, -1.f);
			write<float>(base_projectile + 0x2d8, -1.f); 
		}
		if (misc::nosway) {
			const auto base_player = get_base_player(entity);
			write<float>(base_player + 0x510, 1.f);
		}

		if (misc::norecoil) {
			const auto recoil_properties = read<uintptr_t>(base_projectile + 0x2c0);
			if (!recoil_properties)
				return;

			write<float>(recoil_properties + 0x1C, 5.f);
			write<float>(recoil_properties + 0x24, 5.f);
			write<float>(recoil_properties + 0x18, 5.f);
			write<float>(recoil_properties + 0x20, 5.f);
		}
	}

	if (misc::notimeeoka)
	{
		if (std::wcsstr(held_item_name.c_str(), XorString(L"Eoka")) != nullptr)
		{
			write<float>(base_projectile + 0x340, 500.f);
		}
	}
}

void admin_flag(std::uint64_t entity, bool is_enabled)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return;

	auto player_flags = read<uintptr_t>(base_player + base_player::OffsetPlayerFlags);

	if (is_enabled)
		player_flags |= 4;
	else
		player_flags &= ~4;

	write<std::uint64_t>(base_player + base_player::OffsetPlayerFlags, player_flags);
}

void air_struck(uint64_t entity, bool enabled)
{
	const auto base_player = get_base_player(entity);

	if (!base_player)
		return;

	if (enabled == true) {
		//write<bool>(base_player + 0x498, true);
	}
	else {
		//write<bool>(base_player + 0x498, false);
	}
}

std::vector<uint64_t> RustPlayerList;
std::vector<uint64_t> RustCrateList;
std::vector<uint64_t> RustCollectibleList;
std::vector<uint64_t> RustOreList;
std::vector<uint64_t> RustAIList;
std::vector<uint64_t> RustGroundList;
std::vector<uint64_t> RustHelicopterList;
DWORD WINAPI entity_thread(LPVOID)
{
	while (TRUE)
	{
		std::vector<uint64_t> PlayerList;
		std::vector<uint64_t> CrateList;
		std::vector<uint64_t> CollectibleList;
		std::vector<uint64_t> OreList;
		std::vector<uint64_t> AIList;
		std::vector<uint64_t> GroundList;
		std::vector<uint64_t> HelicopterList;

		/* the first object is always the camera object */
		const auto first_tagged_object = read<uintptr_t>(game_object_manager + 0x8);

		if (!first_tagged_object)
			continue;

		/* unity objects are in a linked list */
		const auto object_entry = read<uintptr_t>(first_tagged_object + 0x10);

		if (!object_entry)
			continue;

		/* now we're accessing the actual object's instance */
		const auto object_instance = read<uintptr_t>(object_entry + 0x30);

		if (!object_instance)
			continue;

		/* here we're accessing the object's class / object game uses */
		local::camera_instance.store(read<uintptr_t>(object_instance + 0x18));

		const auto unk1 = read<uintptr_t>(base_networkable + 0xb8);

		if (!unk1)
			continue;

		const auto client_entities = read<uintptr_t>(unk1);

		if (!client_entities)
			continue;

		const auto entity_realm = read<uintptr_t>(client_entities + 0x10);

		if (!entity_realm)
			continue;

		const auto buffer_list = read<uintptr_t>(entity_realm + 0x28);

		if (!buffer_list)
			continue;

		const auto object_list = read<uintptr_t>(buffer_list + 0x18);

		if (!object_list)
			continue;

		const auto object_list_size = read<std::uint32_t>(buffer_list + 0x10);

		for (auto i = 0u; i < object_list_size; i++)
		{

			const auto current_object = read<uintptr_t>(object_list + (0x20 + (i * 8)));

			if (!current_object)
				continue;

			const auto object_name = get_class_name(current_object);

			if (object_name == "")
				continue;

			if (strstr(object_name.c_str(), XorString("BasePlayer"))) {



				/* garbo shiz again */
				const auto unk1 = read<uintptr_t>(current_object + 0x10);

				if (!unk1)
					continue;

				const auto unk2 = read<uintptr_t>(unk1 + 0x30);

				if (!unk2)
					continue;

				const auto player = read<uintptr_t>(unk2 + 0x30);

				if (!player)
					continue;

				if (i == 0)
				{
					local::local_player = player;
					continue;
				}

				//glm::vec2 player_screen{};
				const glm::vec3 player_position = get_obj_pos(player);

				//if (!math::world_to_screen(player_position, &player_screen))
				//	continue;

				const auto player_sleeping = get_player_sleeping(player);
				const auto player_health = get_player_health(player);
				const auto player_name = get_player_name(player);
				const int player_distance = (int)ceil(glm::distance(player_position, get_obj_pos(local::local_player)));

				if (player_health <= 0) {
					continue;
				}
				if (player_distance > 400)
					continue;

				PlayerList.push_back(player);
				
			}

			const auto unk1 = read<uintptr_t>(current_object + 0x10);

			if (!unk1)
				continue;

			const auto unk2 = read<uintptr_t>(unk1 + 0x30);

			if (!unk2)
				continue;

			const auto crate = read<uintptr_t>(unk2 + 0x30);
			const auto collectables = read<uintptr_t>(unk2 + 0x30);
			const auto ore = read<uintptr_t>(unk2 + 0x30);
			const auto scientist = read<uintptr_t>(unk2 + 0x30);
			const auto helicopter = read<uintptr_t>(unk2 + 0x30);

			if (object_name.find(XorString("LootCo")) != std::string::npos) {

				if (!crate)
					continue;

				const glm::vec3 crate_position = get_obj_pos(crate);
				const int crate_distance = glm::distance(crate_position, get_obj_pos(local::local_player));

				if (crate_distance <= visuals::MaxCrateDistance)
				{
					CrateList.push_back(unk2);
				}
			}

			if (object_name.find(XorString("Collectible")) != std::string::npos) {

				if (!collectables)
					continue;

				const glm::vec3 coll_position = get_obj_pos(collectables);
				const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

				if (coll_distance <= visuals::MaxCollectableDistance)
				{
					CollectibleList.push_back(unk2);
				}
			}

			if (object_name.find(XorString("OreRe")) != std::string::npos) {

				if (!ore)
					continue;

				const glm::vec3 ore_position = get_obj_pos(ore);
				const int ore_distance = glm::distance(ore_position, get_obj_pos(local::local_player));

				if (ore_distance <= visuals::MaxOreDistance)
				{
					OreList.push_back(unk2);
				}
			}

			if ((strstr(object_name.c_str(), XorString("Scientist")) || strstr(object_name.c_str(), XorString("ScientistNPC")))) {

				if (!scientist)
					continue;

				const glm::vec3 scientist_position = get_obj_pos(scientist);
				const int scientist_distance = glm::distance(scientist_position, get_obj_pos(local::local_player));

				if (scientist_distance <= visuals::MaxScientistDistance)
				{
					AIList.push_back(unk2);
				}
			}

			auto class_name = get_class_name(current_object);
			if (class_name.find(XorString("DroppedItem")) != std::string::npos)
			{
				GroundList.push_back(current_object);
			}

			if (object_name.find(XorString("Scraptransporthelicopter")) != std::string::npos) {

				if (!helicopter)
					continue;

				HelicopterList.push_back(unk2);
			}

		}

		RustPlayerList.clear();
		RustPlayerList = PlayerList;
		RustCrateList.clear();
		RustCrateList = CrateList;
		RustCollectibleList.clear();
		RustCollectibleList = CollectibleList;
		RustOreList.clear();
		RustOreList = OreList;
		RustAIList.clear();
		RustAIList = AIList;
		RustGroundList.clear();
		RustGroundList = GroundList;
		RustHelicopterList.clear();
		RustHelicopterList = HelicopterList;

		SaveCPU(250);
	}
}
