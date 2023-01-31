// MaxiMod Games 2021
// Modie Shakarchi

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	
	UGrabber();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Grab();

private:

	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400.f;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100.f;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
		
};
