// Fill out your copyright notice in the Description page of Project Settings.

#include "Oldentide.h"
#include "myCharacter.h"


// Sets default values
AmyCharacter::AmyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AmyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AmyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AmyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

