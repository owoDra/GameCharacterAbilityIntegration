// Copyright (C) 2023 owoDra

#pragma once

#include "CharacterModifier.h"

#include "AbilitySet.h"

#include "CharacterModifier_ApplyAbilitySet.generated.h"


/**
 * Modifier class to add ability system component to Pawn
 */
UCLASS(meta = (DisplayName = "CM Apply Ability Set"))
class UCharacterModifier_ApplyAbilitySet final : public UCharacterModifier
{
	GENERATED_BODY()
public:
	UCharacterModifier_ApplyAbilitySet();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ApplyAbilitySet")
	TArray<TObjectPtr<UAbilitySet>> AbilitySets;

protected:
	virtual bool OnApply(APawn* Pawn) const override;

};
