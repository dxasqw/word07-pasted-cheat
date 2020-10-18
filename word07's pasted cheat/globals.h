namespace offsets
{

	namespace managers
	{
		uint64_t engine = NULL;
		uint64_t gnames = NULL;
		uint64_t world = NULL;
		uint64_t viewport = NULL;
		uint64_t world_test = NULL;
	}

	namespace base_player
	{
		uint64_t OffsetLifestate =                 0x1EC;   // public BaseCombatEntity.LifeState lifestate
		uint64_t OffsetPlayerHealth =              0x1F4;   // private float _health
		uint64_t OffsetPlayerModel =               0x490;   // public PlayerModel playerModel
		uint64_t OffsetFrozen =                    0x498;   // public bool Frozen
		uint64_t OffsetClientTeam =                0x500;   // public PlayerTeam clientTeam
		uint64_t OffsetPlayerFlags =               0x5B8;   // public BasePlayer.PlayerFlags playerFlags
		uint64_t OffsetPlayerInventory =           0x5C8;   // public PlayerInventory inventory
		uint64_t OffsetPlayerInput =               0x5E0;  // public PlayerInput input
		uint64_t OffsetPlayerMovement =            0x5E8;   // public BaseMovement movement
		uint64_t OffsetSteamID =                   0x610;   // public ulong userID
		uint64_t OffsetUserIDString =              0x618;   // public string UserIDString
		uint64_t OffsetUserDisplayName =           0x620;   // protected string _displayName
		uint64_t OffsetNoBlockAiming =             0x63C;   // public bool clothingBlocksAiming
		uint64_t OffsetSpeedReduction =            0x640;   // public float clothingMoveSpeedReduction
		uint64_t OffsetWaterBonus =                0x644;   // public float clothingWaterSpeedBonus
		uint64_t OffsetNoSway =                    0x648;   // public float clothingAccuracyBonus
	}

	namespace items
	{
		uint64_t OffsetSkin =                      0x50;    // public ulong skin
		uint64_t OffsetName =                      0x58;    // public string name
		uint64_t OffsetHeld =                      0x98;    // private EntityRef heldEntity
	}

	namespace base_projectile
	{
		uint64_t OffsetFractionalReload =          0x2A8;   // public bool fractionalReload
		uint64_t OffsetAutomatic =                 0x270;  // public bool automatic
		uint64_t OffsetAiming =                    0x2F1;   // public bool aiming
		uint64_t OffsteDistanceScale =             0x268;  // public float distanceScale
		uint64_t OffsetProjectileVelocityScale =   0x26C;  // public float projectileVelocityScale
	}

	namespace model_player
	{
		uint64_t OffsetIsLocalPlayer = 0x251;
		uint64_t OffsetPlayerVelocity = 0x1f4;
	}

	namespace local
	{
		std::uint64_t local_player = 0;
		std::atomic<uint64_t> camera_instance{};
	}

}

namespace settings
{
	namespace aimbot
	{
		bool aimbot = false;
		bool ignore_team = false;
		bool rcs = true;
		bool forceauto = false;
		bool smooth = false;
		bool fovcircle = false;
		bool prediction = false;
		bool alonercs = false;

		int smoothscale = 1;
		float aimspeed = 1.f;
		float aimfov = 25;

		int selected_weapon = 0;

		int hitbox = 0;

		uint64_t resultant_entity;
	}

	namespace items
	{
		bool enable_items = false;
		bool meds = false;
		bool armors = false;
		bool attach = false;
		bool rifles = false;
		bool snipers = false;
		bool weapons = false;
		bool ammo = false;
		bool clothing = false;
		bool others = false;
	}

	namespace visuals
	{
		bool box = false;
		bool skel = false;
		bool car = false;
		bool health = false;
		bool zombies = false;
		bool animals = false;
		bool wepnhands = false;
		bool name = false;
		bool dbgname = false;
		bool crosshair = false;
		bool outline = false;
		bool lines = false;
		bool knocked = false;
		bool team = false;
		bool team_name = false;
		bool show_head = false;
		bool health_based = false;
		bool sleeping_player = false;

		bool show_ore = false;
		bool ore_stone = false;
		bool ore_metal = false;
		bool ore_sulfur = false;

		bool show_collectable = false;
		bool coll_vegetables = false;
		bool coll_wood = false;
		bool coll_stone = false;
		bool coll_metal = false;
		bool coll_sulfur = false;

		bool show_crates = false;
		bool crate_tools = false;
		bool crate_military = false;
		bool crate_normal = false;
		bool crate_barrel = false;
		bool crate_elite = false;

		bool show_droppeditems = false;
		bool show_scientists = false;

		int boxMode = 0;
		int nameMode = 0;
		int skelMode = 0;
		int animMode = 0;
		int itemMode = 0;
		int carMode = 0;
		int lineMode = 0;
		int healthMode = 0;

		int NumberofEntity = 0;
		int SpectatorCount = 0;

		int MaxDistance = 1000;
		int MaxCrateDistance = 100;
		int MaxCollectableDistance = 50;
		int MaxOreDistance = 100;
		int MaxScientistDistance = 200;
		int MaxSkeletonDrawDistance = 50;
		int MaxZombDistance = 300;
		int MaxAnimalDistance = 300;

		glm::vec3 CurrentPosition = { 0, 0, 0 };
		glm::vec3 SavePosition1 = { 0, 0, 0 };
	}

	namespace colors
	{
		float chamscol[3] = { 1.0f , 0.0f , 0.0f };
		float espcol[3] = { 1.0f , 0.0f , 0.0f };
		float skelcol[3] = { 1.0f , 1.0f , 1.0f };
		float crosscol[3] = { 1.0f , 0.0f , 0.0f };

		float orecol[3] = { 1.0f , 0.0f , 0.0f };
		float collcol[3] = { 1.0f , 0.0f , 0.0f };
		float cratecol[3] = { 1.0f , 0.0f , 0.0f };
		float scientistcol[3] = { 1.0f , 0.0f , 0.0f };
		float itemscol[3] = { 1.0f , 0.0f , 0.0f };
	}

	namespace misc
	{
		bool speedhack = false;
		bool superjump = false;
		bool removegrass = false;
		bool alwaysday = false;
		bool overlayfps = false;

		bool peter_parker = false;
		bool admin_flag = false;
		bool norecoil = false;
		bool nospread = false;
		bool nosway = false;
		bool notimeeoka = false;
		bool airstuck = false;

		float speedval = 2.0f;
		float settime = 0.f;
		float superheight = 1;
		int superscale = 2;
	}

	namespace menu
	{
		bool rainbow_colors = false;
		bool menu_key = false;
		bool player_list = false;
		bool overlay_fps = true;
		bool debug = false;
		bool debug2 = false;
		bool watermark = true;
		bool limit60 = false;
		int font_size = 14;
		int box_thick = 1;
		float rainbow_speed = 0.25f;
		float crosshair_size = 1.f;
		static int settsMode = 0;
		ImFont* SkeetFont;
	}

	namespace hotkeys
	{
		int aimkey;
		int airstuckey;
	}

	static const char* keyNames[] =
	{
		"",
		"Left Mouse",
		"Right Mouse",
		"Cancel",
		"Middle Mouse",
		"Mouse 5",
		"Mouse 4",
		"",
		"Backspace",
		"Tab",
		"",
		"",
		"Clear",
		"Enter",
		"",
		"",
		"Shift",
		"Control",
		"Alt",
		"Pause",
		"Caps",
		"",
		"",
		"",
		"",
		"",
		"",
		"Escape",
		"",
		"",
		"",
		"",
		"Space",
		"Page Up",
		"Page Down",
		"End",
		"Home",
		"Left",
		"Up",
		"Right",
		"Down",
		"",
		"",
		"",
		"Print",
		"Insert",
		"Delete",
		"",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"",
		"",
		"",
		"",
		"",
		"Numpad 0",
		"Numpad 1",
		"Numpad 2",
		"Numpad 3",
		"Numpad 4",
		"Numpad 5",
		"Numpad 6",
		"Numpad 7",
		"Numpad 8",
		"Numpad 9",
		"Multiply",
		"Add",
		"",
		"Subtract",
		"Decimal",
		"Divide",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
	};

	BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
		char lpString[1024];
		sprintf(lpString, "%d", nInteger);
		return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
	}

	BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
		char lpString[1024];
		sprintf(lpString, "%f", nInteger);
		return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
	}

	float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
	{
		char szData[32];

		GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

		return (float)atof(szData);
	}

	void Save_Settings(LPCSTR path)
	{
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_playeresp"), visuals::box, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_boxstyle"), visuals::boxMode, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_health"), visuals::health, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_healthstyle"), visuals::healthMode, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_skeleton"), visuals::skel, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_crosshair"), visuals::crosshair, path);
		WritePrivateProfileFloat(XorString("Visuals"), XorString("m_crossize"), menu::crosshair_size, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_playername"), visuals::name, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_drawhead"), visuals::show_head, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_outline"), visuals::outline, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_snaplines"), visuals::lines, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_linemode"), visuals::lineMode, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_fontsize"), menu::font_size, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_boxthick"), menu::box_thick, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_itemhands"), visuals::wepnhands, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_showsleeping"), visuals::sleeping_player, path);
		WritePrivateProfileInt(XorString("Visuals"), XorString("m_playerlist"), menu::player_list, path);

		if (visuals::SavePosition1.x != 0 || visuals::SavePosition1.y != 0 || visuals::SavePosition1.z != 0) {
			WritePrivateProfileFloat(XorString("Positions"), XorString("m_save_pos1.x"), visuals::SavePosition1.x, path);
			WritePrivateProfileFloat(XorString("Positions"), XorString("m_save_pos1.y"), visuals::SavePosition1.y, path);
			WritePrivateProfileFloat(XorString("Positions"), XorString("m_save_pos1.z"), visuals::SavePosition1.z, path);
		}

		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_aimbot"), aimbot::aimbot, path);
		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_smooth"), aimbot::smooth, path);
		WritePrivateProfileFloat(XorString("Aimbot"), XorString("m_aimbotfov"), aimbot::aimfov, path);
		WritePrivateProfileFloat(XorString("Aimbot"), XorString("m_aimbotsmooth"), aimbot::aimspeed, path);
		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_fovcircle"), aimbot::fovcircle, path);
		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_aimkey"), hotkeys::aimkey, path);
		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_hitbox"), aimbot::hitbox, path);
		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_rcs"), aimbot::rcs, path);
		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_forceauto"), aimbot::forceauto, path);
		WritePrivateProfileInt(XorString("Aimbot"), XorString("m_prediction"), aimbot::prediction, path);

		WritePrivateProfileInt(XorString("Misc"), XorString("m_playerlist"), menu::player_list, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_overlayfps"), menu::overlay_fps, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_watermarker"), menu::watermark, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_norecoil"), misc::norecoil, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_nospread"), misc::nospread, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_nosway"), misc::nosway, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_fixeoka"), misc::notimeeoka, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_spiderman"), misc::peter_parker, path);
		WritePrivateProfileInt(XorString("Misc"), XorString("m_airstuckkey"), hotkeys::airstuckey, path);

		WritePrivateProfileInt(XorString("ItemOre"), XorString("m_showore"), visuals::show_ore, path);
		WritePrivateProfileInt(XorString("ItemOre"), XorString("m_ore_metal"), visuals::ore_metal, path);
		WritePrivateProfileInt(XorString("ItemOre"), XorString("m_ore_stone"), visuals::ore_stone, path);
		WritePrivateProfileInt(XorString("ItemOre"), XorString("m_ore_sulfur"), visuals::ore_sulfur, path);
		WritePrivateProfileInt(XorString("ItemOre"), XorString("m_droppeditems"), visuals::show_droppeditems, path);
		WritePrivateProfileInt(XorString("ItemOre"), XorString("m_scientists"), visuals::show_scientists, path);

		WritePrivateProfileInt(XorString("ItemCollectable"), XorString("m_showcollectable"), visuals::show_collectable, path);
		WritePrivateProfileInt(XorString("ItemCollectable"), XorString("m_coll_metal"), visuals::coll_metal, path);
		WritePrivateProfileInt(XorString("ItemCollectable"), XorString("m_coll_sulfur"), visuals::coll_sulfur, path);
		WritePrivateProfileInt(XorString("ItemCollectable"), XorString("m_coll_stone"), visuals::coll_stone, path);
		WritePrivateProfileInt(XorString("ItemCollectable"), XorString("m_coll_vegetables"), visuals::coll_vegetables, path);
		WritePrivateProfileInt(XorString("ItemCollectable"), XorString("m_coll_wood"), visuals::coll_wood, path);

		WritePrivateProfileInt(XorString("ItemCrates"), XorString("m_showcrates"), visuals::show_crates, path);
		WritePrivateProfileInt(XorString("ItemCrates"), XorString("m_crate_barrel"), visuals::crate_barrel, path);
		WritePrivateProfileInt(XorString("ItemCrates"), XorString("m_crate_military"), visuals::crate_military, path);
		WritePrivateProfileInt(XorString("ItemCrates"), XorString("m_crate_normal"), visuals::crate_normal, path);
		WritePrivateProfileInt(XorString("ItemCrates"), XorString("m_crate_elite"), visuals::crate_elite, path);
		WritePrivateProfileInt(XorString("ItemCrates"), XorString("m_crate_tools"), visuals::crate_tools, path);

		WritePrivateProfileFloat(XorString("Colors"), XorString("m_espr"), colors::espcol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_espg"), colors::espcol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_espb"), colors::espcol[2], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_skelr"), colors::skelcol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_skelg"), colors::skelcol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_skelb"), colors::skelcol[2], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_crossr"), colors::crosscol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_crossg"), colors::crosscol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_crossb"), colors::crosscol[2], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_crater"), colors::cratecol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_crateg"), colors::cratecol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_crateb"), colors::cratecol[2], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_collr"), colors::collcol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_collg"), colors::collcol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_collb"), colors::collcol[2], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_orer"), colors::orecol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_oreg"), colors::orecol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_oreb"), colors::orecol[2], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_itemsr"), colors::itemscol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_itemsg"), colors::itemscol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_itemsb"), colors::itemscol[2], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_scientistr"), colors::scientistcol[0], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_scientistg"), colors::scientistcol[1], path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_scientistb"), colors::scientistcol[2], path);
		WritePrivateProfileInt(XorString("Colors"), XorString("m_rainbow"), menu::rainbow_colors, path);
		WritePrivateProfileFloat(XorString("Colors"), XorString("m_rainbowspeed"), menu::rainbow_speed, path);

		WritePrivateProfileInt(XorString("Distance"), XorString("m_collactabledistance"), visuals::MaxCollectableDistance, path);
		WritePrivateProfileInt(XorString("Distance"), XorString("m_collactabledistance"), visuals::MaxOreDistance, path);
		WritePrivateProfileInt(XorString("Distance"), XorString("m_cratedistance"), visuals::MaxCrateDistance, path);
		WritePrivateProfileInt(XorString("Distance"), XorString("m_scientistdistance"), visuals::MaxScientistDistance, path);
		WritePrivateProfileInt(XorString("Distance"), XorString("m_esqueletoistance"), visuals::MaxSkeletonDrawDistance, path);
	}

	void Load_Settings(LPCSTR path)
	{
		visuals::box = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_playeresp"), visuals::box, path);
		visuals::health = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_health"), visuals::health, path);
		visuals::healthMode = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_healthstyle"), visuals::healthMode, path);
		visuals::boxMode = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_boxstyle"), visuals::boxMode, path);
		visuals::crosshair = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_crosshair"), visuals::crosshair, path);
		visuals::skel = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_skeleton"), visuals::skel, path);
		menu::crosshair_size = GetPrivateProfileFloat(XorString("Visuals"), XorString("m_crossize"), menu::crosshair_size, path);
		visuals::name = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_playername"), visuals::name, path);
		visuals::show_head = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_drawhead"), visuals::show_head, path);
		visuals::outline = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_outline"), visuals::outline, path);
		visuals::lines = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_snaplines"), visuals::lines, path);
		visuals::lineMode = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_linemode"), visuals::lineMode, path);
		menu::font_size = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_fontsize"), menu::font_size, path);
		menu::box_thick = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_boxthick"), menu::box_thick, path);
		visuals::wepnhands = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_itemhands"), visuals::wepnhands, path);
		visuals::sleeping_player = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_showsleeping"), visuals::sleeping_player, path);
		menu::player_list = GetPrivateProfileIntA(XorString("Visuals"), XorString("m_playerlist"), menu::player_list, path);

		visuals::SavePosition1.x = GetPrivateProfileFloat(XorString("Positions"), XorString("m_save_pos1.x"), visuals::SavePosition1.x, path);
		visuals::SavePosition1.y = GetPrivateProfileFloat(XorString("Positions"), XorString("m_save_pos1.y"), visuals::SavePosition1.y, path);
		visuals::SavePosition1.z = GetPrivateProfileFloat(XorString("Positions"), XorString("m_save_pos1.z"), visuals::SavePosition1.z, path);

		aimbot::aimbot = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_aimbot"), aimbot::aimbot, path);
		aimbot::smooth = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_smooth"), aimbot::smooth, path);
		aimbot::aimfov = GetPrivateProfileFloat(XorString("Aimbot"), XorString("m_aimbotfov"), aimbot::aimfov, path);
		aimbot::aimspeed = GetPrivateProfileFloat(XorString("Aimbot"), XorString("m_aimbotsmooth"), aimbot::aimspeed, path);
		aimbot::fovcircle = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_fovcircle"), aimbot::fovcircle, path);
		hotkeys::aimkey = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_aimkey"), hotkeys::aimkey, path);
		aimbot::hitbox = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_hitbox"), aimbot::hitbox, path);
		aimbot::rcs = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_rcs"), aimbot::rcs, path);
		aimbot::forceauto = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_forceauto"), aimbot::forceauto, path);
		aimbot::prediction = GetPrivateProfileIntA(XorString("Aimbot"), XorString("m_prediction"), aimbot::prediction, path);

		menu::player_list = GetPrivateProfileIntA(XorString("Misc"), XorString("m_playerlist"), menu::player_list, path);
		misc::overlayfps = GetPrivateProfileIntA(XorString("Misc"), XorString("m_overlayfps"), menu::overlay_fps, path);
		menu::watermark = GetPrivateProfileIntA(XorString("Misc"), XorString("m_watermarker"), menu::watermark, path);
		misc::norecoil = GetPrivateProfileIntA(XorString("Misc"), XorString("m_norecoil"), misc::norecoil, path);
		misc::nospread = GetPrivateProfileIntA(XorString("Misc"), XorString("m_nospread"), misc::nospread, path);
		misc::nosway = GetPrivateProfileIntA(XorString("Misc"), XorString("m_nosway"), misc::nosway, path);
		misc::notimeeoka = GetPrivateProfileIntA(XorString("Misc"), XorString("m_fixeoka"), misc::notimeeoka, path);
		misc::peter_parker = GetPrivateProfileIntA(XorString("Misc"), XorString("m_spiderman"), misc::peter_parker, path);
		hotkeys::airstuckey = GetPrivateProfileIntA(XorString("Misc"), XorString("m_airstuckkey"), hotkeys::airstuckey, path);

		visuals::show_ore = GetPrivateProfileIntA(XorString("ItemOre"), XorString("m_showore"), visuals::show_ore, path);
		visuals::ore_metal = GetPrivateProfileIntA(XorString("ItemOre"), XorString("m_ore_metal"), visuals::ore_metal, path);
		visuals::ore_stone = GetPrivateProfileIntA(XorString("ItemOre"), XorString("m_ore_stone"), visuals::ore_stone, path);
		visuals::ore_sulfur = GetPrivateProfileIntA(XorString("ItemOre"), XorString("m_ore_sulfur"), visuals::ore_sulfur, path);
		visuals::show_droppeditems = GetPrivateProfileIntA(XorString("ItemOre"), XorString("m_droppeditems"), visuals::show_droppeditems, path);
		visuals::show_scientists = GetPrivateProfileIntA(XorString("ItemOre"), XorString("m_scientists"), visuals::show_scientists, path);

		visuals::show_collectable = GetPrivateProfileIntA(XorString("ItemCollectable"), XorString("m_showcollectable"), visuals::show_collectable, path);
		visuals::coll_metal = GetPrivateProfileIntA(XorString("ItemCollectable"), XorString("m_coll_metal"), visuals::coll_metal, path);
		visuals::coll_sulfur = GetPrivateProfileIntA(XorString("ItemCollectable"), XorString("m_coll_sulfur"), visuals::coll_sulfur, path);
		visuals::coll_stone = GetPrivateProfileIntA(XorString("ItemCollectable"), XorString("m_coll_stone"), visuals::coll_stone, path);
		visuals::coll_vegetables = GetPrivateProfileIntA(XorString("ItemCollectable"), XorString("m_coll_vegetables"), visuals::coll_vegetables, path);
		visuals::coll_wood = GetPrivateProfileIntA(XorString("ItemCollectable"), XorString("m_coll_wood"), visuals::coll_wood, path);

		visuals::show_crates = GetPrivateProfileIntA(XorString("ItemCrates"), XorString("m_showcrates"), visuals::show_crates, path);
		visuals::crate_barrel = GetPrivateProfileIntA(XorString("ItemCrates"), XorString("m_crate_barrel"), visuals::crate_barrel, path);
		visuals::crate_military = GetPrivateProfileIntA(XorString("ItemCrates"), XorString("m_crate_military"), visuals::crate_military, path);
		visuals::crate_normal = GetPrivateProfileIntA(XorString("ItemCrates"), XorString("m_crate_normal"), visuals::crate_normal, path);
		visuals::crate_elite = GetPrivateProfileIntA(XorString("ItemCrates"), XorString("m_crate_elite"), visuals::crate_elite, path);
		visuals::crate_tools = GetPrivateProfileIntA(XorString("ItemCrates"), XorString("m_crate_tools"), visuals::crate_tools, path);

		colors::espcol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_espr"), colors::espcol[0], path);
		colors::espcol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_espg"), colors::espcol[1], path);
		colors::espcol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_espb"), colors::espcol[2], path);
		colors::skelcol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_skelr"), colors::skelcol[0], path);
		colors::skelcol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_skelg"), colors::skelcol[1], path);
		colors::skelcol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_skelb"), colors::skelcol[2], path);
		colors::crosscol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_crossr"), colors::crosscol[0], path);
		colors::crosscol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_crossg"), colors::crosscol[1], path);
		colors::crosscol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_crossb"), colors::crosscol[2], path);
		colors::cratecol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_crater"), colors::cratecol[0], path);
		colors::cratecol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_crateg"), colors::cratecol[1], path);
		colors::cratecol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_crateb"), colors::cratecol[2], path);
		colors::collcol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_collr"), colors::collcol[0], path);
		colors::collcol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_collg"), colors::collcol[1], path);
		colors::collcol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_collb"), colors::collcol[2], path);
		colors::orecol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_orer"), colors::orecol[0], path);
		colors::orecol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_oreg"), colors::orecol[1], path);
		colors::orecol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_oreb"), colors::orecol[2], path);
		colors::itemscol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_itemsr"), colors::itemscol[0], path);
		colors::itemscol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_itemsg"), colors::itemscol[1], path);
		colors::itemscol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_itemsb"), colors::itemscol[2], path);
		colors::scientistcol[0] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_scientistr"), colors::scientistcol[0], path);
		colors::scientistcol[1] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_scientistg"), colors::scientistcol[1], path);
		colors::scientistcol[2] = GetPrivateProfileFloat(XorString("Colors"), XorString("m_scientistb"), colors::scientistcol[2], path);

		visuals::MaxCollectableDistance = GetPrivateProfileIntA(XorString("Distance"), XorString("m_collactabledistance"), visuals::MaxCollectableDistance, path);
		visuals::MaxOreDistance = GetPrivateProfileIntA(XorString("Distance"), XorString("m_collactabledistance"), visuals::MaxOreDistance, path);
		visuals::MaxCrateDistance = GetPrivateProfileIntA(XorString("Distance"), XorString("m_cratedistance"), visuals::MaxCrateDistance, path);
		visuals::MaxScientistDistance = GetPrivateProfileIntA(XorString("Distance"), XorString("m_scientistdistance"), visuals::MaxScientistDistance, path);
		visuals::MaxSkeletonDrawDistance = GetPrivateProfileIntA(XorString("Distance"), XorString("m_esqueletoistance"), visuals::MaxSkeletonDrawDistance, path);

		menu::rainbow_colors = GetPrivateProfileIntA(XorString("Colors"), XorString("m_rainbow"), menu::rainbow_colors, path);
		menu::rainbow_speed = GetPrivateProfileFloat(XorString("Colors"), XorString("m_rainbowspeed"), menu::rainbow_speed, path);
	};
	
}