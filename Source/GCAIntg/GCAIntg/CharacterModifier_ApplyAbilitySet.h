// Copyright (C) 2023 owoDra

#pragma once

#include "CharacterModifier.h"

#include "AbilitySet.h"

#include "CharacterModifier_ApplyAbilitySet.generated.h"


/**
 * Modifier class to add ability system component to Pawn
 */
UCLASS(meta = (DisplayName = "CM Add Ability System Component"))
class UCharacterModifier_ApplyAbilitySet final : public UCharacterModifier
{
	GENERATED_BODY()
public:
	UCharacterModifier_ApplyAbilitySet() {}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TSoftClassPtr<UGAEAbilitySystemComponent> ComponentClass{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TArray<TObjectPtr<UAbilitySet>> AbilitySets;

protected:
	virtual void OnApply(APawn* Pawn) const override;

};
