#pragma once

#include "GameTypes.h"

class TESCamera;
class NiNode;

class PlayerInputHandler
{
public:
	PlayerInputHandler();
	virtual ~PlayerInputHandler();

	virtual void Unk_01();
	virtual void Unk_02();
	virtual void Unk_03();
	virtual void Unk_04();

	UInt32	unk04;				// 04
	NiNode	* cameraNode;		// 08
	NiNode	* controllerNode;	// 0C
};

class TESCameraState
{
public:
	TESCameraState();
	virtual ~TESCameraState();

	virtual void Unk_01();
	virtual void Unk_02();
	virtual void Unk_03();
	virtual void Unk_04();
	virtual void Unk_05();
	virtual void Unk_06();
	virtual void Unk_07();
	virtual void Unk_08();

	BSIntrusiveRefCounted	refCount;	// 04
	TESCamera				* camera;	// 08
	UInt32					unk0C;		// 0C
};

class DragonCameraState : public TESCameraState
{
public:
	DragonCameraState();
	virtual ~DragonCameraState();

	PlayerInputHandler		inputHandler;	// 10
};

class HorseCameraState : public TESCameraState
{
public:
	HorseCameraState();
	virtual ~HorseCameraState();

	PlayerInputHandler		inputHandler;	// 10
};

class TweenMenuCameraState : public TESCameraState
{
public:
	TweenMenuCameraState();
	virtual ~TweenMenuCameraState();
};

class VATSCameraState : public TESCameraState
{
public:
	VATSCameraState();
	virtual ~VATSCameraState();
};

class FreeCameraState : public TESCameraState
{
public:
	FreeCameraState();
	virtual ~FreeCameraState();
};

class AutoVanityState : public TESCameraState
{
public:
	AutoVanityState();
	virtual ~AutoVanityState();
};

class FurnitureCameraState : public TESCameraState
{
public:
	FurnitureCameraState();
	virtual ~FurnitureCameraState();
};

class IronSightsState : public TESCameraState
{
public:
	IronSightsState();
	virtual ~IronSightsState();
};

class FirstPersonState : public TESCameraState
{
public:
	FirstPersonState();
	virtual ~FirstPersonState();

	PlayerInputHandler		inputHandler;	// 10
};

class ThirdPersonState : public TESCameraState
{
public:
	ThirdPersonState();
	virtual ~ThirdPersonState();

	PlayerInputHandler		inputHandler;	// 10
};

class BleedoutCameraState : public ThirdPersonState
{
public:
	BleedoutCameraState();
	virtual ~BleedoutCameraState();

	PlayerInputHandler		inputHandler;	// 10
};

class PlayerCameraTransitionState : public TESCameraState
{
public:
	PlayerCameraTransitionState();
	virtual ~PlayerCameraTransitionState();
};

class TESCamera
{
public:
	TESCamera();
	virtual ~TESCamera();

	virtual void Unk_01();
	virtual void Unk_02();

	UInt32			unk04[0x06];	// 04
	NiNode			* niNode;		// 18
	TESCameraState	* cameraState;	// 1C
	UInt32			unk20[0x01];	// 20

	MEMBER_FN_PREFIX(TESCamera);
	DEFINE_MEMBER_FN(SetCameraState, UInt32, 0x00653040, TESCameraState * cameraState);
	// sub_653040 - UInt32 SetState(PlayerInputHandler*)
};

class LocalMapCamera : public TESCamera
{
public:
	LocalMapCamera();
	virtual ~LocalMapCamera();
};

class MapCamera : public TESCamera
{
public:
	MapCamera();
	virtual ~MapCamera();
};

class RaceSexCamera : public TESCamera
{
public:
	RaceSexCamera();
	virtual ~RaceSexCamera();
};

class PlayerCamera : public TESCamera
{
public:
	PlayerCamera();
	virtual ~PlayerCamera();

	static PlayerCamera *	GetSingleton(void)
	{
		return *((PlayerCamera **)0x012E6488);
	}

	enum
	{
		kCameraState_FirstPerson = 0,
		kCameraState_AutoVanity,
		kCameraState_VATS,
		kCameraState_Free,
		kCameraState_IronSights,
		kCameraState_Furniture,
		kCameraState_Transition,
		kCameraState_TweenMenu,
		kCameraState_ThirdPerson1,
		kCameraState_ThirdPerson2,
		kCameraState_Horse,
		kCameraState_Bleedout,
		kCameraState_Dragon,
		kNumCameraStates
	};

	UInt32 unk24[(0x68 - 0x24) >> 2];	// 24
	TESCameraState * cameraStates[kNumCameraStates];	// 68
};
