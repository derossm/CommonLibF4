#pragma once

namespace RE
{
	enum class LOCK_LEVEL;

	enum class DIFFICULTY_LEVEL
	{
		kVeryEasy = 0x0,
		kLow = 0x0,
		kEasy = 0x1,
		kNormal = 0x2,
		kHard = 0x3,
		kVeryHard = 0x4,
		kSurvival = 0x5,
		kTrueSurvival = 0x6,
		kHigh = 0x6,
	};

	namespace GamePlayFormulas
	{
		enum class EXPERIENCE_ACTIVITY
		{
			kKillNPC = 0,
			kHackComputer = 1,
		};

		inline bool CanHackGateCheck(LOCK_LEVEL a_lockLevel)
		{
			using func_t = decltype(&GamePlayFormulas::CanHackGateCheck);
			static REL::Relocation<func_t> func{ REL::ID(269668) };
			return func(a_lockLevel);
		}

		inline bool CanPickLockGateCheck(LOCK_LEVEL a_lockLevel)
		{
			using func_t = decltype(&GamePlayFormulas::CanPickLockGateCheck);
			static REL::Relocation<func_t> func{ REL::ID(1160841) };
			return func(a_lockLevel);
		}

		inline float GetExperienceReward(EXPERIENCE_ACTIVITY a_activity, DIFFICULTY_LEVEL a_difficulty, float a_xpBase)
		{
			using func_t = decltype(&GamePlayFormulas::GetExperienceReward);
			static REL::Relocation<func_t> func{ REL::ID(853500) };
			return func(a_activity, a_difficulty, a_xpBase);
		}

		inline float GetLockXPReward(LOCK_LEVEL a_lockLevel)
		{
			using func_t = decltype(&GamePlayFormulas::GetLockXPReward);
			static REL::Relocation<func_t> func{ REL::ID(880926) };
			return func(a_lockLevel);
		}
	}
}
