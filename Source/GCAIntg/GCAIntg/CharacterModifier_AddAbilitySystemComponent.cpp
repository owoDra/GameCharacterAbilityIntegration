﻿// Copyright (C) 2023 owoDra

#include "CharacterModifier_AddAbilitySystemComponent.h"

#include "GCAIntgLogs.h"

#include "GAEAbilitySystemComponent.h"

#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterModifier_AddAbilitySystemComponent)


UCharacterModifier_AddAbilitySystemComponent::UCharacterModifier_AddAbilitySystemComponent()
{
	bOnlyApplyOnLocal = false;
	bApplyOnClient = false;
	bApplyOnServer = true;
}


bool UCharacterModifier_AddAbilitySystemComponent::OnApply(APawn* Pawn) const
{
	const auto bCanApply{ Super::OnApply(Pawn) };

	if (bCanApply)
	{
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

			UE_LOG(LogGCAI, Log, TEXT("+Component (Name: %s, Class: %s)"), *GetNameSafe(NewASC), *GetNameSafe(LoadedComponentClass));

			for (const auto& AbilitySet : AbilitySets)
			{
				UE_LOG(LogGCAI, Log, TEXT("++AbilitySet (Name: %s)"), *GetNameSafe(AbilitySet));

				AbilitySet->GiveToAbilitySystem(NewASC, nullptr);
			}
		}
	}

	return bCanApply;
}
