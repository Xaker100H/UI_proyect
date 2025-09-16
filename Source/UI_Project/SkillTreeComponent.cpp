#include "SkillTreeComponent.h"

USkillTreeComponent::USkillTreeComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USkillTreeComponent::BeginPlay()
{
    Super::BeginPlay();
        if (Skills.Num() == 0)
    {
        // Inicializa ejemplo de skills
        FSkillNode Skill1;
        Skill1.Name = "Dash";
        Skill1.Cost = 1;
        Skill1.State = ESkillState::Available;
        Skill1.RequiredNodeIndex = -1;

        FSkillNode Skill2;
        Skill2.Name = "Double Jump";
        Skill2.Cost = 2;
        Skill2.State = ESkillState::Locked;
        Skill2.RequiredNodeIndex = 0; // Depende de Skill1

        Skills.Add(Skill1);
        Skills.Add(Skill2);
    }
    // Las habilidades sin requisito se marcan como disponibles
    for (int i = 0; i < Skills.Num(); i++)
    {
        if (Skills[i].RequiredNodeIndex == -1)
        {
            Skills[i].State = ESkillState::Available;
        }
    }
}

bool USkillTreeComponent::CanUnlockSkill(int32 Index) const
{
    if (!Skills.IsValidIndex(Index)) return false;
    const FSkillNode& Node = Skills[Index];

    if (Node.State != ESkillState::Available) return false;
    if (PlayerPoints < Node.Cost) return false;

    return true;
}

bool USkillTreeComponent::UnlockSkill(int32 Index)
{
    if (!CanUnlockSkill(Index)) return false;

    FSkillNode& Node = Skills[Index];
    Node.State = ESkillState::Unlocked;
    PlayerPoints -= Node.Cost;

    // Hacer disponible la siguiente en la cadena
    for (int i = 0; i < Skills.Num(); i++)
    {
        if (Skills[i].RequiredNodeIndex == Index && Skills[i].State == ESkillState::Locked)
        {
            Skills[i].State = ESkillState::Available;
        }
    }
    return true;
}
