#pragma once

#include "GameTypes.h"
#include "GameEvents.h"
#include "InputMap.h"

// Note: These are different from those in Hooks_DI
enum
{
	kDeviceType_Keyboard = 0,
	kDeviceType_Mouse,
	kDeviceType_Gamepad
};

class BSInputDevice
{
public:
	virtual UInt32	Unk_01(void);		// pure
	virtual	void	Unk_02(float unk1);	// pure
	virtual	void	Unk_03(void);		// pure
	virtual bool	IsEnabled(void);	// Always 1 for non-gamepad?
	virtual			~BSInputDevice();
	virtual void	Unk_06(void);		// pure
};

// 10 - See sub_A61970
class InputEvent
{
public:
	enum
	{
		kEventType_Button = 0,
		kEventType_MouseMove,
		kEventType_Char,
		kEventType_Thumbstick,
		kEventType_DeviceConnect,
		kEventType_Kinect
	};

	virtual			~InputEvent();
	virtual bool	IsIDEvent();
	virtual UInt32	GetID();

//	void			** _vtbl;	// 00
	UInt32			deviceType;	// 04
	UInt32			eventType;	// 08
	InputEvent		* next;		// 0C
};

class IDEvent
{
public:
	UInt32			deviceID;			// 00 - device ID?
};

// 20
class ButtonEvent : public IDEvent, public InputEvent
{
public:
	UInt32			keyMask;	// 14
	UInt32			modFlags;	// 18 (00000038 when ALT is pressed, 0000001D when STRG is pressed)
	float			timer;		// 1C (hold duration)
};

class MouseMoveEvent : public IDEvent, public InputEvent
{
};

// 14
class CharEvent : public InputEvent
{
public:
	UInt32			keyCode;		// 10 (ascii-compatible)
};

class ThumbstickEvent : public IDEvent, public InputEvent
{
};

class DeviceConnectEvent : public InputEvent
{
};

class KinectEvent : public IDEvent, public InputEvent
{
};

class InputEventDispatcher : public EventDispatcher<InputEvent,InputEvent*>
{
public:
	UInt32			unk030;		// 030
	BSInputDevice	* keyboard;	// 034
	BSInputDevice	* mouse;	// 038
	BSInputDevice	* gamepad;	// 03C
	
	bool	IsGamepadEnabled(void);
};
STATIC_ASSERT(offsetof(InputEventDispatcher, gamepad) == 0x03C);

extern InputEventDispatcher ** g_inputEventDispatcher;

template <>
class BSTEventSink <InputEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(InputEvent ** evn, InputEventDispatcher * dispatcher) = 0;
};

// 9C
class InputManager
{
public:
	enum
	{
		kContext_Gameplay = 0,
		kContext_MenuMode,
		kContext_Console,
		kContext_ItemMenu,
		kContext_Inventory,
		kContext_DebugText,
		kContext_Favorites,
		kContext_Map,
		kContext_Stats,
		kContext_Cursor,
		kContext_Book,
		kContext_DebugOverlay,
		kContext_Journal,
		kContext_TFCMode,
		kContext_MapDebug,
		kContext_Lockpicking,
		kContext_Favor,
		kContextCount = 17
	};

	struct InputContext
	{
		// 10
		struct Mapping
		{
			const char	* name;		// 00
			UInt32		buttonID;	// 04
			UInt32		sortIndex;	// 08
			UInt32		unk0C;		// 0C
		};

		tArray<Mapping>	keyboardMap;
		tArray<Mapping>	mouseMap;
		tArray<Mapping>	gamepadMap;
	};

	UInt8			pad00[0x34];				// 00
	InputContext	* context[kContextCount];	// 34
	UInt8			pad78[0x20];				// 78
	UInt8			allowTextInput;				// 98
	UInt8			pad99[3];					// 99

	static InputManager *	GetSingleton(void);

	UInt8	AllowTextInput(bool allow);

	UInt32	GetMappedKey(const char * name, UInt32 deviceType, UInt32 contextIdx);
};
STATIC_ASSERT(sizeof(InputManager) == 0x9C);

//?
class PlayerControls
{
public:
	virtual			~PlayerControls();
	virtual UInt32	Unk_01();

//	void			** _vtbl;		// 00
	UInt8			pad04[0x3C];	// 04
	bool			remapMode;		// 40 - might be named differently
	UInt8			pad41[3];		// 41

	static PlayerControls *	GetSingleton(void);
};
STATIC_ASSERT(offsetof(PlayerControls, remapMode) == 0x040);

// ?
class MenuControls
{
public:
	virtual			~MenuControls();
	virtual UInt32	Unk_01();

//	void			** _vtbl;		// 00
	UInt8			pad04[0x3C];	// 04
	UInt8			pad40;			// 40
	UInt8			pad41;			// 41
	bool			remapMode;		// 42
	UInt8			pad43;			// 43

	static MenuControls *	GetSingleton(void);
};
STATIC_ASSERT(offsetof(MenuControls, remapMode) == 0x042);