#pragma once

#include "skse/ScaleformCallbacks.h"
#include "skse/GameTypes.h"
#include "skse/GameEvents.h"
#include "skse/Utilities.h"
#include "skse/Hooks_UI.h"

class TESObjectREFR;

//// menu implementations

// 1C+
class IMenu : public FxDelegateHandler
{
public:
	IMenu();
	virtual ~IMenu();
	
	virtual void	InstallCallbacks(AddCallbackVisitor * visitor);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual UInt32	Unk_04(void * arg);
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);	// CurrentTime
	virtual void	Unk_06(void);

	GFxMovieView	* view;	// 08 - init'd to 0, a class, virtual fn 0x114 called in dtor
	UInt8			unk0C;		// 0C - init'd to 3
	UInt8			pad0D[3];	// 0D
	UInt32			unk10;		// 10 - init'd to 0
	UInt32			unk14;		// 14 - init'd to 0x12
	GRefCountBase	* unk18;	// 18 - holds a reference
};

// 34
class Console : public IMenu
{
public:
	// C+
	struct Unk20
	{
		struct Unk0
		{
			UInt32	unk0;
			UInt32	unk4;
		};

		struct Unk8
		{
			UInt32	unk0;
		};

		Unk0	unk0;	// 0
		Unk8	unk8;	// 8
	};

	void	* opcodeInfo;	// 1C - constructor checks that opcodes match
	Unk20	unk20;			// 20 - init'd to 0, probably history linked list?
	UInt32	unk2C;			// 2C - init'd to 0
	UInt8	unk30;			// 30 - init'd to 0
};

// 68
class BarterMenu : public IMenu
{
	GFxValue	* root;		// 1C
	// ...
	UInt8		unk34;		// 34
};

//// menu management

// 08
class IUIMessageData
{
public:
	virtual ~IUIMessageData();

//	void	** _vtbl;	// 00
	UInt8	unk04;		// 04
	UInt8	unk05;		// 05
	UInt8	pad06[2];	// 06
};

// 14
class BSUIMessageData : public IUIMessageData
{
public:
	BSString			* unk08;	// 08
	StringCache::Ref	unk0C;		// 0C
	UInt32				unk10;		// 10
};

// 10
// ### pool added in 1.3 (or maybe 1.2)
class UIMessage
{
public:
	enum
	{
		kMessage_Refresh = 0,	// used after ShowAllMapMarkers
		kMessage_Open,
		kMessage_Close,
	};

	StringCache::Ref	strData;	// 00
	UInt32				message;	// 04
	IUIMessageData		* objData;	// 08 - something with a virtual destructor
	UInt8				isPooled;	// 0C
	UInt8				pad0D[3];	// 0D
};

// 04
template <typename T>
class BSTMessageQueue
{
public:
	BSTMessageQueue();
	virtual ~BSTMessageQueue();

	virtual bool	Push(T * obj);		// pure, add (loop until lock taken, call Fn05)
	virtual bool	TryPush(T * obj);	// pure, try add (try to take lock, return false if already taken, else call Fn05)
	virtual bool	Pop(T * obj);		// pure, remove (loop until lock taken, call Fn06)
	virtual bool	TryPop(T * obj);	// pure, try remove (try to take lock, return false if already taken, else call Fn06)

//	void	** _vtbl;	// 00
};

// 08
template <typename T>
class BSTCommonMessageQueue : public BSTMessageQueue <T>
{
protected:
	virtual bool	PushInternal(T * obj);	// pure
	virtual bool	PopInternal(T * obj);	// pure

public:
	volatile UInt32	lock;	// 04
};

// 08 + sizeof(T) * T_len + 0C
template <typename T, UInt32 T_len>
class BSTCommonStaticMessageQueue : public BSTCommonMessageQueue <T>
{
public:
	T		data[T_len];	// 008
	UInt32	numEntries;		// 198 - offsets are for <UIMessage *, 100>
	UInt32	writePtr;		// 19C
	UInt32	readPtr;		// 1A0
};

// 1C8
// 5CC - pool added in 1.2 or 1.3
class UIManager
{
public:
	enum
	{
		kPoolSize = 0x40,
	};

	typedef BSTCommonStaticMessageQueue <UIMessage *, 100>	MessageQueue;

	UInt32			unk000;		// 000
	MessageQueue	messages;	// 004
	UInt32			pad1A8[(0x1C8 - 0x1A8) / 4];	// 1A8
	UInt32			poolUsed;	// 1C8
	UIMessage		messagePool[kPoolSize];	// 1CC

	MEMBER_FN_PREFIX(UIManager);
	// this takes ownership of the message ptr
//	DEFINE_MEMBER_FN(AddMessage, void, 0x004503E0, UIMessage * msg);	// old 1.1 implementation
	// 1.3 uses a little non-thread-safe pool of UIMessages to wrap around the nicely thread-safe BSTMessageQueue it gets added to
	DEFINE_MEMBER_FN(AddMessage, void, 0x00431CE0, StringCache::Ref * strData, UInt32 msgID, void * objData);

	static UIManager *	GetSingleton(void)
	{
		return *((UIManager **)0x012E27E4);
	}

	// Used by Hooks_UI
	void ProcessCommands(void);
	void QueueCommand(UIDelegate * cmd);

	DEFINE_MEMBER_FN(ProcessEventQueue_HookTarget, void, 0x00A5B8E0);
};


// 11C
class UIStringHolder
{
public:
	void			* unk00;					// 000
	BSFixedString	faderData;					// 004 "FaderData"
	BSFixedString	hudData;					// 008 "HUDData"
	BSFixedString	hudCamData;					// 00C "HUDCamData"
	BSFixedString	floatingQuestMarkers;		// 010 "FloatingQuestMarkers"
	BSFixedString	consoleData;				// 014 "ConsoleData"
	BSFixedString	quantityData;				// 018 "QuantityData"
	BSFixedString	messageBoxData;				// 01C "MessageBoxData"
	BSFixedString	bsUIScaleformData;			// 020 "BSUIScaleformData"
	BSFixedString	bsUIMessageData;			// 024 "BSUIMessageData"
	BSFixedString	bsUIAnalogData;				// 028 "BSUIAnalogData"
	BSFixedString	inventoryUpdateData;		// 02C "InventoryUpdateData"
	BSFixedString	refHandleUIData;			// 030 "RefHandleUIData"
	BSFixedString	tesFormUIData;				// 034 "TESFormUIData"
	BSFixedString	loadingMenuData;			// 038 "LoadingMenuData"
	BSFixedString	kinectStateData;			// 03C "KinectStateChangeData"
	BSFixedString	kinectUserEventData;		// 040 "KinectUserEventData"
	BSFixedString	inventoryMenu;				// 044 "InventoryMenu"
	BSFixedString	console;					// 048 "Console"
	BSFixedString	dialogueMenu;				// 04C "Dialogue Menu"
	BSFixedString	hudMenu;					// 050 "HUD Menu"
	BSFixedString	mainMenu;					// 054 "Main Menu"
	BSFixedString	messageBoxMenu;				// 058 "MessageBoxMenu"
	BSFixedString	cursorMenu;					// 05C "Cursor Menu"
	BSFixedString	faderMenu;					// 060 "Fader Menu"
	BSFixedString	magicMenu;					// 064 "MagicMenu"
	BSFixedString	topMenu;					// 068 "Top Menu"
	BSFixedString	overlayMenu;				// 06C "Overlay Menu"
	BSFixedString	overlayInteractionMenu;		// 070 "Overlay Interaction Menu"
	BSFixedString	loadingMenu;				// 074 "Loading Menu"
	BSFixedString	tweenMenu;					// 078 "TweenMenu"
	BSFixedString	barterMenu;					// 07C "BarterMenu"
	BSFixedString	giftMenu;					// 080 "GiftMenu"
	BSFixedString	debugTextMenu;				// 084 "Debug Text Menu"
	BSFixedString	mapMenu;					// 088 "MapMenu"
	BSFixedString	lockpickingMenu;			// 08C "Lockpicking Menu"
	BSFixedString	quantityMenu;				// 090 "Quantity Menu"
	BSFixedString	statsMenu;					// 094 "StatsMenu"
	BSFixedString	containerMenu;				// 098 "ContainerMenu"
	BSFixedString	sleepWaitMenu;				// 09C "Sleep/Wait Menu"
	BSFixedString	levelUpMenu;				// 0A0 "LevelUp Menu"
	BSFixedString	journalMenu;				// 0A4 "Journal Menu"
	BSFixedString	bookMenu;					// 0A8 "Book Menu"
	BSFixedString	favoritesMenu;				// 0AC "FavoritesMenu"
	BSFixedString	raceSexMenu;				// 0B0 "RaceSex Menu"
	BSFixedString	craftingMenu;				// 0B4 "Crafting Menu"
	BSFixedString	trainingMenu;				// 0B8 "Training Menu"
	BSFixedString	mistMenu;					// 0BC "Mist Menu"
	BSFixedString	tutorialMenu;				// 0C0 "Tutorial Menu"
	BSFixedString	creditsMenu;				// 0C4 "Credits Menu"
	BSFixedString	titleSequenceMenu;			// 0C8 "TitleSequence Menu"
	BSFixedString	consoleNativeUIMenu;		// 0CC "Console Native UI Menu"
	BSFixedString	kinectMenu;					// 0D0 "Kinect Menu"
	BSFixedString	textWidget;					// 0D4 "TextWidget"
	BSFixedString	buttonBarWidget;			// 0D8 "ButtonBarWidget"
	BSFixedString	graphWidget;				// 0DC "GraphWidget"
	BSFixedString	textureWidget;				// 0E0 "TextureWidget"
	BSFixedString	uiMenuOK;					// 0E4 "UIMenuOK"
	BSFixedString	uiMenuCancel;				// 0E8 "UIMenuCancel"
	BSFixedString	showText;					// 0EC "Show Text"
	BSFixedString	hideText;					// 0F0 "Hide Text"
	BSFixedString	showList;					// 0F4 "Show List"
	BSFixedString	voiceReady;					// 0F8 "Voice Ready"
	BSFixedString	dmfoStr;					// 0FC "DMFOStr"
	BSFixedString	showJournal;				// 100 "Show Journal"
	BSFixedString	journalSettingsSaved;		// 104 "Journal Settings Saved"
	BSFixedString	closeMenu;					// 108 "CloseMenu"
	BSFixedString	closingAllMenus;			// 10C "Closing All Menus"
	BSFixedString	refreshMenu;				// 110 "RefreshMenu"
	BSFixedString	menuTextureDegradeEvent;	// 114 "Menu Texture Degrade Event"
	BSFixedString	diamondMarker;				// 118 "<img src='DiamondMarker' width='10' height='15' align='baseline' vspace='5'>"

	static UIStringHolder *	GetSingleton(void)
	{
		return *((UIStringHolder **)0x012E27E0);
	}
};

// E4
class Inventory3DManager
{
public:
	~Inventory3DManager();

	static Inventory3DManager * GetSingleton(void)
	{
		return *((Inventory3DManager **)0x01B2DC8C);
	}

//	void			** _vtbl;	// 00
	UInt32			pad04[(0x34 - 0x04) / 4];	// 04
	TESObjectREFR	* object;	// 34
	// ...
};

// 00C
class MenuTableItem
{
public:
	BSFixedString	name;				// 000
	IMenu			* menuInstance;		// 004	0 if the menu is not currently open
	void			* menuConstructor;	// 008

	bool operator==(const MenuTableItem & rhs) const	{ return name == rhs.name; }
	bool operator==(const BSFixedString a_name) const	{ return name == a_name; }
	operator UInt32() const								{ return (UInt32)name.data; }

	static inline UInt32 GetHash(BSFixedString * key)
	{
		UInt32 hash;
		CRC32_Calc4(&hash, (UInt32)key->data);
		return hash;
	}

	void Dump(void)
	{
		_MESSAGE("\t\tname: %s", name);
		_MESSAGE("\t\tinstance: %08X", menuInstance);
	}
};

typedef tHashSet<MenuTableItem,BSFixedString> MenuTable;

// 11C
class MenuManager
{

	// 030
	struct Unknown3
	{
		UInt32		freqLow;	// 000 (= Frequency.LowPart)
		UInt32		freqHigh;	// 004 (= Frequency.HighPart)

		UInt32		unk_008;	// 008 (= 0)
		UInt32		unk_00C;	// 00C (= 0)
		UInt32		unk_010;	// 010 (= 0)
		UInt32		unk_014;	// 014 (= 0)
		UInt32		unk_018;	// 018 (= 0)
		UInt32		unk_01C;	// 018 (= frequency related)
		
		UInt32		unk_020;	// 020
		UInt32		unk_024;	// 024

		UInt32		unk_028;	// 028 (= 0)
		UInt32		unk_02C;	// 02C (= 0)
	};
	STATIC_ASSERT(sizeof(Unknown3) == 0x30);

private:

	UInt32					unk_000;	// 000

	EventDispatcher<MenuOpenCloseEvent>		menuOpenCloseEventDispatcher;	// 004
	EventDispatcher<MenuModeChangeEvent>	menuModeChangeEventDispatcher;	// 034
	EventDispatcher<void*>					unk_064;						// 064 - New in 1.6.87.0 - Kintect related?

	UnkArray				menuStack;	// 094
	UInt32					unk_0A0;	// 0A0
	MenuTable				menuTable;	// 0A4
	UInt32					unk_0C0;	// 0C0 (= 0)
	UInt32					unk_0C4;	// 0C4 (= 0)
	UInt32					unk_0C8;	// 0C8 (= 0)
	UInt32					unk_0CC;	// 0CC (= 0)
	UInt32					unk_0D0;	// 0D0 (= 0)
	UInt32					unk_0D4;	// 0D4 (= 0)
	UInt32					unk_0D8;	// 0D8 (= 0)
	UInt32					unk_0DC;	// 0DC (= 0)
	UInt32					unk_0E0;	// 0E0 (= 0)
	UInt32					unk_0E4;	// 0E4
	Unknown3				unk_0E8;
	bool					unk_118;	// 118 (= 0)
	bool					unk_119;	// 119 (= 0)
	char					pad[2];

	MEMBER_FN_PREFIX(MenuManager);
	DEFINE_MEMBER_FN(IsMenuOpen, bool, 0x00A5C490, BSFixedString * menuName);
	//DEFINE_MEMBER_FN(Register, void, 0x00A5C8A0, const char * name, void * ctorFunc);

public:

	static MenuManager * GetSingleton(void)
	{
		return *((MenuManager **)0x012E2748);
	}

	EventDispatcher<MenuOpenCloseEvent> * MenuOpenCloseEventDispatcher()
	{
		return &menuOpenCloseEventDispatcher;
	}

	bool				IsMenuOpen(BSFixedString * menuName);
	GFxMovieView *		GetMovieView(BSFixedString * menuName);
};
STATIC_ASSERT(sizeof(MenuManager) == 0x11C);

// ?
class UISaveLoadManager
{
public:
	virtual ~UISaveLoadManager();

	// See Hooks_SaveLoad
	void DeleteSavegame_Hook(double saveIndex);

	static UISaveLoadManager * GetSingleton(void)
	{
		return *((UISaveLoadManager **)0x01B0FFCC);
	}

private:
	MEMBER_FN_PREFIX(UISaveLoadManager);
	DEFINE_MEMBER_FN(DeleteSavegame_HookTarget, void, 0x00897EF0, double saveIndex);
};
