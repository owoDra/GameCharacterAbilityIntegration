// Copyright (C) 2024 owoDra

#pragma once

#include "Recipe/CharacterRecipe.h"

#include "AbilitySet.h"

#include "CharacterRecipe_AddAbilitySystemComponent.generated.h"

class UGAEAbilitySystemComponent;
class UAbilityTagRelationshipMapping;


/**
 * Modifier class to add ability system component to Pawn
 */
UCLASS()
class UCharacterRecipe_AddAbilitySystemComponent final : public UCharacterRecipe
{
	GENERATED_BODY()
public:
	UCharacterRecipe_AddAbilitySystemComponent();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AddAbilitySystemComponent")
	TSoftClassPtr<UGAEAbilitySystemComponent> ComponentClass{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "AddAbilitySystemComponent")
	TArray<TSoftObjectPtr<UAbilitySet>> AbilitySets;

	UPROPERTY(EditDefaultsOnly, Category = "AddAbilitySystemComponent")
	TSoftObjectPtr<const UAbilityTagRelationshipMapping> TagRelationshipMapping;

protected:
	virtual void StartSetupNonInstanced_Implementation(FCharacterRecipePawnInfo Info) const override;

};
