﻿// Copyright (C) 2024 owoDra

#include "CharacterRecipe_ApplyAbilitySet.h"

#include "GAEAbilitySystemComponent.h"
#include "AbilityTagRelationshipMapping.h"

#include "CharacterInitStateComponent.h"
#include "GCExtLogs.h"

#include "AbilitySystemGlobals.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterRecipe_ApplyAbilitySet)


UCharacterRecipe_ApplyAbilitySet::UCharacterRecipe_ApplyAbilitySet()
{
	InstancingPolicy = ECharacterRecipeInstancingPolicy::NonInstanced;
	NetExecutionPolicy = ECharacterRecipeNetExecutionPolicy::ServerOnly;

#if WITH_EDITOR
	StaticClass()->FindPropertyByName(FName{ TEXTVIEW("InstancingPolicy") })->SetPropertyFlags(CPF_DisableEditOnTemplate);
	StaticClass()->FindPropertyByName(FName{ TEXTVIEW("NetExecutionPolicy") })->SetPropertyFlags(CPF_DisableEditOnTemplate);
#endif
}


void UCharacterRecipe_ApplyAbilitySet::StartSetupNonInstanced_Implementation(FCharacterRecipePawnInfo Info) const
{
	auto* Pawn{ Info.Pawn.Get() };

	if (auto* ASC{ UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Pawn) })
	{
		for (const auto& AbilitySetSoftObject : AbilitySets)
		{
			auto* AbilitySet
			{
				AbilitySetSoftObject.IsNull() ? nullptr :
				AbilitySetSoftObject.IsValid() ? AbilitySetSoftObject.Get() : AbilitySetSoftObject.LoadSynchronous()
			};

			UE_LOG(LogGameExt_CharacterRecipe, Log, TEXT("++AbilitySet (Name: %s)"), *GetNameSafe(AbilitySet));

			AbilitySet->GiveToAbilitySystem(ASC, nullptr);
		}

		if (auto* GAEASC{ Cast<UGAEAbilitySystemComponent>(ASC) })
		{
			if (!TagRelationshipMapping.IsNull())
			{
				const auto* LoadedTagRelationshipMapping
				{
					TagRelationshipMapping.IsValid() ? TagRelationshipMapping.Get() : TagRelationshipMapping.LoadSynchronous()
				};

				UE_LOG(LogGameExt_CharacterRecipe, Log, TEXT("++TagRelationshipMapping (Name: %s)"), *GetNameSafe(LoadedTagRelationshipMapping));

				GAEASC->SetTagRelationshipMapping(LoadedTagRelationshipMapping);
			}
		}
	}
}
