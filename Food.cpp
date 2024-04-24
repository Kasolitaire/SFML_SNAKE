#include "Food.h"

bool Food::ToggleReverseModifier()
{
    m_reverseModifierEnable = !m_reverseModifierEnable;
    return m_reverseModifierEnable;
}

bool Food::ToggleSpeedModifier()
{
    m_speedModifierEnable = !m_speedModifierEnable;
    return m_speedModifierEnable;
}

void Food::SetFoodTexture()
{
}
