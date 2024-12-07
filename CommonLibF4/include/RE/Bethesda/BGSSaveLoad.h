#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSThread.h"
#include "RE/Bethesda/Events.h"

namespace RE
{
	namespace BSSaveDataSystemUtility
	{
		enum class RESULT;
	}

	class BGSSaveLoadFile;
	class BSEventFlag;
	class BSSaveDataSystemUtilityFile;

	struct BGSNumericIDIndex
	{
	public:
		~BGSNumericIDIndex() noexcept {}  // intentional

		enum class Flags : std::uint8_t
		{
			kDefault = 1u << 6,  // idx 0x00
			kCreated = 1u << 7,  // idx 0xFF
		};

		[[nodiscard]] bool IsCreated() const noexcept { return flags.all(Flags::kCreated); }
		[[nodiscard]] bool IsDefault() const noexcept { return flags.all(Flags::kDefault); }

		// members
		union
		{
			struct
			{
				union
				{
					std::uint8_t                      data1;
					REX::EnumSet<Flags, std::uint8_t> flags;
				};                   // 0
				std::uint8_t data2;  // 1
				std::uint8_t data3;  // 2
			};
			std::uint8_t data[3]{ 0 };
		};  // 0
	};
	static_assert(sizeof(BGSNumericIDIndex) == 0x3);

	class alignas(0x80) BGSSaveLoadThread :
		public BSThread  // 00
	{
	public:
		struct AsyncRequest
		{
		public:
			using TaskFinishedCallback_t = void (*)(bool);

			// members
			std::uint32_t          taskTypeID;            // 00
			BGSSaveLoadFile*       savefile;              // 08
			TaskFinishedCallback_t taskFinishedCallback;  // 10
			BSFixedString          previousSaveToDelete;  // 18
		};
		static_assert(sizeof(AsyncRequest) == 0x20);

		virtual ~BGSSaveLoadThread();  // 00

		// members
		bool        running;   // 50
		bool        busy;      // 51
		BSEventFlag haveTask;  // 58
		// BSTCommonStaticMessageQueue<AsyncRequest, 8> asyncSaveLoadOperationQueue;  // 80
		std::byte pad80[0x780 - 0x80];
	};
	static_assert(sizeof(BGSSaveLoadThread) == 0x780);

	class BSSaveDataSystemUtilityImage
	{
	public:
		// members
		std::uint32_t size;    // 00
		std::uint32_t width;   // 04
		std::uint32_t height;  // 08
		char*         buffer;  // 10
	};
	static_assert(sizeof(BSSaveDataSystemUtilityImage) == 0x18);

	class SavefileMetadata
	{
	public:
		void FillDataFromFileName(char* a_fileName)
		{
			using func_t = decltype(&SavefileMetadata::FillDataFromFileName);
			REL::Relocation<func_t> func{ REL::ID(116131) };
			return func(this, a_fileName);
		}

		char FileNameA[260];
		_FILETIME CreationTimestamp;
		std::uint64_t PlayerLevel;
		std::uint32_t FilenameVersion;
		std::uint32_t SaveGameNumber;
		std::uint64_t PlayerID;
		BSStringT<char> PlayerName;
		BSStringT<char> PlayerLocID;
		BSStringT<char> PlayTime;
		bool IsValid;
		bool HasSaveNumber;
		bool NeedsSync;
		bool Modded;
		bool Survival;
	};

	class BGSSaveLoadFileEntry
	{
	public:

		void DeleteGame()
		{
			using func_t = decltype(&BGSSaveLoadFileEntry::DeleteGame);
			REL::Relocation<func_t> func{ REL::ID(91575) };
			return func(this);
		}

		void LoadData()
		{
			using func_t = decltype(&BGSSaveLoadFileEntry::LoadData);
			REL::Relocation<func_t> func{ REL::ID(1100644) };
			return func(this);
		}

		// members
		char* fileName;					 // 000
		char* playerName;				 // 008
		char* playerTitle;				 // 010
		char* location;					 // 018
		char* playTime;					 // 020
		char* raceName;					 // 028
		int version;					 // 030
		std::uint32_t saveGameNumber;    // 034
		std::uint32_t playerLevel;       // 038
		float levelProgress;			 // 03C
		float levelThreshold;			 // 040
		std::uint32_t screenshotWidth;   // 044
		std::uint32_t screenshotHeight;  // 048
		std::uint32_t screenshotOffset;  // 04C
		_FILETIME fileTime;				 // 050
		_FILETIME saveTime;				 // 058
		int deviceID;					 // 060
		bool loaded;					 // 064
		bool corrupt;					 // 065
		bool needsSync;					 // 066
	};
	static_assert(sizeof(BGSSaveLoadFileEntry) == 0x68);

	class BGSSaveLoadManager :
		public BSTEventSink<SPECIALMenuEvent::NameChangedEvent>  // 00
	{
	public:
		using SaveCompleteCallback_t = void (*)(BSSaveDataSystemUtility::RESULT, BSSaveDataSystemUtilityFile**);
		using LoadCompleteCallback_t = void (*)(BSSaveDataSystemUtility::RESULT, BSSaveDataSystemUtilityFile**);

		enum class QUEUED_TASK : std::int32_t
		{
			kAutoSave = 0x1,
			kForceSave = 0x2,
			kLoadMostRecentSave = 0x4,
			kQuickSave = 0x8,
			kQuickLoad = 0x10,
			kQuickNewSave = 0x20,
			kLoadGame = 0x40,
			kSysUtilLoadGame = 0x80,
			kMissingContentLoad = 0x100,
			kAutoSaveCommit = 0x200,
			kQuickSaveCommit = 0x400,
			kCaptureFaceGen = 0x800,
			kBuildSaveGameList = 0x1000,
			kRefreshScreenshot = 0x2000,
			kSaveAndQuit = 0x4000,
			kConfirmModsLoad = 0x8000,
			kSaveAndQuitToDesktop = 0x10000,
		};

		virtual ~BGSSaveLoadManager();  // 00

		// override (BSTEventSink)
		BSEventNotifyControl ProcessEvent(const SPECIALMenuEvent::NameChangedEvent& a_event, BSTEventSource<SPECIALMenuEvent::NameChangedEvent>* a_source) override;  // 01

		[[nodiscard]] static BGSSaveLoadManager* GetSingleton()
		{
			static REL::Relocation<BGSSaveLoadManager**> singleton{ REL::ID(2697802) };
			return *singleton;
		}

		void QueueSaveLoadTask(QUEUED_TASK a_task)
		{
			using func_t = decltype(&BGSSaveLoadManager::QueueSaveLoadTask);
			static REL::Relocation<func_t> func{ REL::ID(2228080) };
			return func(this, a_task);
		}

		std::uint32_t BuildSaveGameList(std::uint64_t a_playerID)
		{
			using func_t = decltype(&BGSSaveLoadManager::BuildSaveGameList);
			REL::Relocation<func_t> func{ REL::ID(1342984) };
			return func(this, a_playerID);
		}

		bool GetSaveDirectoryPath(char* a_directoryPath)
		{
			using func_t = decltype(&BGSSaveLoadManager::GetSaveDirectoryPath);
			REL::Relocation<func_t> func{ REL::ID(1569549) };
			return func(this, a_directoryPath);
		}

		// members
		BSTArray<BGSSaveLoadFileEntry*>          saveGameList;                  // 008
		bool                                     isSaveListBuilt;               // 020
		std::uint32_t                            saveGameCount;                 // 024
		std::uint32_t                            currentSaveGameNumber;         // 028
		std::uint64_t                            saveGameListBuildID;           // 030
		std::int32_t                             currentAutoSaveNumber;         // 038
		bool                                     simulatedMode;                 // 03C
		bool                                     autosaveDisabledForDiskspace;  // 03D
		std::uint32_t                            queuedTasks;                   // 040
		std::uint32_t                            saveOperationDelayCounter;     // 044
		BGSSaveLoadFileEntry*                    queuedEntryToLoad;             // 048
		std::uint64_t                            lastSaveTime;                  // 050
		bool                                     savingAllowed;                 // 058
		char*                                    mostRecentSaveGame;            // 060
		std::int32_t                             mostRecentSaveGameDeviceID;    // 068
		BSTHashMap<std::uint64_t, BSFixedString> playerIDNameMap;               // 070
		BSTHashMap<BSFixedString, BSFixedString> editorIdLocationMap;           // 0A0
		std::uint64_t                            currentPlayerID;               // 0D0
		std::uint64_t                            displayPlayerID;               // 0D8
		BSFixedString                            savefileNameToDelete;          // 0E0
		BSTHashMap<std::uint32_t, BSFixedString> autosaveFileNames;             // 0E8
		BSFixedString                            quicksaveFileName;             // 118
		BSFixedString                            exitsaveFileName;              // 120
		bool                                     hasSaveData;                   // 128
		BGSSaveLoadFile*                         saveLoadFile;                  // 130
		bool                                     returnedFromSysUtil;           // 138
		bool                                     sysUtilLoadDataComplete;       // 139
		SaveCompleteCallback_t                   sysUtilSaveCompleteCallback;   // 140
		LoadCompleteCallback_t                   sysUtilLoadCompleteCallback;   // 148
		BSSaveDataSystemUtilityImage             saveDataCreateImage;           // 150
		BSSaveDataSystemUtilityImage             saveDataBackgroundImage;       // 168
		BSSaveDataSystemUtilityImage             saveDataIconEncodedImage;      // 180
		NiPointer<NiTexture>                     screenshot[1];                 // 198
		BGSSaveLoadThread                        saveLoadTasksThread;           // 200
	};
	static_assert(sizeof(BGSSaveLoadManager) == 0x980);
}
