// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f));
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	int32 randVal = FMath::RandRange(1, 100);

	auto* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(player != nullptr)
	{
		if(randVal <= rate)
		{
			dir = player->GetActorLocation() - GetActorLocation();
			FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation());
			SetActorRotation(PlayerRot);
		}
		else dir = GetActorForwardVector();
	}
	else dir = GetActorForwardVector();
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + dir.GetSafeNormal() * speed * DeltaTime);
}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if(player != nullptr)
	{
		player->Destroy();
	}
	Destroy();
}

