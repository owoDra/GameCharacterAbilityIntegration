﻿// Copyright (C) 2024 owoDra

#include "CharacterRecipe_AddAbilitySystemComponent.h"

#include "GAEAbilitySystemComponent.h"
#include "AbilityTagRelationshipMapping.h"

#include "CharacterInitStateComponent.h"
#include "GCExtLogs.h"

#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterRecipe_AddAbilitySystemComponent)


UCharacterRecipe_AddAbilitySystemComponent::UCharacterRecipe_AddAbilitySystemComponent()
{
	InstancingPolicy = ECharacterRecipeInstancingPolicy::NonInstanced;
	NetExecutionPolicy = ECharacterRecipeNetExecutionPolicy::ServerOnly;

#if WITH_EDITOR
	StaticClass()->FindPropertyByName(FName{ TEXTVIEW("InstancingPolicy") })->SetPropertyFlags(CPF_DisableEditOnTemplate);
	StaticClass()->FindPropertyByName(FName{ TEXTVIEW("NetExecutionPolicy") })->SetPropertyFlags(CPF_DisableEditOnTemplate);
#endif
}


void UCharacterRecipe_AddAbilitySystemComponent::StartSetupNonInstanced_Implementation(FCharacterRecipePawnInfo Info) const
{
	auto* Pawn{ Info.Pawn.Get() };

	auto* LoadedComponentClass
	{
		ComponentClass.IsNull() ? nullptr :
		ComponentClass.IsValid() ? ComponentClass.Get() : ComponentClass.LoadSynchronous()
	};

	if (LoadedComponentClass)
	{
		auto* NewASC{ NewObject<UGAEAbilitySystemComponent>(Pawn, LoadedComponentClass) };
		NewASC->RegisterComponent();
		NewASC->InitAbilityActorInfo(Pawn, Pawn);

		UE_LOG(LogGameExt_CharacterRecipe, Log, TEXT("+Component (Name: %s, Class: %s)"), *GetNameSafe(NewASC), *GetNameSafe(LoadedComponentClass));

		for (const auto& AbilitySetSoftObject : AbilitySets)
		{
			auto* AbilitySet
			{
				AbilitySetSoftObject.IsNull() ? nullptr :
				AbilitySetSoftObject.IsValid() ? AbilitySetSoftObject.Get() : AbilitySetSoftObject.LoadSynchronous()
			};

			UE_LOG(LogGameExt_CharacterRecipe, Log, TEXT("++AbilitySet (Name: %s)"), *GetNameSafe(AbilitySet));

			AbilitySet->GiveToAbilitySystem(NewASC, nullptr);
		}

		if (TagRelationshipMapping.IsNull())
		{
			const auto* LoadedTagRelationshipMapping
			{
				TagRelationshipMapping.IsValid() ? TagRelationshipMapping.Get() : TagRelationshipMapping.LoadSynchronous()
			};

			UE_LOG(LogGameExt_CharacterRecipe, Log, TEXT("++TagRelationshipMapping (Name: %s)"), *GetNameSafe(LoadedTagRelationshipMapping));

			NewASC->SetTagRelationshipMapping(LoadedTagRelationshipMapping);
		}
	}
}
