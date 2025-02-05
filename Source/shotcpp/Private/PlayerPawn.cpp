// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BulletActor.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f));
	BoxComp->SetCollisionProfileName(TEXT("Player"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(RootComponent);
	FirePosition->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 100.0f), FRotator(90.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = FVector(0.0f, h, v);
	dir.Normalize();

	SetActorLocation(GetActorLocation() + dir * speed * DeltaTime, true);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Hori"), this, &APlayerPawn::OnHori);
	PlayerInputComponent->BindAxis(TEXT("Verti"), this, &APlayerPawn::OnVerti);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnFire);
}

void APlayerPawn::OnHori(float val)
{
	h = val;
}

void APlayerPawn::OnVerti(float val)
{
	v = val;
}

void APlayerPawn::OnFire()
{
	GetWorld()->SpawnActor<class ABulletActor>(BulletFactory, FirePosition->GetComponentTransform());
}

