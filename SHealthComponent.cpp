// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
    DefaultHealth = 100.f;
    bDied = false;
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    AActor* MyOwner = GetOwner();
    if(MyOwner)
    {
        //Apply Damage to the player
        MyOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::HandleTakeAnyDamage);
    }
    
    Health = DefaultHealth;
	
}

//function to handle OnTakeAnyDamage event.
void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if(Damage <= 0)
    {
        return;
    }
    
    // Update health clamped
    Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
    
    UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));
    
    OnHealthChanged.Broadcast(this, Health, Damage,DamageType, InstigatedBy, DamageCauser);
}

//Get Current Health
float USHealthComponent::GetHealth() const
{
    return Health;
}
