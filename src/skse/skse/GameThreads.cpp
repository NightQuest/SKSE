#include "GameThreads.h"
#include "GameAPI.h"
#include "GameReferences.h"
#include "GameData.h"
#include "GameForms.h"
#include "GameRTTI.h"

#include "common/IMemPool.h"

IThreadSafeBasicMemPool<SKSETaskUpdateTintMasks,10>		s_updateTintMasksDelegatePool;
IThreadSafeBasicMemPool<SKSETaskUpdateHairColor,10>		s_updateHairColorDelegatePool;
IThreadSafeBasicMemPool<SKSETaskRegenHead,10>			s_regenHeadDelegatePool;
IThreadSafeBasicMemPool<SKSETaskChangeHeadPart,10>		s_changeHeadPartDelegatePool;

void BSTaskPool::UpdateTintMasks()
{
	SKSETaskUpdateTintMasks * cmd = s_updateTintMasksDelegatePool.Allocate();
	if(cmd) {
		QueueTask(cmd);
	}
}

void BSTaskPool::UpdateHairColor()
{
	SKSETaskUpdateHairColor * cmd = s_updateHairColorDelegatePool.Allocate();
	if(cmd) {
		QueueTask(cmd);
	}
}

void BSTaskPool::RegenerateHead(Actor * actor)
{
	SKSETaskRegenHead * cmd = SKSETaskRegenHead::Create(actor);
	if(cmd) {
		QueueTask(cmd);
	}
}

void BSTaskPool::ChangeHeadPart(Actor * actor, BGSHeadPart * headPart)
{
	SKSETaskChangeHeadPart * cmd = SKSETaskChangeHeadPart::Create(actor, headPart);
	if(cmd) {
		QueueTask(cmd);
	}
}

void SKSETaskUpdateTintMasks::Dispose(void)
{
	s_updateTintMasksDelegatePool.Free(this);
}

void SKSETaskUpdateTintMasks::Run()
{
	(*g_thePlayer)->UpdateSkinColor();
	UpdatePlayerTints();
}

void SKSETaskUpdateHairColor::Run()
{
	(*g_thePlayer)->UpdateHairColor();
}

void SKSETaskUpdateHairColor::Dispose(void)
{
	s_updateHairColorDelegatePool.Free(this);
}

SKSETaskRegenHead * SKSETaskRegenHead::Create(Actor * actor)
{
	SKSETaskRegenHead * cmd = s_regenHeadDelegatePool.Allocate();
	if (cmd)
	{
		cmd->m_actor = actor;
	}
	return cmd;
}

void SKSETaskRegenHead::Dispose(void)
{
	s_regenHeadDelegatePool.Free(this);
}

void SKSETaskRegenHead::Run()
{
	TESNPC * npc = DYNAMIC_CAST(m_actor->baseForm, TESForm, TESNPC);
	BSFaceGenNiNode * faceNode = m_actor->GetFaceGenNiNode();
	BGSHeadPart * facePart = NULL;
	if(CALL_MEMBER_FN(npc, HasOverlays)()) {
		facePart = npc->GetHeadPartOverlayByType(BGSHeadPart::kTypeFace);
	} else {
		facePart = CALL_MEMBER_FN(npc, GetHeadPartByType)(BGSHeadPart::kTypeFace);
	}
	if(npc && faceNode && facePart) {
		CALL_MEMBER_FN(FaceGen::GetSingleton(), RegenerateHead)(faceNode, facePart, npc);
	}
}


SKSETaskChangeHeadPart * SKSETaskChangeHeadPart::Create(Actor * actor, BGSHeadPart* newPart)
{
	SKSETaskChangeHeadPart * cmd = s_changeHeadPartDelegatePool.Allocate();
	if (cmd)
	{
		cmd->m_actor = actor;
		cmd->m_newPart = newPart;
	}
	return cmd;
}

void SKSETaskChangeHeadPart::Dispose(void)
{
	s_changeHeadPartDelegatePool.Free(this);
}

void SKSETaskChangeHeadPart::Run()
{
	if(m_actor && m_newPart) {
		if(m_newPart->type != BGSHeadPart::kTypeMisc) {
			TESNPC * npc = DYNAMIC_CAST(m_actor->baseForm, TESForm, TESNPC);
			if(npc) {
				BGSHeadPart * oldPart = NULL;
				if(CALL_MEMBER_FN(npc, HasOverlays)())
					oldPart = npc->GetHeadPartOverlayByType(m_newPart->type);
				if(!oldPart)
					oldPart = CALL_MEMBER_FN(npc, GetHeadPartByType)(m_newPart->type);

				CALL_MEMBER_FN(npc, ChangeHeadPart)(m_newPart);
				ChangeActorHeadPart(m_actor, oldPart, m_newPart);
			}
		}
	}
}
