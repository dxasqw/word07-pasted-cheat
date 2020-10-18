#define M_PI                       3.14159265358979323846f
#define URotationToRadians(URotation)        ((URotation)* (M_PI / 32768.0f))
#define URotationToDegree( URotation )        ( ( URotation ) * ( 360.0f / 65536.0f ) ) 
#define DegreeToURotation( Degree )            ( ( Degree ) * ( 65536.0f / 360.0f ) )
#define DegreeToRadian( Degree )            ( ( Degree ) * ( M_PI / 180.0f ) 
#define RadianToURotation( URotation )        ( ( URotation ) * ( 32768.0f / M_PI ) ) 
#define RadianToDegree( Radian )            ( ( Radian ) * ( 180.0f / M_PI ) )
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))

using namespace offsets;
namespace math
{
	inline float dot(D3DXVECTOR3 a, D3DXVECTOR3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline float GetLength(glm::vec3 a) {
		return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	__forceinline glm::vec2 CalcAngle(const glm::vec3& Src, const glm::vec3& Dst) {
		glm::vec3 dir = Src - Dst;
		float length = GetLength(dir);
		return glm::vec2{ RAD2DEG(asin(dir.y / length)), RAD2DEG(-atan2(dir.x, -dir.z)) };
	}

	void Normalize(float& Yaw, float& Pitch) {
		if (Pitch < -89) Pitch = -89;
		else if (Pitch > 89) Pitch = 89;
		if (Yaw < -360) Yaw += 360;
		else if (Yaw > 360) Yaw -= 360;
	}

	glm::vec2 ClampAngles(glm::vec2 vec)
	{
		if (vec.x > 89.0f && vec.x <= 180.0f)
		{
			vec.x = 89.0f;
		}
		while (vec.x > 180.f)
		{
			vec.x -= 360.f;
		}
		while (vec.x < -89.0f)
		{
			vec.x = -89.0f;
		}
		while (vec.y > 180.f)
		{
			vec.y -= 360.f;
		}
		while (vec.y < -180.f)
		{
			vec.y += 360.f;
		}
		return vec;
	}

	glm::vec2 ClampAngle(glm::vec2 qaAng)
	{
		if (qaAng.x > 89.0f)
			qaAng.x = 89.0f;
		if (qaAng.x < -89.0f)
			qaAng.x = -89.0f;
		while (qaAng.y > 180.0f)
			qaAng.y -= 360.0f;
		while (qaAng.y < -180.0f)
			qaAng.y += 360.0f;
		return qaAng;
	}

	namespace aim
	{
		int select_hitbox()
		{
			int hitbox = 0;

			if (settings::aimbot::hitbox == 0)
				hitbox = BoneList::head; //head
			else if (settings::aimbot::hitbox == 1)
				hitbox = BoneList::neck; //neck
			else if (settings::aimbot::hitbox == 2)
				hitbox = BoneList::pelvis; //chest
			else if (settings::aimbot::hitbox == 3)
				hitbox = BoneList::penis;
			else if (settings::aimbot::hitbox == 4)
				hitbox = BoneList::pelvis;

			return hitbox;
		}

		glm::vec3 IsPrediction(uintptr_t player, int bone)
		{
			auto base_player = get_base_player(player);
			uintptr_t PlayerModel = read<uintptr_t>(base_player + base_player::OffsetPlayerModel); //public PlayerModel playerModel;
			glm::vec3 vel = read<glm::vec3>(PlayerModel + model_player::OffsetPlayerVelocity);

			glm::vec3 Bone = get_bone_position(player, bone);
			const int distance = (int)ceil(glm::distance(get_obj_pos(player), get_obj_pos(local::local_player)));

			if (distance > 0.001f) {

				float BulletTime = distance / GetBulletSpeed(local::local_player);
				glm::vec3 predict = vel * BulletTime * 0.75f;
				Bone += predict; Bone.y += (4.905f * BulletTime * BulletTime);
			}
			return Bone;
		}

		float ScreenToEnemy(glm::vec3 position)
		{
			glm::vec2 out;
			world_to_screen(position, &out);
			return (fabs(out.x - (Width / 2)) + fabs(out.y - (Height / 2)));
		}

		bool GetKey()
		{
			return (GetAsyncKeyState(hotkeys::aimkey));
		}
		
		bool isAimboting = false;
		uintptr_t GetNearestPlayer()
		{
			uintptr_t resultant_entity;
			float bestFov = settings::aimbot::aimfov * 8;

			const auto first_tagged_object = read<uintptr_t>(game_object_manager + 0x8);

			if (!first_tagged_object)
				return false;

			const auto object_entry = read<uintptr_t>(first_tagged_object + 0x10);

			if (!object_entry)
				return false;

			const auto object_instance = read<uintptr_t>(object_entry + 0x30);

			if (!object_instance)
				return false;

			const auto unk1 = read<uintptr_t>(base_networkable + 0xb8);

			if (!unk1)
				return false;

			const auto client_entities = read<uintptr_t>(unk1);

			if (!client_entities)
				return false;

			const auto entity_realm = read<uintptr_t>(client_entities + 0x10);

			if (!entity_realm)
				return false;

			const auto buffer_list = read<uintptr_t>(entity_realm + 0x28);

			if (!buffer_list)
				return false;

			const auto object_list = read<uintptr_t>(buffer_list + 0x18);

			if (!object_list)
				return false;

			const auto object_list_size = read<std::uint32_t>(buffer_list + 0x10);

			for (auto i = 0u; i < object_list_size; i++)
			{

				const auto current_object = read<uintptr_t>(object_list + (0x20 + (i * 8)));

				if (!current_object)
					continue;

				const auto object_name = get_class_name(current_object);

				if (object_name == "")
					continue;

				if (strstr(object_name.c_str(), XorString("BasePlayer")) || (strstr(object_name.c_str(), XorString("Scientist")))) {

					const auto unk1 = read<uintptr_t>(current_object + 0x10);

					if (!unk1)
						continue;

					const auto unk2 = read<uintptr_t>(unk1 + 0x30);

					if (!unk2)
						continue;

					const auto player = read<uintptr_t>(unk2 + 0x30);

					if (!player)
						continue;

					const auto player_health = get_player_health(player);
					const auto player_sleeping = get_player_sleeping(player);

					if (player_health <= 0) continue;
					if (player_sleeping) continue;

					glm::vec3 AimPos;
					if (aimbot::prediction == true)
						AimPos = IsPrediction(player, select_hitbox());
					else if (aimbot::prediction == false)
						AimPos = get_bone_position(player, select_hitbox());

					float fov = ScreenToEnemy(AimPos);

					if (fov < bestFov)
					{
						bestFov = fov;
						resultant_entity = player;
					}

				}
			}

			return resultant_entity;
		}

		uintptr_t resultant_entity;
		void ValidTarget()
		{
			resultant_entity = GetNearestPlayer();

			if (resultant_entity)
			{
				const auto player_health = get_player_health(resultant_entity);
				const auto player_sleeping = get_player_sleeping(resultant_entity);

				if (player_health <= 0)
				{
					resultant_entity = NULL;
					return;
				}
				if (player_sleeping)
					resultant_entity = NULL;

				glm::vec3 AimPos;

				if (aimbot::prediction == true)
					AimPos = IsPrediction(resultant_entity, select_hitbox());
				else if (aimbot::prediction == false)
					AimPos = get_bone_position(resultant_entity, select_hitbox());

				float fov = ScreenToEnemy(AimPos);

				if (fov > settings::aimbot::aimfov * 8)
					resultant_entity = NULL;
			}
			else
			{
				resultant_entity = NULL;
			}
		}

		void AimbotLoop()
		{
			if (!settings::aimbot::aimbot)
				return;

			ValidTarget();

			if (resultant_entity)
			{
				glm::vec3 AimPos;

				if (aimbot::prediction == true)
					AimPos = IsPrediction(resultant_entity, select_hitbox());
				else if (aimbot::prediction == false)
					AimPos = get_bone_position(resultant_entity, select_hitbox());

				auto LocalPos = get_bone_position(local::local_player, select_hitbox());
				glm::vec2 aim_screen;

				const auto Input = GetPlayerInput(get_base_player(local::local_player));
				glm::vec2 current_angle = GetViewAngles(Input);
				glm::vec2 RecoilAngle = GetRecoilAngle(Input);

				if (GetAsyncKeyState(hotkeys::aimkey) & 0x8000)
				{
					glm::vec2 angle = CalcAngle(LocalPos, AimPos) - GetViewAngles(Input);
					glm::vec2 FinalAngle = GetViewAngles(Input) + angle;
					ClampAngles(FinalAngle);
					ClampAngles(RecoilAngle);

					if (aimbot::rcs) {
						FinalAngle.x -= RecoilAngle.x;
						FinalAngle.y -= RecoilAngle.y;
					}

					if (aimbot::smooth) {
						glm::vec2 delta = ClampAngle(FinalAngle - current_angle);
						ClampAngles(delta);
						FinalAngle.x = current_angle.x += delta.x / aimbot::aimspeed;
						FinalAngle.y = current_angle.y += delta.y / aimbot::aimspeed;
						FinalAngle = ClampAngles(FinalAngle);
					}

					Normalize(FinalAngle.y, FinalAngle.x);
					SetViewAngles(Input, FinalAngle);
				}
			}
		}

	}
}