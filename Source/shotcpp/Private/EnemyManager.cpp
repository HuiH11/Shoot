// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Components/ArrowComponent.h"
#include "EnemyActor.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(RootComp);
	ArrowComp->SetRelativeRotation(FRotator(-90.0f, 180.0f, 0.0f));
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurTime += DeltaTime;
	if(CurTime>MakeTime)
	{
		MakeEnemy();
	}
}

void AEnemyManager::MakeEnemy()
{
	GetWorld()->SpawnActor<class AEnemyActor>(EnemyFactory, ArrowComp->GetComponentTransform());
	CurTime = 0.0f;
}

