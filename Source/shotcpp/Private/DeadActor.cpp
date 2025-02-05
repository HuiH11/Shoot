// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadActor.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"

// Sets default values
ADeadActor::ADeadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f));
	BoxComp->SetCollisionProfileName(TEXT("Dead"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADeadActor::OnDeadOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADeadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeadActor::OnDeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if(player == nullptr)
	{
		OtherActor->Destroy();
	}

}

