// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MediaPlayer.h"
#include "UEL_Tv.generated.h"

class UUEL_MediaPlayerWidget;

UCLASS()
class UELIVEVIDEOEXAMPLE_API AUEL_Tv : public AActor
{
	GENERATED_BODY()


	void StopPlaying();
	void Play();
	
	
public:
	
	
	// Sets default values for this actor's properties
	AUEL_Tv();

	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	UStaticMeshComponent* TV_Screen;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere)
	UMediaSource* MediaSource;

	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<UUEL_MediaPlayerWidget> MediaPlayerWidgetClass;

	UPROPERTY()
	UUEL_MediaPlayerWidget* MediaPlayerWidget;

	UFUNCTION(BlueprintCallable, Category=UI)
	void SetMediaPlayerWidgetVisibility(bool bVisible);

	UPROPERTY(BlueprintReadWrite)
	bool isTVOn;
	
	UPROPERTY(BlueprintReadWrite)
	bool isMediaPlaying;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetVideoCamera(AActor* OtherActor, AActor* ActorToFocus) const;

	UFUNCTION(BlueprintPure)
	APlayerController* GetControllerOfActor(const AActor* OtherActor) const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
