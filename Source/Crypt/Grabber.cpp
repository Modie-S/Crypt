// MaxiMod Games 2021
// Modie Shakarchi



#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



UGrabber::UGrabber()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	
}



void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
	
}



void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor::Red
	);

	DrawDebugSphere(
		GetWorld(),
		End,
		10.f,
		10,
		FColor::Blue,
		false,
		5
	);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);	
	return GetWorld()->SweepSingleByChannel(
						OutHitResult,
						Start,
						End,
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel2,
						Sphere
						);
}


void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) return;

	FHitResult HitResult;
	bool ConfirmHit = GetGrabbableInReach(HitResult);
	if (ConfirmHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitResult.GetActor()->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}


void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}