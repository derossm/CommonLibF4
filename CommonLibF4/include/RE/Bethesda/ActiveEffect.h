#pragma once

#include "RE/Bethesda/BSSoundHandle.h"
#include "RE/Bethesda/ReferenceEffectController.h"
#include "RE/Bethesda/TESForms.h"

namespace RE
{
	class ActiveEffect;
	class EffectItem;
	class MagicItem;
	class MagicTarget;
	class ReferenceEffect;
	class TESForm;
	class TESObjectREFR;

	namespace MagicSystem
	{
		enum class CastingSource;
	}

	class __declspec(novtable) ActiveEffect :
		public BSIntrusiveRefCounted
	{
	public:
		static constexpr auto RTTI{ RTTI::ActiveEffect };
		static constexpr auto VTABLE{ VTABLE::ActiveEffect };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kActiveEffect };

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kNoHitShader = 1U << 1,
			kNoHitEffectArt = 1U << 2,
			kNoInitialFlare = 1U << 4,
			kApplyingHitEffects = 1U << 5,
			kApplyingSounds = 1U << 6,
			kHasConditions = 1U << 7,
			kRecover = 1U << 9,
			kDualCasted = 1U << 12,
			kInactive = 1U << 15,
			kAppliedEffects = 1U << 16,
			kRemovedEffects = 1U << 17,
			kDispelled = 1U << 18,
			kWornOff = 1U << 31
		};

		enum class ConditionStatus : std::uint32_t
		{
			kNotAvailable = static_cast<std::underlying_type_t<ConditionStatus>>(-1),
			kFalse = 0,
			kTrue = 1
		};

		virtual ~ActiveEffect();

		bool CheckDisplacementSpellOnTarget()
		{
			using func_t = decltype(&ActiveEffect::CheckDisplacementSpellOnTarget);
			static REL::Relocation<func_t> func{ REL::ID(1415178) };
			return func(this);
		}

		// members
		ActiveEffectReferenceEffectController                   hitEffectController;  // 0C
		BSSoundHandle                                           persistentSound;      // 30
		ActorHandle                                             caster;               // 38
		NiPointer<NiNode>                                       sourceNode;           // 40
		MagicItem*                                              spell;                // 48
		EffectItem*                                             effect;               // 50
		MagicTarget*                                            target;               // 58
		TESBoundObject*                                         source;               // 60
		BSSimpleList<ReferenceEffect*>*                         hitEffects;           // 68
		MagicItem*                                              displacementSpell;    // 70
		float                                                   elapsedSeconds;       // 74
		float                                                   duration;             // 78
		float                                                   magnitude;            // 7C
		REX::EnumSet<Flags, std::uint32_t>                      flags;                // 80
		REX::EnumSet<ConditionStatus, std::uint32_t>            conditionStatus;      // 84
		std::uint16_t                                           uniqueID;             // 8C
		REX::EnumSet<MagicSystem::CastingSource, std::uint32_t> castingSource;        // 90
	};
	static_assert(sizeof(ActiveEffect) == 0x98);
}
