// Copyright (C) 2023 owoDra

#include "CharacterModifier_ApplyAbilitySet.h"

#include "GCAIntgLogs.h"

#include "GAEAbilitySystemComponent.h"

#include "AbilitySystemGlobals.h"

#include "GameFramework/Pawn.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterModifier_ApplyAbilitySet)


UCharacterModifier_ApplyAbilitySet::UCharacterModifier_ApplyAbilitySet()
{
	bOnlyApplyOnLocal = false;
	bApplyOnClient = false;
	bApplyOnServer = true;
}

bool UCharacterModifier_ApplyAbilitySet::OnApply(APawn* Pawn) const
{
	const auto bCanApply{ Super::OnApply(Pawn) };

	if (bCanApply)
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

	return bCanApply;
}
