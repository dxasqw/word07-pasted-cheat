using namespace settings;
using namespace math;
float distances = 0.f;

void draw_skeleton(uint64_t player)
{

	int aSkeleton[][2] =
	{
			{ neck, spine1 },
			{ spine1, l_hip }, { l_hip,  l_knee }, {  l_knee, l_foot },
			{ spine1, r_hip }, { r_hip,  r_knee }, {  r_knee, r_foot },
			{ neck, l_upperarm }, { l_upperarm, l_forearm },{ l_forearm, l_hand },
			{ neck, r_upperarm }, { r_upperarm, r_forearm },{ r_forearm, r_hand },
	};

	RGBA SkelColor = { colors::skelcol[0] * 255, colors::skelcol[1] * 255, colors::skelcol[2] * 255, 255 };

	if (menu::rainbow_colors)
		SkelColor = Col.rainbow();

	for (int i = 0; i < 13; ++i)
	{
		glm::vec3 Bone1 = get_bone_position(player, aSkeleton[i][0]);
		if (Bone1 == glm::vec3(0, 0, 0))
			continue;

		glm::vec3 Bone2 = get_bone_position(player, aSkeleton[i][1]);
		if (Bone2 == glm::vec3(0, 0, 0))
			continue;

		glm::vec2 Out1;
		glm::vec2 Out2;

		if (world_to_screen(Bone1, &Out1) && world_to_screen(Bone2, &Out2)) {
			DrawLine(Out1.x, Out1.y, Out2.x, Out2.y, &SkelColor, menu::box_thick);
		}
	}
}

static void players_draw()
{
	for (uintptr_t player : RustPlayerList)
	{
		RGBA ESPColor = { colors::espcol[0] * 255, colors::espcol[1] * 255, colors::espcol[2] * 255, 255 };
		const glm::vec3 player_position = get_obj_pos(player);

		const auto player_sleeping = get_player_sleeping(player);
		const auto player_health = get_player_health(player);
		const auto player_name = get_player_name(player);
		std::wstring player_item = get_player_item_name(player);
		const int player_distance = (int)ceil(glm::distance(player_position, get_obj_pos(local::local_player)));
		//printf("%s\n", player_item.c_str());

		visuals::CurrentPosition = get_obj_pos(local::local_player);

		auto BoxHead = get_bone_position(player, head);

		if (GetAsyncKeyState(hotkeys::aimkey)) {
			if (player == math::aim::resultant_entity)
				ESPColor = Col.skyblue;
		}

		glm::vec2 player_screen{};
		glm::vec2 head_screen{};
		glm::vec2 normal_head{};

		if (menu::rainbow_colors)
			ESPColor = Col.rainbow();

		if (!world_to_screen(player_position, &player_screen))
			continue;

		if (!world_to_screen(glm::vec3(BoxHead.x, BoxHead.y + 0.3, BoxHead.z), &head_screen))
			continue;

		if (!world_to_screen(BoxHead, &normal_head))
			continue;

		if (!player_sleeping)
		{
			float BoxHeight = player_screen.y - head_screen.y;
			float BoxWidth = BoxHeight / 1.8f;

			if (visuals::name)
			{
				char name[64];
				sprintf_s(name, XorString("[%dm] - %S"), player_distance, player_name.c_str());
				DrawString(menu::font_size, head_screen.x, head_screen.y - 5, &Col.white_, true, true, name);
			}

			if (visuals::box)
			{
				if (visuals::boxMode == 0 || visuals::boxMode == 1)
				{
					if (visuals::outline)
					{
						DrawNormalBox(player_screen.x - BoxWidth / 2 + 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						DrawNormalBox(player_screen.x - BoxWidth / 2 - 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						DrawNormalBox(player_screen.x - BoxWidth / 2, head_screen.y + 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						DrawNormalBox(player_screen.x - BoxWidth / 2, head_screen.y - 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
					}
					DrawNormalBox(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &ESPColor);
				}
				if (visuals::boxMode == 2 || visuals::boxMode == 3)
				{
					if (visuals::outline)
					{
						DrawCornerBox(player_screen.x - BoxWidth / 2 + 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						DrawCornerBox(player_screen.x - BoxWidth / 2 - 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						DrawCornerBox(player_screen.x - BoxWidth / 2, head_screen.y + 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						DrawCornerBox(player_screen.x - BoxWidth / 2, head_screen.y - 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
					}
					DrawCornerBox(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &ESPColor);
				}

				if (visuals::boxMode == 1 || visuals::boxMode == 3) menu::box_thick = 1,
					DrawFilledRect(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, &Col.filled);
			}

			if (visuals::health)
			{
				if (visuals::healthMode == 0 || visuals::healthMode == 3)
					DrawLeftProgressBar(player_screen.x, head_screen.y, BoxWidth, BoxHeight, 1, player_health);
				if (visuals::healthMode == 1 || visuals::healthMode == 4)
					DrawRightProgressBar(player_screen.x, head_screen.y, BoxWidth, BoxHeight, 1, player_health);
				if (visuals::healthMode == 2 || visuals::healthMode == 3 || visuals::healthMode == 4)
				{
					char vida[100];
					sprintf(vida, XorString("Health: %d "), player_health);
					DrawString(12, player_screen.x, player_screen.y + 5, &Col.white, true, true, vida);
				}
			}

			if (visuals::skel) {
				if (player_distance <= visuals::MaxSkeletonDrawDistance) {
					draw_skeleton(player);
				}
			}

			if (visuals::lines)
			{
				if (visuals::lineMode == 0)
					DrawLine((Width / 2), Height, player_screen.x, player_screen.y, &ESPColor, menu::box_thick);
				if (visuals::lineMode == 1)
					DrawLine((Width), Height / 2, player_screen.x, player_screen.y, &ESPColor, menu::box_thick);
				if (visuals::lineMode == 2)
					DrawLine((Width / 2), Height / 2, player_screen.x, player_screen.y, &ESPColor, menu::box_thick);
			}

			if (visuals::show_head)
				DrawCircle(normal_head.x, normal_head.y, BoxHeight / 25, &Col.white_, 15);


			if (player_item.find(XorString(L"rifle.bolt")) != std::string::npos)
				player_item = XorString(L"BOLT Sniper");

			if (player_item.find(XorString(L"rifle.ak")) != std::string::npos)
				player_item = XorString(L"AK-47 Rifle");

			if (player_item.find(XorString(L"rifle.lr300")) != std::string::npos)
				player_item = XorString(L"LR300 Rifle");

			if (player_item.find(XorString(L"rifle.l96")) != std::string::npos)
				player_item = XorString(L"AWM Sniper");

			if (player_item.find(XorString(L"rifle.m39")) != std::string::npos)
				player_item = XorString(L"M39 Rifle");

			if (player_item.find(XorString(L"rifle.semiauto")) != std::string::npos)
				player_item = XorString(L"Semi Auto Rifle");

			if (player_item.find(XorString(L"lmg.m249")) != std::string::npos)
				player_item = XorString(L"M249 LMG");

			if (player_item.find(XorString(L"smg.mp5")) != std::string::npos)
				player_item = XorString(L"MP5 SMG");

			if (player_item.find(XorString(L"smg.2")) != std::string::npos)
				player_item = XorString(L"SMG Auto");

			if (player_item.find(XorString(L"smg.thompson")) != std::string::npos)
				player_item = XorString(L"Thompson SMG");

			if (player_item.find(XorString(L"pistol.nailgun")) != std::string::npos)
				player_item = XorString(L"Nailgun Pistol");

			if (player_item.find(XorString(L"pistol.eoka")) != std::string::npos)
				player_item = XorString(L"EOKA Pistol");

			if (player_item.find(XorString(L"pistol.m92")) != std::string::npos)
				player_item = XorString(L"M92 Pistol");

			if (player_item.find(XorString(L"pistol.python")) != std::string::npos)
				player_item = XorString(L"Python Pistol");

			if (player_item.find(XorString(L"pistol.revolver")) != std::string::npos)
				player_item = XorString(L"Revolver Pistol");

			if (player_item.find(XorString(L"pistol.semiauto")) != std::string::npos)
				player_item = XorString(L"Semi Auto Pistol");

			if (player_item.find(XorString(L"shotgun.pump")) != std::string::npos)
				player_item = XorString(L"Shotgun Pump");

			if (player_item.find(XorString(L"shotgun.double")) != std::string::npos)
				player_item = XorString(L"Double Shotgun");

			if (player_item.find(XorString(L"shotgun.spas12")) != std::string::npos)
				player_item = XorString(L"SPAS-12 Shotgun");

			if (visuals::wepnhands)
			{
				char vida[100];
				sprintf(vida, XorString("%ls"), player_item.c_str());
				DrawString(menu::font_size, head_screen.x, head_screen.y - 15, &Col.red, true, true, vida);
			}

			//auto base_player = get_base_player(player);
			//uintptr_t PlayerModel = read<uintptr_t>(base_player + 0x490); //public PlayerModel playerModel;
			//glm::vec3 vel = read<glm::vec3>(PlayerModel + 0x1f4);
			//char vell[100];
			//sprintf(vell, XorString("x%f y%f z%f"), vel.x, vel.y, vel.z);
			//DrawString(menu::font_size, head_screen.x, head_screen.y , &Col.red, true, true, vell);
		}
		else
		{
			char txt[64];
			sprintf(txt, XorString("%dm - %s"), player_distance, XorString("Sleeping Player"));
			if (visuals::sleeping_player)
				DrawString(menu::font_size, player_screen.x, player_screen.y, &Col.red, true, true, txt);
		}

	}

	glm::vec3 SavePosition1 = settings::visuals::SavePosition1;
	glm::vec2 SavePos1{};

	if (SavePosition1.x != 0 || SavePosition1.y != 0 || SavePosition1.z != 0)
	{
		if (world_to_screen(SavePosition1, &SavePos1))
		{
			const int save_distance = (int)ceil(glm::distance(SavePosition1, get_obj_pos(local::local_player)));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), save_distance, XorString("Home1"));
			DrawString(14, SavePos1.x, SavePos1.y, &Col.yellow, true, true, txt);
		}
	}
}

static void crates_draw()
{
	if (!visuals::show_crates)
		return;

	for (uintptr_t crates : RustCrateList)
	{
		const auto crate = read<uintptr_t>(crates + 0x30);

		if (!crate)
			continue;

		const auto crateName = read<uintptr_t>(crates + 0x60);
		std::string name = read_ascii(crateName, 64);

		RGBA CrateColor = { colors::cratecol[0] * 255, colors::cratecol[1] * 255, colors::cratecol[2] * 255, 255 };

		if (name.find(XorString("crate_tools")) != std::string::npos && visuals::crate_tools) {

			glm::vec2 crate_screen{};
			const glm::vec3 crate_position = get_obj_pos(crate);

			if (!world_to_screen(crate_position, &crate_screen))
				continue;

			const int crate_distance = glm::distance(crate_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), crate_distance, XorString("Tools Crate"));
			DrawString(menu::font_size, crate_screen.x, crate_screen.y, &CrateColor, true, true, txt);
		}
		if (strstr(name.c_str(), XorString("assets/bundled/prefabs/radtown/crate_normal.prefab")) && visuals::crate_military) {

			glm::vec2 crate_screen{};
			const glm::vec3 crate_position = get_obj_pos(crate);

			if (!world_to_screen(crate_position, &crate_screen))
				continue;

			const int crate_distance = glm::distance(crate_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), crate_distance, XorString("Military Crate"));
			DrawString(menu::font_size, crate_screen.x, crate_screen.y, &CrateColor, true, true, txt);
		}
		if (strstr(name.c_str(), XorString("assets/bundled/prefabs/radtown/crate_normal_2.prefab")) && visuals::crate_normal) {

			glm::vec2 crate_screen{};
			const glm::vec3 crate_position = get_obj_pos(crate);

			if (!world_to_screen(crate_position, &crate_screen))
				continue;

			const int crate_distance = glm::distance(crate_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), crate_distance, XorString("Normal Crate"));
			DrawString(menu::font_size, crate_screen.x, crate_screen.y, &CrateColor, true, true, txt);
		}
		if (name.find(XorString("crate_elite")) != std::string::npos && visuals::crate_elite) {

			glm::vec2 crate_screen{};
			const glm::vec3 crate_position = get_obj_pos(crate);

			if (!world_to_screen(crate_position, &crate_screen))
				continue;

			const int crate_distance = glm::distance(crate_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), crate_distance, XorString("Elite Crate"));
			DrawString(menu::font_size, crate_screen.x, crate_screen.y, &CrateColor, true, true, txt);
		}
		if (name.find(XorString("barrel")) != std::string::npos && visuals::crate_barrel) {

			glm::vec2 crate_screen{};
			const glm::vec3 crate_position = get_obj_pos(crate);

			if (!world_to_screen(crate_position, &crate_screen))
				continue;

			const int crate_distance = glm::distance(crate_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), crate_distance, XorString("Barrel"));
			DrawString(menu::font_size, crate_screen.x, crate_screen.y, &CrateColor, true, true, txt);
		}
	}
}

static void collectables_draw()
{
	if (!visuals::show_collectable)
		return;

	for (uintptr_t collect : RustCollectibleList)
	{
		const auto coll = read<uintptr_t>(collect + 0x30);

		if (!coll)
			continue;

		const auto collectName = read<uintptr_t>(collect + 0x60);
		std::string name = read_ascii(collectName, 64);

		RGBA CollColor = { colors::collcol[0] * 255, colors::collcol[1] * 255, colors::collcol[2] * 255, 255 };

		if (name.find(XorString("hemp")) != std::string::npos && visuals::coll_vegetables) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Hemp"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}

		if (name.find(XorString("mushroom")) != std::string::npos && visuals::coll_vegetables) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Mushroom"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}

		if (name.find(XorString("pumpkin")) != std::string::npos && visuals::coll_vegetables) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Pumpkin"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}

		if (name.find(XorString("corn")) != std::string::npos && visuals::coll_vegetables) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Corn"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}

		if (name.find(XorString("wood")) != std::string::npos && visuals::coll_wood) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Wood"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}

		if (name.find(XorString("stone-col")) != std::string::npos && visuals::coll_stone) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Stone"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}

		if (name.find(XorString("metal")) != std::string::npos && visuals::coll_metal) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Metal"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}

		if (name.find(XorString("sulfur")) != std::string::npos && visuals::coll_sulfur) {

			glm::vec2 coll_screen{};
			const glm::vec3 coll_position = get_obj_pos(coll);

			if (!world_to_screen(coll_position, &coll_screen))
				continue;

			const int coll_distance = glm::distance(coll_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), coll_distance, XorString("Sulfur"));
			DrawString(menu::font_size, coll_screen.x, coll_screen.y, &CollColor, true, true, txt);
		}
	}
}

static void ore_draw()
{
	if (!visuals::show_ore)
		return;

	for (uintptr_t Ore : RustOreList)
	{
		const auto ore = read<uintptr_t>(Ore + 0x30);

		if (!ore)
			continue;

		const auto collectName = read<uintptr_t>(Ore + 0x60);
		std::string name = read_ascii(collectName, 64);

		RGBA OreColor = { colors::orecol[0] * 255, colors::orecol[1] * 255, colors::orecol[2] * 255, 255 };

		if (name.find(XorString("stone-ore")) != std::string::npos && visuals::ore_stone) {

			glm::vec2 ore_screen{};
			const glm::vec3 ore_position = get_obj_pos(ore);

			if (!world_to_screen(ore_position, &ore_screen))
				continue;


			const int ore_distance = glm::distance(ore_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), ore_distance, XorString("Stone-Ore"));
			DrawString(menu::font_size, ore_screen.x, ore_screen.y, &OreColor, true, true, txt);
		}

		if (name.find(XorString("metal-ore")) != std::string::npos && visuals::ore_metal) {

			glm::vec2 ore_screen{};
			const glm::vec3 ore_position = get_obj_pos(ore);

			if (!world_to_screen(ore_position, &ore_screen))
				continue;


			const int ore_distance = glm::distance(ore_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), ore_distance, XorString("Metal-Ore"));
			DrawString(menu::font_size, ore_screen.x, ore_screen.y, &OreColor, true, true, txt);
		}

		if (name.find(XorString("sulfur-ore")) != std::string::npos && visuals::ore_sulfur) {

			glm::vec2 ore_screen{};
			const glm::vec3 ore_position = get_obj_pos(ore);

			if (!world_to_screen(ore_position, &ore_screen))
				continue;


			const int ore_distance = glm::distance(ore_position, get_obj_pos(local::local_player));

			char txt[64];
			sprintf(txt, XorString("%dm - %s"), ore_distance, XorString("Sulfur-Ore"));
			DrawString(menu::font_size, ore_screen.x, ore_screen.y, &OreColor, true, true, txt);
		}
	}
}

static void scientist_draw()
{
	if (!visuals::show_scientists)
		return;

	for (uintptr_t AI : RustAIList)
	{
		RGBA ScientColor = { colors::scientistcol[0] * 255, colors::scientistcol[1] * 255, colors::scientistcol[2] * 255, 200 };

		const auto scientist = read<uintptr_t>(AI + 0x30);

		glm::vec2 scientist_screen{};
		glm::vec2 head_screen{};
		const glm::vec3 scientist_position = get_obj_pos(scientist);
		const int scientist_distance = glm::distance(scientist_position, get_obj_pos(local::local_player));

		const auto scientist_health = get_player_health(scientist);
		const auto scientist_item = get_player_item_name(scientist);

		auto BoxHead = get_bone_position(scientist, head);

		if (GetAsyncKeyState(hotkeys::aimkey)) {
			if (scientist == math::aim::resultant_entity)
				ScientColor = Col.skyblue;
		}

		if (!world_to_screen(scientist_position, &scientist_screen))
			continue;

		if (!world_to_screen(glm::vec3(BoxHead.x, BoxHead.y + 0.3, BoxHead.z), &head_screen))
			continue;

		float BoxHeight = scientist_screen.y - head_screen.y;
		float BoxWidth = BoxHeight / 1.8f;

		if (visuals::box)
		{
			DrawNormalBox(scientist_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &ScientColor);
		}

		char vida[100];
		sprintf(vida, XorString("Weapon: %ls"), scientist_item.c_str());
		DrawString(menu::font_size, head_screen.x, head_screen.y - 15, &ScientColor, true, true, vida);

		char txt[100];
		sprintf(txt, XorString("[%dm] - %s"), scientist_distance, XorString("Scientist"));
		DrawString(menu::font_size, head_screen.x, head_screen.y - 5, &ScientColor, true, true, txt);

		char vida2[100];
		sprintf(vida2, XorString("Health: %dHP"), (int)scientist_health);
		DrawString(menu::font_size, head_screen.x, head_screen.y - 25, &ScientColor, true, true, vida2);
		//draw_skeleton(scientist);
	}
}

static void grounditems_draw()
{
	if (!visuals::show_droppeditems)
		return;

	for (uintptr_t Ground : RustGroundList)
	{
		RGBA ItemColor = { colors::itemscol[0] * 255, colors::itemscol[1] * 255, colors::itemscol[2] * 255, 255 };

		const auto baseObject = read<uintptr_t>(Ground + 0x10);

		if (!baseObject)
			continue;

		const auto object = read<uintptr_t>(baseObject + 0x30);

		if (!object)
			continue;

		auto CurrentItem = read<uintptr_t>(Ground + 0x150);

		uint64_t objectClass = read<uint64_t>(object + 0x30);
		auto Transform = read<uintptr_t>(objectClass + 0x8);
		auto VisualState = read<uintptr_t>(Transform + 0x38);
		glm::vec3 item_pos = read<glm::vec3>(VisualState + 0x90);
		glm::vec2 item_screen{};

		int ItemAmmount = read<int>(CurrentItem + 0x30);

		const int items_distance = glm::distance(item_pos, get_obj_pos(local::local_player));
		const auto item_name = get_item_name(CurrentItem);

		if (!world_to_screen(item_pos, &item_screen))
			continue;

		if (items_distance <= visuals::MaxCollectableDistance)
		{
			char txt[100];
			sprintf(txt, XorString("%dm - %ls - %d"), items_distance, item_name.c_str(), ItemAmmount);
			DrawString(menu::font_size, item_screen.x, item_screen.y, &ItemColor, true, true, txt);
		}
	}
}

static void draw_helicopter()
{
	if (!visuals::show_droppeditems)
		return;

	for (uintptr_t heli : RustHelicopterList)
	{
		RGBA ItemColor = { colors::itemscol[0] * 255, colors::itemscol[1] * 255, colors::itemscol[2] * 255, 255 };

		const auto helicopter = read<uintptr_t>(heli + 0x30);

		glm::vec2 heli_screen{};
		const glm::vec3 heli_position = get_obj_pos(helicopter);
		const int heli_distance = glm::distance(heli_position, get_obj_pos(local::local_player));

		if (!world_to_screen(heli_position, &heli_screen))
			continue;

		char txt[100];
		sprintf(txt, "%dm - %s", heli_distance, "Helicopter");
		DrawString(menu::font_size, heli_screen.x, heli_screen.y, &ItemColor, true, true, txt);
	}
}

void features()
{
	if (misc::peter_parker)
		DoSpider(get_base_player(local::local_player));

	if (misc::admin_flag == true)
		admin_flag(local::local_player, true);
	else if (misc::admin_flag == false)
		admin_flag(local::local_player, false);


	if (GetAsyncKeyState(hotkeys::airstuckey))
		misc::airstuck = true;
	else
		misc::airstuck = false;

	if (misc::airstuck == true)
		air_struck(local::local_player, true);
	else if (misc::airstuck == false)
		air_struck(local::local_player, false);

	FastReload(local::local_player);
}

static void debug_draw()
{
	if (settings::menu::overlay_fps) {
		char fpsinfo[64];
		sprintf(fpsinfo, XorString("Overlay FPS: %0.f"), ImGui::GetIO().Framerate);
		RGBA FPS = Col.red;
		if (menu::rainbow_colors)
			FPS = Col.rainbow();
		DrawStrokeText(30, 35, &FPS, fpsinfo);
	}

	

	if (menu::debug)
	{
		char vida[100];
		const auto Input = GetPlayerInput(get_base_player(local::local_player));
		sprintf(vida, XorString("%f %f %f"), GetViewAngles(Input).x, GetViewAngles(Input).y, GetViewAngles(Input).y);
		DrawString(12, 45, 45, &Col.white, false, false, vida);
	}

	char txt[100];
	sprintf(txt, "Current Bullet Speed: %f", GetBulletSpeed(local::local_player));
	DrawString(menu::font_size, 25, 65, &Col.yellow, false, true, txt);

	const auto current_item = get_held_item(local::local_player);

	if (!current_item)
		return;

	char txt2[100];
	sprintf(txt2, "Current Weapon: %S", get_item_name(current_item).c_str());
	DrawString(menu::font_size, 25, 85, &Col.yellow, false, true, txt2);

	const auto base_projectile = read<uintptr_t>(current_item + 0x98);
	float projectile_velocity = read<float>(base_projectile + 0x26C);

	char txt3[100];
	sprintf(txt3, "Proj Vel: %f", projectile_velocity);
	DrawString(menu::font_size, 25, 105, &Col.yellow, false, true, txt3);
}

void PlayerList()
{
	if (!menu::menu_key)
		return;

	if (!menu::player_list)
		return;

	static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;

	ImGui::Begin(XorString("Players Around List"), NULL, flags);
	{
		ImGui::SetWindowSize(ImVec2(675, 300), ImGuiCond_Once);
		{
			ImGui::BeginChild(XorString("##players"), ImVec2(-1, -1));
			{
				ImGui::Columns(2, XorString("##mycolumns"));
				ImGui::Separator();
				ImGui::Text(XorString("Players List: ")); ImGui::NextColumn();
				ImGui::Text(XorString("Informations: ")); ImGui::NextColumn();

				static int index;
				std::vector< std::string > playersList;
				for (uintptr_t player : RustPlayerList)
				{
					if (!player)
						continue;

					auto player_name = get_player_name_string(player);

					playersList.push_back(player_name);
				}

				std::vector< const char* > players_cstr;
				for (int x = 0; x < playersList.size(); x++)
				{
					players_cstr.emplace_back(playersList[x].c_str());
				}

				auto players_array = playersList.data();
				ImGui::ListBox(XorString("##namesplayers"), &index, players_cstr.data(), players_cstr.size()); ImGui::NextColumn();

				for (uintptr_t player : RustPlayerList)
				{
					if (!player)
						continue;

					auto player_name = get_player_name_string(player);

					if (player_name != playersList[index].c_str())
						continue;

					const glm::vec3 player_position = get_obj_pos(player);
					const auto player_sleeping = get_player_sleeping(player);
					const auto player_health = get_player_health(player);
					const auto player_item = get_player_item_name(player);
					const auto player_admin = get_player_admin(player);
					const auto player_steam = get_steam_id(player);
					const int player_distance = (int)ceil(glm::distance(player_position, get_obj_pos(local::local_player)));

					char selected[300];
					ImGui::Text(XorString("Selected Player: %s"), player_name);
					ImGui::Text(XorString("Item in Hands: %S"), player_item.c_str());
					ImGui::Text(XorString("Health: %d"), player_health);
					ImGui::Text(XorString("SteamID: %d"), player_steam);
					if (player_sleeping) ImGui::Text(XorString("Sleeping: Yes"), player_health); else ImGui::Text(XorString("Sleeping: No"), player_health);
					if (player_admin) ImGui::Text(XorString("Admin: Yes"), player_health); else ImGui::Text(XorString("Admin: No"), player_health);
					ImGui::Text(XorString("Distance: %d"), (int)player_distance);

					ImGui::Text(XorString("Position:"));
					ImGui::Text(XorString("x-> %f"), player_position.x);
					ImGui::Text(XorString("y-> %f"), player_position.y);
					ImGui::Text(XorString("z-> %f"), player_position.z);
				}
			}
		}
	}
	ImGui::End();
}

static void draw_things()
{
	players_draw();
	crates_draw();
	collectables_draw();
	ore_draw();
	scientist_draw();
	grounditems_draw();
	features();
	debug_draw();
	crosshair_draw();
	shortcurts();
	PlayerList();

	if (menu::limit60)
		Sleep(15);
}