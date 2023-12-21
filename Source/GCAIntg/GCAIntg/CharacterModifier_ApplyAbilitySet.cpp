// Copyright (C) 2023 owoDra

#include "CharacterModifier_ApplyAbilitySet.h"

#include "GCAIntgLogs.h"

#include "GAEAbilitySystemComponent.h"

#include "AbilitySystemGlobals.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterModifier_ApplyAbilitySet)


void UCharacterModifier_ApplyAbilitySet::OnApply(APawn* Pawn) const
{
	check(Pawn);

	UE_LOG(LogGCAI, Log, TEXT("[%s] On Instance Apply(%s)"),
		Pawn->HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"), *GetNameSafe(this));

	const auto* World{ Pawn->GetWorld() };
	const auto bIsServer{ World->GetNetMode() != NM_Client };

	if (bIsServer)
	{
		if (auto* ASC{ UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Pawn) })
		{
			for (const auto& AbilitySet : AbilitySets)
			{
				UE_LOG(LogGCAI, Log, TEXT("++AbilitySet (Name: %s)"), *GetNameSafe(AbilitySet));

				AbilitySet->GiveToAbilitySystem(ASC, nullptr);
			}
		}
	}
}
