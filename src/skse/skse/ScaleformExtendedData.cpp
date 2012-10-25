#include "ScaleformCallbacks.h"
#include "ScaleformMovie.h"
#include "ScaleformExtendedData.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "GameRTTI.h"

// Helpers
double round(double r)
{
	return (r >= 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void RegisterString(GFxValue * dst,  GFxMovieView * view, const char * name, const char * str)
{
	GFxValue	fxValue;

	view->CreateString(&fxValue, str);

	dst->SetMember(name, &fxValue);
}

void RegisterNumber(GFxValue * dst, const char * name, double value)
{
	GFxValue	fxValue;

	fxValue.SetNumber(value);

	dst->SetMember(name, &fxValue);
}

void RegisterBool(GFxValue * dst, const char * name, bool value)
{
	GFxValue fxValue;
	fxValue.SetBool(value);
	dst->SetMember(name, &fxValue);
}

void RegisterKeywords(GFxValue * pFxVal, GFxMovieView * view, BGSKeywordForm * keywordForm)
{
	GFxValue	keywordRoot;
	view->CreateObject(&keywordRoot);

	// Add all keywords as boolean properties with value true

	UInt32 count = keywordForm->numKeywords;
	BGSKeyword ** keywords = keywordForm->keywords;
	if(keywords)
	{
		for(int i = 0; i < count; i++)
		{
			BGSKeyword * pKey = keywords[i];
			if(pKey)
			{
				const char * keyString = pKey->keyword.Get();
				if(keyString)
				{
					RegisterBool(&keywordRoot, keyString, true);
				}
			}
		}
	}

	pFxVal->SetMember("keywords", &keywordRoot);
}

// Data extensions
namespace scaleformExtend
{
	void CommonItemData(GFxValue* pFxVal, TESForm * pForm)
	{
		if(!pFxVal || !pForm)
			return;

		RegisterBool(pFxVal, "extended", true);
		RegisterNumber(pFxVal, "formType", (double)pForm->GetFormType());
		RegisterNumber(pFxVal, "formId", (double)pForm->formID);
	}

	void StandardItemData(GFxValue * pFxVal, TESForm * pForm)
	{
		if(!pForm || !pFxVal)
			return;

		switch(pForm->GetFormType())
		{
		case kFormType_Armor:
			{
				TESObjectARMO * pArmor = DYNAMIC_CAST(pForm, TESForm, TESObjectARMO);
				if(pArmor)
				{
					RegisterNumber(pFxVal, "partMask", pArmor->bipedObject.data.parts);
					RegisterNumber(pFxVal, "weightClass", pArmor->bipedObject.data.weightClass);
				}
			}
			break;

		case kFormType_Weapon:
			{
				TESObjectWEAP * pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
				if(pWeapon)
				{
					UInt8 weaponType = pWeapon->type();
					RegisterNumber(pFxVal, "subType", weaponType);
					RegisterNumber(pFxVal, "speed", pWeapon->speed());
					RegisterNumber(pFxVal, "reach", pWeapon->reach());
					RegisterNumber(pFxVal, "stagger", pWeapon->stagger());
					RegisterNumber(pFxVal, "critDamage", pWeapon->critDamage());
					RegisterNumber(pFxVal, "minRange", pWeapon->minRange());
					RegisterNumber(pFxVal, "maxRange", pWeapon->maxRange());
				}
			}
			break;

		case kFormType_SoulGem:
			{
				TESSoulGem	* soulGem = DYNAMIC_CAST(pForm, TESForm, TESSoulGem);
				if(soulGem)
				{
					RegisterNumber(pFxVal, "soulSize", soulGem->soulSize);
					RegisterNumber(pFxVal, "gemSize", soulGem->gemSize);
				}
			}
			break;

		case kFormType_Potion:
			{
				AlchemyItem * pAlchemy = DYNAMIC_CAST(pForm, TESForm, AlchemyItem);
				if(pAlchemy)
				{
					RegisterNumber(pFxVal, "flags", pAlchemy->unkA4.unk00.flags);
				}
			}
			break;

		case kFormType_Book:
			{
				TESObjectBOOK * pBook = DYNAMIC_CAST(pForm, TESForm, TESObjectBOOK);
				if(pBook)
				{
					RegisterNumber(pFxVal, "bookType", pBook->data.type);
					switch(pBook->data.GetSanitizedType())
					{
					case TESObjectBOOK::Data::kType_Skill:
						RegisterNumber(pFxVal, "teachesSkill", pBook->data.teaches.skill);
						break;

					case TESObjectBOOK::Data::kType_Spell:
						{
							double formID = -1;

							if(pBook->data.teaches.spell)
								formID = pBook->data.teaches.spell->formID;

							RegisterNumber(pFxVal, "teachesSpell", formID);
						}
						break;
					}
				}
			}
			break;

		default:
			break;
		}
	}


	void MagicItemData(GFxValue * pFxVal, GFxMovieView * movieView, TESForm * pForm)
	{
		if(!pFxVal || !pForm)
			return;

		switch(pForm->GetFormType())
		{
		case kFormType_Spell:
		case kFormType_ScrollItem:
		case kFormType_Ingredient:
		case kFormType_Potion:
			{
				MagicItem * pMagicItem = DYNAMIC_CAST(pForm, TESForm, MagicItem);
				if(pMagicItem)
				{
					if(pMagicItem->fullName.name.data)
						RegisterString(pFxVal, movieView, "spellName", pMagicItem->fullName.name.data);

					MagicItem::EffectItem * pEffect = CALL_MEMBER_FN(pMagicItem, GetCostliestEffectItem)(5, false);
					if(pEffect && pEffect->mgef)
					{
						RegisterNumber(pFxVal, "magnitude", pEffect->magnitude);
						RegisterNumber(pFxVal, "duration", pEffect->duration);
						RegisterNumber(pFxVal, "area", pEffect->area);

						// PLB: Normally I'd have this as a separate object but SkyUI is already using this
						scaleformExtend::MagicItemData(pFxVal, movieView, pEffect->mgef);
					}
				}
			}
			break;

		case kFormType_EffectSetting:
			{
				EffectSetting * pEffectSetting = DYNAMIC_CAST(pForm, TESForm, EffectSetting);
				if(pEffectSetting)
				{
					UInt32 school = pEffectSetting->school();
					UInt32 skillLevel = pEffectSetting->level();

					if(pEffectSetting->fullName.name.data)
						RegisterString(pFxVal, movieView, "effectName", pEffectSetting->fullName.name.data);

					RegisterNumber(pFxVal, "subType", pEffectSetting->school());
					RegisterNumber(pFxVal, "skillLevel", pEffectSetting->level());
					RegisterNumber(pFxVal, "archetype", pEffectSetting->properties.archetype);
					RegisterNumber(pFxVal, "deliveryType", pEffectSetting->properties.deliveryType);
					RegisterNumber(pFxVal, "castTime", pEffectSetting->properties.castingTime);
					RegisterNumber(pFxVal, "delayTime", pEffectSetting->properties.delayTime);
					RegisterNumber(pFxVal, "actorValue", pEffectSetting->properties.primaryValue);
					RegisterNumber(pFxVal, "magicType", pEffectSetting->properties.resistance);
				}
			}
			break;
		case kFormType_Shout:
			{
				TESShout * pShout = DYNAMIC_CAST(pForm, TESForm, TESShout);
				if(pShout)
				{
					if(pShout->fullName.name.data)
						RegisterString(pFxVal, movieView, "fullName", pShout->fullName.name.data);

					// Words
					GFxValue words;
					movieView->CreateArray(&words);
					for(int i = 0; i < pShout->Words::kNumWords; i++)
					{
						GFxValue word;
						movieView->CreateObject(&word);

						if(pShout->words[i].word && pShout->words[i].word->fullName.name.data)
							RegisterString(pFxVal, movieView, "fullName", pShout->words[i].word->fullName.name.data);

						RegisterNumber(&word, "recoveryTime", pShout->words[i].recoverytime);

						// Spell Object
						scaleformExtend::MagicItemData(&word, movieView, pShout->words[i].spell);
						words.PushBack(&words);
					}
					pFxVal->SetMember("words", &words);
				}
			}
			break;

		default:
			break;
		}
	}

	void ActorData(GFxValue * pFxVal,  GFxMovieView * movieView, TESForm * pForm)
	{
		if(!pForm || !pFxVal)
			return;

		switch(pForm->GetFormType())
		{
		case kFormType_Race:
			{
				TESRace * pRace = DYNAMIC_CAST(pForm, TESForm, TESRace);
				if(pRace)
				{
					if(pRace->fullName.name.data)
						RegisterString(pFxVal, movieView, "fullName", pRace->fullName.name.data);

					// Spells
					GFxValue spells;
					movieView->CreateArray(&spells);
					for(int i = 0; i < pRace->spellList.GetSpellCount(); i++)
					{
						GFxValue spell;
						movieView->CreateObject(&spell);
						scaleformExtend::MagicItemData(&spell, movieView, pRace->spellList.GetNthSpell(i));
						spells.PushBack(&spell);
					}
					pFxVal->SetMember("spells", &spells);

					// Shouts
					GFxValue shouts;
					movieView->CreateArray(&shouts);
					for(int i = 0; i < pRace->spellList.GetShoutCount(); i++)
					{
						GFxValue shout;
						movieView->CreateObject(&shout);
						scaleformExtend::MagicItemData(&shout, movieView, pRace->spellList.GetNthShout(i));
						shouts.PushBack(&shout);
					}
					pFxVal->SetMember("shouts", &shouts);
				}
			}
			break;
		case kFormType_NPC:
			{
				TESNPC * pNPC = DYNAMIC_CAST(pForm, TESForm, TESNPC);
				if(pNPC)
				{
					if(pNPC->fullName.name.data)
						RegisterString(pFxVal, movieView, "fullName", pNPC->fullName.name.data);
					if(pNPC->shortName.data)
						RegisterString(pFxVal, movieView, "shortName", pNPC->shortName.data);

					RegisterNumber(pFxVal, "weight", pNPC->weight);

					GFxValue race;
					movieView->CreateObject(&race);
					scaleformExtend::ActorData(&race, movieView, pNPC->race.race);
					pFxVal->SetMember("race", &race);

					// Spells
					GFxValue spells;
					movieView->CreateArray(&spells);
					for(int i = 0; i < pNPC->spellList.GetSpellCount(); i++)
					{
						GFxValue spell;
						movieView->CreateObject(&spell);
						scaleformExtend::MagicItemData(&spell, movieView, pNPC->spellList.GetNthSpell(i));
						spells.PushBack(&spell);
					}
					pFxVal->SetMember("spells", &spells);

					// Shouts
					GFxValue shouts;
					movieView->CreateArray(&shouts);
					for(int i = 0; i < pNPC->spellList.GetShoutCount(); i++)
					{
						GFxValue shout;
						movieView->CreateObject(&shout);
						scaleformExtend::MagicItemData(&shout, movieView, pNPC->spellList.GetNthShout(i));
						shouts.PushBack(&shout);
					}
					pFxVal->SetMember("shouts", &shouts);
				}
			}
			break;

		case kFormType_Character:
			{
				Actor * pActor = DYNAMIC_CAST(pForm, TESForm, Actor);
				if(pActor)
				{
					// ActorBase as Object
					GFxValue actorBase;
					movieView->CreateObject(&actorBase);

					scaleformExtend::ActorData(&actorBase, movieView, pActor->baseForm);
					pFxVal->SetMember("actorBase", &actorBase);

					// Spells as Array
					GFxValue addedSpells;
					movieView->CreateArray(&addedSpells);

					for(int i = 0; i < pActor->addedSpells.spellCount; i++)
					{
						GFxValue spell;
						movieView->CreateObject(&spell);
						scaleformExtend::MagicItemData(&spell, movieView, pActor->addedSpells.spells[i]);
						addedSpells.PushBack(&spell);
					}

					pFxVal->SetMember("spells", &addedSpells);

					// ActiveEffects as Array
					GFxValue activeEffects;
					movieView->CreateArray(&activeEffects);

					tList<ActiveEffect> * effects = pActor->magicTarget.GetActiveEffects();
					if(effects)
					{
						for(int i = 0; i < effects->Count(); i++)
						{
							GFxValue effect;
							movieView->CreateObject(&effect);

							ActiveEffect * pEffect = effects->GetNthItem(i);
							RegisterNumber(pFxVal, "elapsed", pEffect->elapsed);
							
							// ActiveEffect
							if(pEffect->effect && pEffect->effect->mgef)
								scaleformExtend::MagicItemData(pFxVal, movieView, pEffect->effect->mgef);
							
							activeEffects.PushBack(&effect);
						}
					}
					pFxVal->SetMember("activeEffects", &activeEffects);
				}
				PlayerCharacter* pPC = DYNAMIC_CAST(pForm, TESForm, PlayerCharacter);
				if(pPC)
				{
					RegisterNumber(pFxVal, "perkPoints", (double)pPC->numPerkPoints);
				}
			}
			break;

		default:
			break;
		}
	}

	void FormListData(GFxValue * pFxVal, GFxMovieView * movieView, TESForm * pForm)
	{
		if(!pForm || !pFxVal)
			return;

		switch(pForm->GetFormType())
		{
		case kFormType_List:
			{
				BGSListForm * formList = DYNAMIC_CAST(pForm, TESForm, BGSListForm);
				if(formList)
				{
					GFxValue formArray;
					movieView->CreateArray(&formArray);

					// Base Added Forms
					for(int i = 0; i < formList->forms.count; i++)
					{
						TESForm* childForm;
						if(formList->forms.GetNthItem(i, childForm))
						{
							GFxValue arrArg;
							movieView->CreateObject(&arrArg);
							scaleformExtend::FormData(&arrArg, movieView, childForm);
							formArray.PushBack(&arrArg);
						}
					}

					// Script Added Forms
					if(formList->addedForms) {
						for(int i = 0; i < formList->addedForms->count; i++)
						{
							UInt32 formid;
							formList->addedForms->GetNthItem(i, formid);
							TESForm* childForm = LookupFormByID(formid);
							if(childForm) {
								GFxValue arrArg;
								movieView->CreateObject(&arrArg);
								scaleformExtend::FormData(&arrArg, movieView, childForm);
								formArray.PushBack(&arrArg);
							}
						}
					}

					pFxVal->SetMember("forms", &formArray);
				}
			}
			break;
		default:
			break;
		}
	}

	// Convenience function, maybe combine all other functions into this one anyway?
	void FormData(GFxValue * pFxVal, GFxMovieView * movieView, TESForm * pForm)
	{
		if(!pForm || !pFxVal)
			return;

		scaleformExtend::CommonItemData(pFxVal, pForm);
		scaleformExtend::StandardItemData(pFxVal, pForm);
		scaleformExtend::MagicItemData(pFxVal, movieView, pForm);
		scaleformExtend::ActorData(pFxVal, movieView, pForm);
		scaleformExtend::FormListData(pFxVal, movieView, pForm);
	}

	void InventoryData(GFxValue * pFxVal, GFxMovieView * movieView, PlayerCharacter::ObjDesc * objDesc)
	{
		TESForm	* pForm = objDesc->form;

		if(!pForm || !pFxVal)
			return;

		PlayerCharacter	* pPC = *g_thePlayer;

		BGSKeywordForm	* keywords = DYNAMIC_CAST(pForm, TESForm, BGSKeywordForm);
		if(keywords)
			RegisterKeywords(pFxVal, movieView, keywords);

		switch(pForm->GetFormType())
		{
		case kFormType_Armor:
			{
				TESObjectARMO * pArmor = DYNAMIC_CAST(pForm, TESForm, TESObjectARMO);
				if(pArmor)
				{
					double armorValue = CALL_MEMBER_FN(pPC, GetArmorValue)(objDesc);
					armorValue = round(armorValue);
					RegisterNumber(pFxVal, "armor", armorValue);
				}
			}
			break;

		case kFormType_Weapon:
			{
				TESObjectWEAP * pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
				if(pWeapon)
				{
					double damage = CALL_MEMBER_FN(pPC, GetDamage)(objDesc);
					damage = round(damage);
					RegisterNumber(pFxVal, "damage", damage);
				}
			}
			break;

		case kFormType_Ammo:
			{
				TESAmmo * pAmmo = DYNAMIC_CAST(pForm, TESForm, TESAmmo);
				if(pAmmo)
				{
					double damage = CALL_MEMBER_FN(pPC, GetDamage)(objDesc);
					damage = round(damage);
					RegisterNumber(pFxVal, "damage", damage);
				}
			}
			break;

		default:
			break;
		}
	}
}