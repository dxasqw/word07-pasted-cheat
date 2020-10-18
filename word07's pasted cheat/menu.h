	using namespace settings;

static const char* boxStyle[] =
{
	"2D",
	"2D Filled",
	"2D Corner",
	"2D Corner Filled",
	"3D Box"
};

static const char* Hitbox[] =
{
	"Head",
	"Neck",
	"Chest",
	"Stomach",
	"Pelvis"
};

static const char* settsName[] =
{
	"Default",
	"Config 1",
	"Config 2"
};

static const char* healthMode[] =
{
	"Left Bar",
	"Right Bar",
	"Numbers",
	"Lbar + Numbers",
	"Rbar + Numbers",
	"Bottom Bar"
};

static const char* linesMode[] =
{
	"Bottom",
	"Top",
	"Crosshair",
	"Aim Fov"
};

static const char* weaponsMode[] =
{
	"All",
	"Rifles",
	"Snipers",
	"Pistols",
	"Shotguns",
	"SMGs",
	"LMGs",
	"Bows"
};

static int keystatus = 0;
static int realkey = 0;
bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}
void ChangeKey2(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::airstuckey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

bool draw_abigsquare()
{
	static int MenuTab = 0;
	static int VisualTab = 0;
	float
		TextSpaceLine = 90.f,
		SpaceLineOne = 120.f,
		SpaceLineTwo = 280.f,
		SpaceLineThr = 420.f;
	ImGuiStyle* style = &ImGui::GetStyle();
	aimbot::selected_weapon = GetLocalSelectedWeapon();

	static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin(XorString("Rust"), NULL, flags);
	{
		ImGui::SetWindowSize(ImVec2(590, 315), ImGuiCond_Once);
		{
			ImGui::BeginChild(XorString("##Tabs"), ImVec2(-1, 30.0f));
			{
				style->ItemSpacing = ImVec2(1, 1);
				ImGui::PushFont(menu::SkeetFont);
				{
					if (ImGui::Button((XorString("! Aimbot")), ImVec2(185, 20)))
					{
						MenuTab = 0;
					}ImGui::SameLine();
					if (ImGui::Button((XorString("$ Visuals")), ImVec2(185, 20)))
					{
						MenuTab = 1;
					}ImGui::SameLine();
					if (ImGui::Button((XorString("% Misc")), ImVec2(185, 20)))
					{
						MenuTab = 2;
					}ImGui::SameLine();
				} ImGui::PopFont();

			} ImGui::EndChild();

			style->ItemSpacing = ImVec2(8, 8);

			if (MenuTab == 0)
			{
				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Text(XorString("Aimbot:"));
				ImGui::SetCursorPos(ImVec2(10, 70));
				ImGui::BeginChild(XorString("##Aimbot"), ImVec2(130.f, 200.f), true);
				{
					ImGui::Checkbox(XorString("Aimbot"), &aimbot::aimbot);
					ImGui::Checkbox(XorString("Smooth"), &aimbot::smooth);
					ImGui::Checkbox(XorString("Show FOV"), &aimbot::fovcircle);
					ImGui::Checkbox(XorString("RCS"), &aimbot::rcs);
					ImGui::Checkbox(XorString("Force Auto"), &aimbot::forceauto);
					ImGui::Checkbox(XorString("Prediction"), &aimbot::prediction);
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(150, 50));
				ImGui::Text(XorString("Settings:"));
				ImGui::SetCursorPos(ImVec2(150, 70));
				ImGui::BeginChild(XorString("##Aimbot2"), ImVec2(-1.f, 200.f), true);
				{
					ImGui::PushItemWidth(200.f);
					ImGui::Text(XorString("Select Weapon: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::Combo(XorString("##selectwep"), &aimbot::selected_weapon, weaponsMode, IM_ARRAYSIZE(weaponsMode));
					ImGui::PopItemWidth();

					ImGui::PushItemWidth(270.f);
					ImGui::Text(XorString("FOV: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::SliderFloatPreciseV2("##fovkrai", &aimbot::aimfov, 1.f, 50.f, "%.2f");

					ImGui::Text(XorString("Smooth: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::SliderFloatPreciseV2(XorString("##smoothkrai"), &aimbot::aimspeed, 1.f, 25.f, "%.2f");

					ImGui::PopItemWidth();

					ImGui::Text(XorString("Aim Key: ")); ImGui::SameLine(SpaceLineOne);
					HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);

					ImGui::PushItemWidth(200.f);
					ImGui::Text(XorString("Hitbox: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::Combo(XorString("##BONES"), &settings::aimbot::hitbox, Hitbox, IM_ARRAYSIZE(Hitbox));
					ImGui::PopItemWidth();
				}
				ImGui::EndChild();
			}
			else if (MenuTab == 1)
			{

				if (ImGui::Button((XorString("Players")), ImVec2(185, 20)))
				{
					VisualTab = 0;
				}ImGui::SameLine();
				if (ImGui::Button((XorString("Items")), ImVec2(185, 20)))
				{
					VisualTab = 1;
				}

				if (VisualTab == 1)
				{
					ImGui::SetCursorPos(ImVec2(10, 80));
					ImGui::Text(XorString("Ore and Others ESP:"));
					ImGui::SetCursorPos(ImVec2(10, 100));
					ImGui::BeginChild(XorString("##ORES"), ImVec2(190.f, 175.f), true);
					{
						ImGui::Checkbox(XorString("Show Ore"), &visuals::show_ore);
						ImGui::Checkbox(XorString("Metal"), &visuals::ore_metal);
						ImGui::Checkbox(XorString("Stone"), &visuals::ore_stone);
						ImGui::Checkbox(XorString("Sulfur"), &visuals::ore_sulfur);
						ImGui::Checkbox(XorString("Dropped Items"), &visuals::show_droppeditems);
						ImGui::Checkbox(XorString("Scientist NPC"), &visuals::show_scientists);
					}
					ImGui::EndChild();

					ImGui::SetCursorPos(ImVec2(210, 80));
					ImGui::Text(XorString("Collectables:"));
					ImGui::SetCursorPos(ImVec2(210, 100));
					ImGui::BeginChild(XorString("##COLLECT"), ImVec2(190.f, 175.f), true);
					{
						ImGui::Checkbox(XorString("Show Collectables"), &visuals::show_collectable);
						ImGui::Checkbox(XorString("Vegetables"), &visuals::coll_vegetables);
						ImGui::Checkbox(XorString("Wood"), &visuals::coll_wood);
						ImGui::Checkbox(XorString("Metal"), &visuals::coll_metal);
						ImGui::Checkbox(XorString("Stone"), &visuals::coll_stone);
						ImGui::Checkbox(XorString("Sulfur"), &visuals::coll_sulfur);
					}
					ImGui::EndChild();

					ImGui::SetCursorPos(ImVec2(410, 80));
					ImGui::Text(XorString("Crates:"));
					ImGui::SetCursorPos(ImVec2(410, 100));
					ImGui::BeginChild(XorString("##CRATES"), ImVec2(-1.f, 175.f), true);
					{
						ImGui::Checkbox(XorString("Show Crates"), &visuals::show_crates);
						ImGui::Checkbox(XorString("Military"), &visuals::crate_military);
						ImGui::Checkbox(XorString("Normal"), &visuals::crate_normal);
						ImGui::Checkbox(XorString("Elite"), &visuals::crate_elite);
						ImGui::Checkbox(XorString("Tools"), &visuals::crate_tools);
						ImGui::Checkbox(XorString("Barrel"), &visuals::crate_barrel);
					}
					ImGui::EndChild();
				}

				if (VisualTab == 0)
				{
					ImGui::SetCursorPos(ImVec2(10, 80));
					ImGui::Text(XorString("Player ESP:"));
					ImGui::SetCursorPos(ImVec2(10, 100));
					ImGui::BeginChild(XorString("##Players1"), ImVec2(240.f, 175.f), true);
					{
						ImGui::Checkbox(XorString("Show Box"), &visuals::box);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(XorString("Show Skeleton"), &visuals::skel);

						ImGui::Checkbox(XorString("Show Name"), &visuals::name);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(XorString("Show Head"), &visuals::show_head);

						ImGui::Checkbox(XorString("Show Health"), &visuals::health);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(XorString("Show Lines"), &visuals::lines);

						ImGui::Checkbox(XorString("Show Item"), &visuals::wepnhands);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(XorString("Show Sleeping"), &visuals::sleeping_player);

						ImGui::Checkbox(XorString("Crosshair"), &visuals::crosshair);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(XorString("Rainbow"), &menu::rainbow_colors);
					}
					ImGui::EndChild();
					ImGui::SetCursorPos(ImVec2(260, 80));
					ImGui::Text(XorString("Styles:"));
					ImGui::SetCursorPos(ImVec2(260, 100));
					ImGui::BeginChild(XorString("##Players22"), ImVec2(-1, 175.f), true);
					{
						ImGui::PushItemWidth(170.f);
						ImGui::Text(XorString("Box Style")); ImGui::SameLine(100.f);
						ImGui::Combo(XorString("##BOXSTYLES"), &visuals::boxMode, boxStyle, IM_ARRAYSIZE(boxStyle));
						ImGui::Text("Health Style"); ImGui::SameLine(100.f);
						ImGui::Combo(XorString("##HEALTHSTYLE"), &visuals::healthMode, healthMode, IM_ARRAYSIZE(healthMode));
						ImGui::Text("Lines Style"); 	ImGui::SameLine(100.f);
						ImGui::Combo(XorString("##LINESSTYLE"), &visuals::lineMode, linesMode, IM_ARRAYSIZE(linesMode));

						ImGui::Text(XorString("Font Size: ")); ImGui::SameLine(TextSpaceLine);
						ImGui::SliderIntPrecise(XorString("##FontSize"), &menu::font_size, 10.f, 15.f);
						ImGui::Text(XorString("Box Thick: ")); ImGui::SameLine(TextSpaceLine);
						ImGui::SliderIntPrecise(XorString("##BoxThick"), &menu::box_thick, 1.f, 3.f);
						ImGui::Text(XorString("Crosshair Size:")); ImGui::SameLine(SpaceLineOne);
						ImGui::SliderFloatPreciseV2(XorString("##cross"), &menu::crosshair_size, 1.f, 100.f, "%.2f");
						ImGui::PopItemWidth();

					}ImGui::EndChild();
				}
			}

			else if (MenuTab == 2)
			{
				//ImGui::SetCursorPos(ImVec2(100, 42));
				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Text(XorString("Risky Features:"));
				ImGui::SetCursorPos(ImVec2(10, 70));
				ImGui::BeginChild(XorString("##Misc1"), ImVec2(240.f, 200.f), true);
				{
					ImGui::Checkbox(XorString("No Recoil"), &misc::norecoil);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(XorString("No Spread"), &misc::nospread);

					ImGui::Checkbox(XorString("No Sway"), &misc::nosway);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(XorString("Fix EOKA"), &misc::notimeeoka);

					ImGui::Checkbox(XorString("Spider Man"), &misc::peter_parker);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(XorString("Admin Flag"), &misc::admin_flag);

					ImGui::Checkbox(XorString("Players List"), &menu::player_list);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(XorString("Outline"), &visuals::outline);

					ImGui::Checkbox(XorString("Overlay FPS"), &menu::overlay_fps);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(XorString("Watermarker"), &menu::watermark);

					ImGui::Checkbox(XorString("Lock at 60 fps (CPU Save)"), &menu::limit60);

					if (ImGui::Button(XorString("Save Current Pos 1"), ImVec2(100, 25)))
					{
						visuals::SavePosition1 = visuals::CurrentPosition;
						settings::Save_Settings(XorString("C:\\Rust-Default.ini"));
					}
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(260, 50));
				ImGui::Text(XorString("Colors:"));
				ImGui::SetCursorPos(ImVec2(260, 70));

				ImGui::BeginChild(XorString("##Misc2"), ImVec2(-1.f, 200.f), true);
				{
					ImGui::PushItemWidth(170.f);
					ImGui::Text(XorString("Crosshair: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##cross"), colors::crosscol);

					ImGui::Text(XorString("ESP: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##esp"), colors::espcol);

					ImGui::Text(XorString("Skeleton: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##skels"), colors::skelcol);

					ImGui::Text(XorString("Crates: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##CRATESCOL"), colors::cratecol);

					ImGui::Text(XorString("Collectables: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##COLLCOL"), colors::collcol);

					ImGui::Text(XorString("Ore: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##ORECOL"), colors::orecol);

					ImGui::Text(XorString("Scientist: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##SCICOL"), colors::scientistcol);

					ImGui::Text(XorString("Items: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(XorString("##ITEMSCOL"), colors::itemscol);


					ImGui::Text(XorString("Collect Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderIntPrecise(XorString("##rainc2olors"), &visuals::MaxCollectableDistance, 0, 2000);

					ImGui::Text(XorString("Crate Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderIntPrecise(XorString("##raincolor1s"), &visuals::MaxCrateDistance, 0, 2000);

					ImGui::Text(XorString("Ore Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderIntPrecise(XorString("##raincolawor1s"), &visuals::MaxOreDistance, 0, 2000);

					ImGui::Text(XorString("Scientist Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderIntPrecise(XorString("##rainco213lawor121s"), &visuals::MaxScientistDistance, 0, 2000);

					ImGui::Text(XorString("Skeleton Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderIntPrecise(XorString("##rai2131wor1s"), &visuals::MaxSkeletonDrawDistance, 0, 300);


					ImGui::Text(XorString("Rainbow Speed: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::SliderFloatPreciseV2(XorString("##raincolors"), &rainbow_speed, 0.1f, 1.0f, "%.2f");
					ImGui::PopItemWidth();

					ImGui::PushItemWidth(120.f);
					ImGui::Text(XorString("AirStruck Key: ")); ImGui::SameLine(120.f);
					HotkeyButton(hotkeys::airstuckey, ChangeKey2, keystatus);
					ImGui::PopItemWidth();
				}
				ImGui::EndChild();
			}

			//ImGui::SetCursorPos(ImVec2(100, 42));
			ImGui::BeginChild(XorString("##Setts"), ImVec2(-1, 30.f));
			{

				ImGui::PushItemWidth(100.f);
				ImGui::Text(XorString("Config: ")); ImGui::SameLine(60.f); ImGui::Combo(XorString("##settsas"), &menu::settsMode, settsName, IM_ARRAYSIZE(settsName));

				ImGui::SameLine(170.f);

				if (ImGui::Button((XorString("Save")), ImVec2(100, 20)))
				{
					if (menu::settsMode == 0)
						settings::Save_Settings(XorString("C:\\Rust-Default.ini"));
					if (menu::settsMode == 1)
						settings::Save_Settings(XorString("C:\\Rust-Setts1.ini"));
					if (menu::settsMode == 2)
						settings::Save_Settings(XorString("C:\\Rust-Setts2.ini"));
				}

				ImGui::SameLine(280.f);
				if (ImGui::Button((XorString("Load")), ImVec2(100, 20)))
				{
					if (menu::settsMode == 0)
						settings::Load_Settings(XorString("C:\\Rust-Default.ini"));
					if (menu::settsMode == 1)
						settings::Load_Settings(XorString("C:\\Rust-Setts1.ini"));
					if (menu::settsMode == 2)
						settings::Load_Settings(XorString("C:\\Rust-Setts2.ini"));
				}
				ImGui::PopItemWidth();
			}ImGui::EndChild();
		}
		ImGui::End();
	}
	return true;
}


void shortcurts()
{
	if (GetAsyncKeyState(VK_INSERT))
	{
		if (menu::menu_key == false)
		{
			menu::menu_key = true;
		}
		else if (menu::menu_key == true)
		{
			menu::menu_key = false;
		}
		Sleep(200);
	}

	if (GetAsyncKeyState(VK_F6))
	{
		if (settings::items::enable_items == false) 
		{
			settings::items::enable_items = true;
		}
		else if (settings::items::enable_items == true) 
		{
			settings::items::enable_items = false;
		}
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_F7))
	{
		if (settings::misc::removegrass == false)
		{
			settings::misc::removegrass = true;
		}
		else if (settings::misc::removegrass == true)
		{
			settings::misc::removegrass = false;
		}
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_F8))
	{
		if (settings::misc::speedhack == false)
		{
			settings::misc::speedhack = true;
		}
		else if (settings::misc::speedhack == true)
		{
			settings::misc::speedhack = false;
		}
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_F9))
	{
		if (settings::misc::superjump == false)
		{
			settings::misc::superjump = true;
		}
		else if (settings::misc::superjump == true)
		{
			settings::misc::superjump = false;
		}
		Sleep(150);
	}
}

static void crosshair_draw()
{
	RGBA crosscolor = { colors::crosscol[0] * 255, colors::crosscol[1] * 255, colors::crosscol[2] * 255, 255 };

	if (menu::rainbow_colors)
		crosscolor = Col.rainbow();

	if (visuals::crosshair) {
		DrawLine((Width / 2) - menu::crosshair_size, (Height / 2), (Width / 2) + (menu::crosshair_size + 1), (Height / 2), &crosscolor, 2.0f);
		DrawLine((Width / 2), (Height / 2) - menu::crosshair_size, (Width / 2), (Height / 2) + (menu::crosshair_size + 1), &crosscolor, 2.0f);
	}

	if (aimbot::fovcircle) {
		DrawCircle(Width / 2, Height / 2, aimbot::aimfov * 8, &crosscolor, 100);
	}
}