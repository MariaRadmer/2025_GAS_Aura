// Copyright Maria Radmer & Leah


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"



AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* playerState = GetPlayerState<AAuraPlayerState>();
	if (!playerState)
	{
	    UE_LOG(LogTemp, Error, TEXT("PlayerState is NULL"));
		return; 
	}
	AbilitySystemComponent = playerState->GetAbilitySystemComponent();
	AttributeSet = playerState->GetUAttributeSet();

	playerState->GetAbilitySystemComponent()->InitAbilityActorInfo(playerState,this);
	
}


