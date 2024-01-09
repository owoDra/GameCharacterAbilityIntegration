// Copyright (C) 2024 owoDra

#include "CharacterModifier_ApplyAbilitySet.h"

#include "GCAIntgLogs.h"

#include "GAEAbilitySystemComponent.h"
#include "AbilityTagRelationshipMapping.h"

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
			for (const auto& AbilitySetSoftObject : AbilitySets)
			{
				auto* AbilitySet
				{
					AbilitySetSoftObject.IsNull() ? nullptr :
					AbilitySetSoftObject.IsValid() ? AbilitySetSoftObject.Get() : AbilitySetSoftObject.LoadSynchronous()
				};

				UE_LOG(LogGCAI, Log, TEXT("++AbilitySet (Name: %s)"), *GetNameSafe(AbilitySet));

				AbilitySet->GiveToAbilitySystem(ASC, nullptr);
			}

			if (auto* GAEASC{ Cast<UGAEAbilitySystemComponent>(ASC) })
			{
				if (TagRelationshipMapping.IsNull())
				{
					const auto* LoadedTagRelationshipMapping
					{
						TagRelationshipMapping.IsValid() ? TagRelationshipMapping.Get() : TagRelationshipMapping.LoadSynchronous()
					};

					UE_LOG(LogGCAI, Log, TEXT("++TagRelationshipMapping (Name: %s)"), *GetNameSafe(LoadedTagRelationshipMapping));

					GAEASC->SetTagRelationshipMapping(LoadedTagRelationshipMapping);
				}
			}
		}
	}

	return bCanApply;
}
