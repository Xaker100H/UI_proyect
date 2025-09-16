#include "HabilityTreeWidget.h"
#include "SkillNodeWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UHabilityTreeWidget::InitializeSkillTree(const TArray<FSkillNode>& Skills)
{
    if (!SkillList) return;

    SkillList->ClearChildren();

     for (int32 i = 0; i < Skills.Num(); i++)
     {
        if (!SkillNodeWidgetClass) continue;

        USkillNodeWidget* Node = CreateWidget<USkillNodeWidget>(this, SkillNodeWidgetClass);
        if (Node)
        {
            Node->SetupNode(Skills[i], i);
            Node->OnNodeClicked.AddDynamic(this, &UHabilityTreeWidget::OnSkillNodeClicked);
            SkillList->AddChild(Node);
        }
     }



    UpdateSkillPoints();
}

void UHabilityTreeWidget::UpdateSkillPoints()
{
    if (SkillPointsText && SkillTreeComponent)
    {
        SkillPointsText->SetText(
            FText::FromString(FString::Printf(TEXT("Skill Points: %d"), SkillTreeComponent->PlayerPoints))
        );
    }
}

void UHabilityTreeWidget::OnSkillNodeClicked(int32 SkillIndex)
{
    if (!SkillTreeComponent) return;

    if (SkillTreeComponent->UnlockSkill(SkillIndex))
    {
        // Refrescar todo el árbol
        InitializeSkillTree(SkillTreeComponent->Skills);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("No se pudo desbloquear la skill"));
    }
}
