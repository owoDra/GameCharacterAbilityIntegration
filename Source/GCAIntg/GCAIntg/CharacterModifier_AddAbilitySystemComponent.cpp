// Copyright (C) 2023 owoDra

#include "CharacterModifier_AddAbilitySystemComponent.h"

#include "GCAIntgLogs.h"

#include "GAEAbilitySystemComponent.h"

#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterModifier_AddAbilitySystemComponent)


void UCharacterModifier_AddAbilitySystemComponent::OnApply(APawn* Pawn) const
{
	check(Pawn);

	UE_LOG(LogGCAI, Log, TEXT("[%s] On Instance Apply(%s)"),
		Pawn->HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"), *GetNameSafe(this));

	const auto* World{ Pawn->GetWorld() };
	const auto bIsServer{ World->GetNetMode() != NM_Client };

	UE_LOG(LogGCAI, Log, TEXT("Adding components for %s to world %s"), *GetPathNameSafe(Pawn), *World->GetDebugDisplayName());

	if (bIsServer)
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
}
