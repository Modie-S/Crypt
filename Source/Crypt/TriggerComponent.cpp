// MaxiMod Games 2021
// Modie Shakarchi


#include "TriggerComponent.h"



UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetCorrectActor();
	if (Actor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}


void UTriggerComponent::SetMoverActive(UMover* ActiveMover)
{
	Mover = ActiveMover;
}


AActor* UTriggerComponent::GetCorrectActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		bool HasCorrectTag = Actor->ActorHasTag(CorrectActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasCorrectTag && !IsGrabbed)
		{
			return Actor;
		}
	}

	return nullptr;
}