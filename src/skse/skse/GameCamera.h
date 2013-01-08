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

	UInt32	unk04;
	NiNode	* cameraNode;
	NiNode	* controllerNode;
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

	BSIntrusiveRefCounted	refCount;
	TESCamera				* camera;
	UInt32					unk0C;
	PlayerInputHandler		inputHandler;
};

class TweenMenuCameraState : public TESCameraState
{
	TweenMenuCameraState();
	virtual ~TweenMenuCameraState();
};

class VATSCameraState : public TESCameraState
{
	VATSCameraState();
	virtual ~VATSCameraState();
};

class FreeCameraState : public TESCameraState
{
	FreeCameraState();
	virtual ~FreeCameraState();
};

class AutoVanityState : public TESCameraState
{
	AutoVanityState();
	virtual ~AutoVanityState();
};

class FurnitureCameraState : public TESCameraState
{
	FurnitureCameraState();
	virtual ~FurnitureCameraState();
};

class IronSightsState : public TESCameraState
{
	IronSightsState();
	virtual ~IronSightsState();
};

class FirstPersonState : public TESCameraState
{
	FirstPersonState();
	virtual ~FirstPersonState();
};

class ThirdPersonState : public TESCameraState
{
	ThirdPersonState();
	virtual ~ThirdPersonState();
};

class BleedoutCameraState : public ThirdPersonState
{
	BleedoutCameraState();
	virtual ~BleedoutCameraState();
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

	UInt32			unk04[0x06];
	NiNode			* niNode;
	TESCameraState	* cameraState;
	UInt32			unk20[0x01];
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
};
