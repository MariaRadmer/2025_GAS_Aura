// Copyright Maria Radmer & Leah

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"

#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface

{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetUAttributeSet() const {return AttributeSet;}

protected:
	UPROPERTY(BlueprintReadOnly,Category="Abilities");
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="Abilities");
	TObjectPtr<UAttributeSet> AttributeSet;

};
