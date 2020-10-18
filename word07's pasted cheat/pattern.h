namespace process
{
	std::uintptr_t find_signature(const std::uintptr_t base_address, const char* sig, const char* mask)
	{
		const auto buffer = std::make_unique<std::array<std::uint8_t, 0x100000>>();
		auto data = buffer.get()->data();
		std::uintptr_t result = 0;

		for (std::uintptr_t i = 0u; i < (2u << 25u); ++i)
		{
			readto(base_address + i * 0x100000, data, 0x100000);

			if (!data)
				return 0;

			for (std::uintptr_t j = 0; j < 0x100000u; ++j)
			{
				if ([](std::uint8_t const* data, std::uint8_t const* sig, char const* mask)
					{
						for (; *mask; ++mask, ++data, ++sig)
						{
							if (*mask == 'x' && *data != *sig) return false;
						}
						return (*mask) == 0;
					}(data + j, (std::uint8_t*)sig, mask))
				{
					result = base_address + i * 0x100000 + j;

					std::uint32_t rel = 0;

					readto(result + 3, &rel, sizeof(std::uint32_t));

					if (!rel)
						return 0;

					return result - base_address + rel + 7;
				}
			}
		}
	}

}


//namespace Initialize
//{
//	uint64_t profile_manager = 0;
//	uint64_t round_manager = 0;
//	DWORD_PTR view_matrix = 0;
//	bool initialize()
//	{
//		profile_manager = process::pattern_scan("48 8B 0D ? ? ? ? E8 ? ? ? ? 80 BF ? ? ? ? ?", 3, 7);
//
//		if (!profile_manager)
//		{
//			std::cout << "[!] profile manager is outdated\n";
//			return false;
//		}
//
//		std::cout << "[+] profile manager: 0x" << std::hex << profile_manager << '\n';
//
//		round_manager = process::pattern_scan("F3 0F 10 05 ? ? ? ? 48 8D 54 24 ? F3 0F 59 C7 ", 4, 8);
//
//		if (!round_manager)
//		{
//			std::cout << "[!] round manager is outdated\n";
//			return false;
//		}
//
//		std::cout << "[+] round manager: 0x" << std::hex << round_manager << '\n';
//
//		//printf("round -> %d\n", game_state);
//
//		return true;
//	}
//}

