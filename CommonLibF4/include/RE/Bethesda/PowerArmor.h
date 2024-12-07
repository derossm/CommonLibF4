#pragma once

#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/Events.h"
#include "RE/Bethesda/HUDModes.h"

namespace RE
{
	namespace ExitPowerArmor
	{
		struct Event;
	}

	namespace PreloadPowerArmor
	{
		struct Event;
	}

	namespace PowerArmor
	{
		[[nodiscard]] inline bool ActorInPowerArmor(const Actor& a_actor)
		{
			using func_t = decltype(&ActorInPowerArmor);
			static REL::Relocation<func_t> func{ REL::ID(2219437) };
			return func(a_actor);
		}

		[[nodiscard]] inline bool PlayerInPowerArmor()
		{
			auto PlayerCharacter = PlayerCharacter::GetSingleton();
			return PlayerCharacter ? ActorInPowerArmor(*PlayerCharacter) : false;
		}

		[[nodiscard]] inline BGSKeyword* GetArmorKeyword()
		{
			using func_t = decltype(&GetArmorKeyword);
			static REL::Relocation<func_t> func{ REL::ID(961172) };
			return func();
		}

		[[nodiscard]] inline BGSKeyword* GetBatteryKeyword()
		{
			using func_t = decltype(&GetBatteryKeyword);
			static REL::Relocation<func_t> func{ REL::ID(1493537) };
			return func();
		}

		[[nodiscard]] inline TESAmmo* GetDefaultBatteryObject()
		{
			using func_t = decltype(&GetDefaultBatteryObject);
			static REL::Relocation<func_t> func{ REL::ID(1279247) };
			return func();
		}

		[[nodiscard]] inline bool IsPowerArmorBattery(const TESBoundObject* a_itemData)
		{
			using func_t = decltype(&IsPowerArmorBattery);
			static REL::Relocation<func_t> func{ REL::ID(1012910) };
			return func(a_itemData);
		}

		inline bool PlaySoundAtPlayer(BGSSoundDescriptorForm* a_soundDescriptor)
		{
			using func_t = decltype(&PlaySoundAtPlayer);
			REL::Relocation<func_t> func{ REL::ID(994664) };
			return func(a_soundDescriptor);
		}

		inline void SyncFurnitureVisualsToInventory(TESObjectREFR* a_furniture, bool a_force3DUpdate, BGSInventoryItem* a_tempItemToAdd, bool a_hideCore)
		{
			using func_t = decltype(&SyncFurnitureVisualsToInventory);
			static REL::Relocation<func_t> func{ REL::ID(1078979) };
			return func(a_furniture, a_force3DUpdate, a_tempItemToAdd, a_hideCore);
		}

		inline REL::Relocation<SettingT<GameSettingCollection>*> fNewBatteryCapacity{ REL::ID(1134204) };
	}

	class __declspec(novtable) PowerArmorGeometry :
		public SimpleAnimationGraphManagerHolder,       // 00
		public BSTEventSink<PreloadPowerArmor::Event>,  // 18
		public BSTEventSink<ExitPowerArmor::Event>,     // 20
		public BSIntrusiveRefCounted,                   // 28
		public BSTSingletonSDM<PowerArmorGeometry>      // 2C
	{
	public:
		static constexpr auto RTTI{ RTTI::PowerArmorGeometry };
		static constexpr auto VTABLE{ VTABLE::PowerArmorGeometry };

		virtual ~PowerArmorGeometry();  // 00

		// override
		virtual void                 BackgroundTaskFinishedLoading() override;                                                                            // 01
		virtual BSEventNotifyControl ProcessEvent(const PreloadPowerArmor::Event& a_event, BSTEventSource<PreloadPowerArmor::Event>* a_source) override;  // 02
		virtual BSEventNotifyControl ProcessEvent(const ExitPowerArmor::Event& a_event, BSTEventSource<ExitPowerArmor::Event>* a_source) override;        // 03

		[[nodiscard]] static PowerArmorGeometry* GetSingleton()
		{
			static REL::Relocation<PowerArmorGeometry**> singleton{ REL::ID(1365745) };
			return *singleton;
		}

		void HidePipboyPAGeometry()
		{
			using func_t = decltype(&PowerArmorGeometry::HidePipboyPAGeometry);
			static REL::Relocation<func_t> func{ REL::ID(976332) };
			return func(this);
		}

		void ShowPipboyPAGeometry()
		{
			using func_t = decltype(&PowerArmorGeometry::ShowPipboyPAGeometry);
			static REL::Relocation<func_t> func{ REL::ID(19066) };
			return func(this);
		}

		// members
		BSTValueEventSink<PipboyLightEvent>            pipboySpotLightEvent;        // 030
		BSTValueEventSink<PlayerAmmoCountEvent>        nextAmmoCount;               // 048
		BSTValueEventSink<PlayerWeaponReloadEvent>     playerReloaded;              // 068
		BSTValueEventSink<CurrentRadsDisplayMagnitude> radsCount;                   // 080
		BSTValueEventSink<CurrentRadsPercentOfLethal>  radsPercentOfLethal;         // 0A0
		BSTValueEventSink<CurrentRadiationSourceCount> radiationSourceCount;        // 0C0
		TESImageSpaceModifier*                         paPipboyEffect;              // 0E0
		NiPointer<NiNode>                              paDashDials;                 // 0E8
		NiPointer<NiNode>                              pipboyPAGlass;               // 0F0
		NiAVObject*                                    paDashLightSpot;             // 0F8
		NiAVObject*                                    paDashLightScope;            // 100
		NiAVObject*                                    paDashLightAux;              // 108
		NiAVObject*                                    paDash;                      // 110
		NiAVObject*                                    plane;                       // 118
		NiAVObject*                                    compass;                     // 120
		BSTArray<void*>                                queued3D;                    // 128
		HUDModes                                       validHUDModes;               // 140
		float                                          radiationSmoother;           // 160
		NiPointer<NiNode>                              dbHUDRain;                   // 168
		bool                                           hudRain;                     // 170
		bool                                           prevShouldBeVisible;         // 171
		bool                                           powerArmorEmergencyLightOn;  // 172
		bool                                           queueInit;                   // 173
		bool                                           prevIsFirstPerson;           // 174
		bool                                           ammoDirty;                   // 175
		bool                                           initialized;                 // 176
	};
	static_assert(sizeof(PowerArmorGeometry) == 0x178);
}
