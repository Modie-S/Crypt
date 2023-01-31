// MaxiMod Games 2021
// Modie Shakarchi

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:

	UTriggerComponent();

protected:
	
	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMoverActive(UMover* Mover);

private:

	UPROPERTY(EditAnywhere)
	FName CorrectActorTag;

	UMover* Mover;

	AActor* GetCorrectActor() const;

};
