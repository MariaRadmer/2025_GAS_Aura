// Copyright Maria Radmer & Leah


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subSystem);
	subSystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI inputModedata;
	inputModedata.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModedata.SetHideCursorDuringCapture(false);
	SetInputMode(inputModedata);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInput->BindAction(moveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& inputActionValue)
{
	const FVector2D inputAxisVector = inputActionValue.Get<FVector2D>();
	const FRotator rotation = GetControlRotation();
	const FRotator YawRotation(0.f, rotation.Yaw, 0.f);

	const FVector forwardsDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* pawn = GetPawn<APawn>();

	if (pawn)
	{
		pawn->AddMovementInput(forwardsDirection, inputAxisVector.Y);
		pawn->AddMovementInput(rightDirection, inputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult cusorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, cusorHit);
	if (!cusorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = cusorHit.GetActor();

	if(LastActor == nullptr)
	{
		if(CurrentActor !=nullptr)
		{
			CurrentActor->HighlightActor();
		}
	} else
	{
		if(CurrentActor == nullptr)
		{
			LastActor->UnHighlightActor();
		} else
		{
			if(LastActor != CurrentActor)
			{
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			} 
		}
	}

	
}
