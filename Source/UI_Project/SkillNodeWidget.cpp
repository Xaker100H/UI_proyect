#include "SkillNodeWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USkillNodeWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (NodeButton)
    {
        NodeButton->OnClicked.AddDynamic(this, &USkillNodeWidget::HandleButtonClicked);
    }
}

void USkillNodeWidget::SetupNode(const FSkillNode& Data, int32 Index)
{
    SkillIndex = Index;

    if (SkillNameText)
    {
        FString StateText;
        switch (Data.State)
        {
        case ESkillState::Locked:    StateText = TEXT("(Locked)"); break;
        case ESkillState::Available: StateText = TEXT("(Available)"); break;
        case ESkillState::Unlocked:  StateText = TEXT("(Unlocked)"); break;
        default: StateText = TEXT(""); break;
        }

        const FString FullText = FString::Printf(TEXT("%s %s - Cost: %d"),
                                                 *Data.Name,
                                                 *StateText,
                                                 Data.Cost);
        SkillNameText->SetText(FText::FromString(FullText));
    }
     if (NodeButton)
     {
        // 👉 Siempre usa el color definido en el SkillTreeComponent
        NodeButton->WidgetStyle.Normal.TintColor  = FSlateColor(Data.ButtonColor);
        NodeButton->WidgetStyle.Hovered.TintColor = FSlateColor(Data.ButtonColor * 1.2f);
        NodeButton->WidgetStyle.Pressed.TintColor = FSlateColor(Data.ButtonColor * 0.8f);

        // El botón solo se desactiva si ya está desbloqueada
        NodeButton->SetIsEnabled(Data.State != ESkillState::Unlocked);
     }
        // 👉 Mensaje cuando se desbloquea la skill
    if (Data.State == ESkillState::Unlocked)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                FString::Printf(TEXT("¡Mejora %s conseguida!"), *Data.Name));
        }
    }

}

void USkillNodeWidget::RefreshFromComponent(USkillTreeComponent* Comp)
{
    if (!Comp || !Comp->Skills.IsValidIndex(SkillIndex)) return;
    const FSkillNode& Data = Comp->Skills[SkillIndex];
    SetupNode(Data, SkillIndex);
}

void USkillNodeWidget::HandleButtonClicked()
{
    OnNodeClicked.Broadcast(SkillIndex);
}
