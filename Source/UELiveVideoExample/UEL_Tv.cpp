// Fill out your copyright notice in the Description page of Project Settings.


#include "UEL_Tv.h"

#include "UEL_MediaPlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AUEL_Tv::AUEL_Tv()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	
	TV_Screen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TV Actor"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	BoxCollision->SetBoxExtent(FVector(250,250,250));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AUEL_Tv::OnBoxBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AUEL_Tv::OnBoxEndOverlap);
	
	TV_Screen->SetupAttachment(RootComponent);
	BoxCollision->SetupAttachment(RootComponent);

	isTVOn = false;
	isMediaPlaying = false;

}

void AUEL_Tv::SetMediaPlayerWidgetVisibility(bool bVisible)
{
	if (MediaPlayerWidget == nullptr)
	{
		MediaPlayerWidget = CreateWidget<UUEL_MediaPlayerWidget>(GetWorld(), MediaPlayerWidgetClass);
	}

	if (MediaPlayerWidget)
	{
		MediaPlayerWidget->MediaPlayer = MediaPlayer;
		if (bVisible)
		{
			MediaPlayerWidget->AddToViewport();
		}
		else
		{
			MediaPlayerWidget->RemoveFromParent();
		}
	}
}

// Called when the game starts or when spawned
void AUEL_Tv::BeginPlay()
{
	Super::BeginPlay();
}

void AUEL_Tv::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("Logged in"));

	if (MediaPlayer)
	{
		Play();
		
		if (!isTVOn)
		{
			MediaPlayer->OpenSource(MediaSource);
			isTVOn = true;
		}
		
		SetVideoCamera(OtherActor, this);
	}
}

void AUEL_Tv::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (isMediaPlaying)
	{
		StopPlaying();
		SetVideoCamera(OtherActor, OtherActor);
	}
	
}

void AUEL_Tv::SetVideoCamera(AActor* OtherActor, AActor* ActorToFocus) const
{
	APlayerController* PlayerController = GetControllerOfActor(OtherActor);
	if (!PlayerController)
	{
		return;
	}
	PlayerController->SetViewTargetWithBlend(ActorToFocus, 0.5);
}

APlayerController* AUEL_Tv::GetControllerOfActor(const AActor* OtherActor) const
{
	const APawn* Pawn = Cast<APawn>(OtherActor);
	if (!IsValid(Pawn))
	{
		return nullptr;
	}
	
	return Cast<APlayerController>(Pawn->GetController());
}

// Called every frame
void AUEL_Tv::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUEL_Tv::StopPlaying()
{
	MediaPlayer->Pause();
	isMediaPlaying = false;
}

void AUEL_Tv::Play()
{
	MediaPlayer->Play();
	isMediaPlaying = true;
}

