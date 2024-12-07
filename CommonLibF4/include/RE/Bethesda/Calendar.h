#pragma once

#include "RE/Bethesda/BSTSingleton.h"

namespace RE
{
	class TESGlobal;

	class Calendar :
		public BSTSingletonSDM<Calendar>
	{
	public:
		struct Months
		{
			enum Month
			{
				kJanuary,
				kFebruary,
				kMarch,
				kApril,
				kMay,
				kJune,
				kJuly,
				kAugust,
				kSeptember,
				kOctober,
				kNovember,
				kDecember,
				kTotal
			};
		};
		using Month = Months::Month;

		[[nodiscard]] static Calendar* GetSingleton()
		{
			static REL::Relocation<Calendar**> singleton{ REL::ID(2689092) };
			return *singleton;
		}

		[[nodiscard]] float         GetHoursPassed() const noexcept;
		[[nodiscard]] std::uint32_t GetMonth() const noexcept;

		int64_t GetDaysPassed()
		{
			using func_t = decltype(&Calendar::GetDaysPassed);
			REL::Relocation<func_t> func{ REL::ID(1209930) };
			return func(this);
		}

		// members
		TESGlobal*    gameYear;         // 08
		TESGlobal*    gameMonth;        // 10
		TESGlobal*    gameDay;          // 18
		TESGlobal*    gameHour;         // 20
		TESGlobal*    gameDaysPassed;   // 28
		TESGlobal*    timeScale;        // 30
		std::uint32_t midnightsPassed;  // 38
		float         rawDaysPassed;    // 3C
	};
	static_assert(sizeof(Calendar) == 0x40);
}
