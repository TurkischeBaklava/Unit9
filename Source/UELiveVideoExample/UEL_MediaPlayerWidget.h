// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MediaPlayer.h"
#include "Blueprint/UserWidget.h"
#include "UEL_MediaPlayerWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UELIVEVIDEOEXAMPLE_API UUEL_MediaPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	UMediaPlayer* MediaPlayer;
	
	
};
