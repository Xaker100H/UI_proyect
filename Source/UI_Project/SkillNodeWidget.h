#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeComponent.h"
#include "SkillNodeWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillNodeClicked, int32, SkillIndex);

UCLASS()
class UI_PROJECT_API USkillNodeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill", meta=(ExposeOnSpawn="true"))
    int32 SkillIndex = -1;

    
    UFUNCTION(BlueprintCallable, Category="Skill")
    void SetupNode(const FSkillNode& Data, int32 Index);

    void RefreshFromComponent(class USkillTreeComponent* Comp);

    UPROPERTY(BlueprintAssignable, Category="Skill")
    FOnSkillNodeClicked OnNodeClicked;


protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta=(BindWidget)) class UButton* NodeButton;
    UPROPERTY(meta=(BindWidget)) class UTextBlock* SkillNameText;


private:
    UFUNCTION() void HandleButtonClicked();
};
