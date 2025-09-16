// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillTreeComponent.generated.h"

UENUM(BlueprintType)
enum class ESkillState : uint8
{
    Locked,
    Available,
    Unlocked
};

USTRUCT(BlueprintType)
struct FSkillNode
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    int32 Cost = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    int32 RequiredNodeIndex = -1; // -1 si no depende de otra

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    ESkillState State = ESkillState::Locked;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    FLinearColor ButtonColor = FLinearColor::White;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UI_PROJECT_API USkillTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillTreeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill Tree")
    TArray<FSkillNode> Skills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill Tree")
    int32 PlayerPoints = 5;



    UFUNCTION(BlueprintCallable, Category="Skill Tree")
    bool CanUnlockSkill(int32 Index) const;

    UFUNCTION(BlueprintCallable, Category="Skill Tree")
    bool UnlockSkill(int32 Index);
};
