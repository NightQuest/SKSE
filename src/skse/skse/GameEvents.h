#pragma once

#include "Utilities.h"
#include "GameTypes.h"
#include "PapyrusVM.h"

template <typename T> class BSTEventSink;

enum EventResult
{
	kEvent_Continue = 0,
	kEvent_Abort
};

// 030
template <typename EventT, typename EventArgT = EventT>
class EventDispatcher
{
	typedef BSTEventSink<EventT> SinkT;

	SimpleLock			lock;				// 000
	tArray<SinkT*>		eventSinks;			// 008
	tArray<SinkT*>		addBuffer;			// 014 - schedule for add
	tArray<SinkT*>		removeBuffer;		// 020 - schedule for remove
	bool				stateFlag;			// 02C - some internal state changed while sending
	char				pad[3];

	MEMBER_FN_PREFIX(EventDispatcher);
	DEFINE_MEMBER_FN(AddEventSink_Internal, void, 0x008C5340, SinkT * eventSink);
	DEFINE_MEMBER_FN(RemoveEventSink_Internal, void, 0x006C0AD0, SinkT * eventSink);
	DEFINE_MEMBER_FN(SendEvent_Internal, void, 0x0073BF10, EventArgT * evn);

public:

	EventDispatcher() : stateFlag(false) {}

	void AddEventSink(SinkT * eventSink)		{ CALL_MEMBER_FN(this,AddEventSink_Internal)(eventSink); }
	void RemoveEventSink(SinkT * eventSink)		{ CALL_MEMBER_FN(this,RemoveEventSink_Internal)(eventSink); }
	void SendEvent(EventArgT * evn)				{ CALL_MEMBER_FN(this,SendEvent_Internal)(evn); }
};
STATIC_ASSERT(sizeof(EventDispatcher<void*>) == 0x30);

// 04
template <typename T>
class BSTEventSink
{
public:
	virtual ~BSTEventSink();
	virtual	EventResult	ReceiveEvent(T * evn, EventDispatcher<T> * dispatcher); // pure
//	void	** _vtbl;	// 00
};

// 30
template <typename T>
class BSTEventSource
{
public:
	virtual ~BSTEventSource();

//	void	** _vtbl;	// 00
	UInt32 unk04[11];	// 04
};

STATIC_ASSERT(sizeof(BSTEventSource<void*>) == 0x30);

// 08
struct TESSleepStartEvent
{
	float startTime;	// 00
	float endTime;		// 04
};

// 08
struct MenuOpenCloseEvent
{
	BSFixedString	menuName;	// 00
	bool			opening;	// 04
	char			pad[3];
};

// Todo
struct MenuModeChangeEvent
{
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

	enum
	{
		kDeviceType_Keyboard = 0,
		kDeviceType_Mouse
	};

	virtual			~InputEvent();
	virtual bool	IsIDEvent();
	virtual UInt32	GetID();

//	void			** _vtbl;	// 00
	const UInt32	deviceType;	// 04
	const UInt32	eventType;	// 08
	InputEvent		* next;		// 0C
};
STATIC_ASSERT(sizeof(InputEvent) == 0x10);

class IDEvent
{
public:
	UInt32			deviceID;			// 00 - device ID?
};

// 20
class ButtonEvent : public IDEvent, public InputEvent
{
public:
	UInt32			scanCode;	// 14
	UInt32			modFlags;	// 18 (00000038 when ALT is pressed, 0000001D when STRG is pressed)
	float			timer;		// 1C (hold duration)
};
STATIC_ASSERT(sizeof(ButtonEvent) == 0x20);

class MouseMoveEvent : public IDEvent, public InputEvent
{
};

// 14
class CharEvent : public InputEvent
{
public:
	UInt32			keyCode;		// 10 (ascii-compatible)
};
STATIC_ASSERT(sizeof(CharEvent) == 0x14);

class ThumbstickEvent : public IDEvent, public InputEvent
{
};

class DeviceConnectEvent : public InputEvent
{
};

class KinectEvent : public IDEvent, public InputEvent
{
};

class Character;
class TESForm;
class ActiveEffect;

struct TESActiveEffectApplyRemoveEvent
{
	Character		* caster;
	Character		* target;
	UInt32			unk08;
	UInt32			unk0C;
	UInt32			unk10;
	UInt32			unk14;
	UInt32			unk18; // Flags?
	UInt32			unk1C; // Use effect2 if this is 1
	TESForm			* source; // Not really sure what this is, probably the extra form
	ActiveEffect	* effect1;
	ActiveEffect	* effect2;
};


template <>
class BSTEventSink <TESSleepStartEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(TESSleepStartEvent * evn, EventDispatcher<TESSleepStartEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <MenuOpenCloseEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(MenuOpenCloseEvent * evn, EventDispatcher<MenuOpenCloseEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <InputEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(InputEvent ** evn, EventDispatcher<InputEvent,InputEvent*> * dispatcher) = 0;
};

// For testing
//extern EventDispatcher<TESSleepStartEvent> * g_sleepStartEventDispatcher;
extern EventDispatcher<InputEvent,InputEvent*> ** g_inputEventDispatcher;
