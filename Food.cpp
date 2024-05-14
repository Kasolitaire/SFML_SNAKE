#include "Food.h"
#include <random>

Food::Food(const Vector2f& size, const Vector2f& position)
{
    m_food.setSize(size);
    SetFoodPosition(position);
}

bool Food::ToggleReverseModifier()
{
    m_reverseModifierEnable = !m_reverseModifierEnable;
    cout << "reverse modifier: " << m_reverseModifierEnable << endl;
    return m_reverseModifierEnable;
}

bool Food::ToggleSpeedModifier() 
{
    m_speedModifierEnable = !m_speedModifierEnable;
    cout << "speed modifier: " << m_speedModifierEnable << endl;
    return m_speedModifierEnable;
}

void Food::SetFoodTexture(const string& filename)
{
    m_food.setTexture(&(AssetManager::GetTexture(filename)));
}

void Food::SetRandomFoodType()
{
    random_device rd;
    uniform_int_distribution<int> dist(0 ,2);
    FoodType randomFoodType = static_cast<FoodType>(dist(rd));
    m_currentFoodType = randomFoodType;
}

void Food::SetFoodPosition(const Vector2f& position)
{
    m_food.setPosition(position);
}

Vector2f Food::GetFoodPosition()
{
    return m_food.getPosition();
}

FoodType Food::GetCurrentFoodType()
{
    return m_currentFoodType;
}

void Food::DrawFood(RenderWindow& r_renderWindow)
{
    r_renderWindow.draw(m_food);
}