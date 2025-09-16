#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeComponent.h"
#include "HabilityTreeWidget.generated.h"

class UVerticalBox;
class UTextBlock;
class USkillNodeWidget;

UCLASS()
class UI_PROJECT_API UHabilityTreeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** Referencia al componente del personaje */
    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
    USkillTreeComponent* SkillTreeComponent;
  
    UPROPERTY(EditDefaultsOnly, Category="SkillTree")
    TSubclassOf<USkillNodeWidget> SkillNodeWidgetClass;

    /** Inicializa la UI con las skills del componente */
    UFUNCTION(BlueprintCallable)
    void InitializeSkillTree(const TArray<FSkillNode>& Skills);

    /** Actualiza el texto de puntos de skill */
    UFUNCTION(BlueprintCallable)
    void UpdateSkillPoints();

protected:
    /** Contenedor donde se meterán los nodos */
    UPROPERTY(meta=(BindWidget))
    UVerticalBox* SkillList;

    /** Texto que mostrará los puntos */
    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* SkillPointsText;

    /** Maneja cuando se clickea un nodo */
    UFUNCTION()
    void OnSkillNodeClicked(int32 SkillIndex);
};
