// Copyright (C) 2024 owoDra

#pragma once

#include "Recipe/CharacterRecipe.h"

#include "AbilitySet.h"

#include "CharacterRecipe_ApplyAbilitySet.generated.h"


/**
 * Modifier class to add ability system component to Pawn
 */
UCLASS()
class UCharacterRecipe_ApplyAbilitySet final : public UCharacterRecipe
{
	GENERATED_BODY()
public:
	UCharacterRecipe_ApplyAbilitySet();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ApplyAbilitySet")
	TArray<TSoftObjectPtr<UAbilitySet>> AbilitySets;

	UPROPERTY(EditDefaultsOnly, Category = "AddAbilitySystemComponent")
	TSoftObjectPtr<const UAbilityTagRelationshipMapping> TagRelationshipMapping;

protected:
	virtual void StartSetupNonInstanced_Implementation(FCharacterRecipePawnInfo Info) const override;

};
