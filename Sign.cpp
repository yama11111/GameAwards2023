#include "Sign.h"

Sign::Sign(const Vector2& mapchipSize)
{
    for (int y{}; y < (int)mapchipSize.y_; y++) {
        mapchip_.emplace_back(std::vector<std::unique_ptr<IBlock>>{});
        for (int x{}; x < (int)mapchipSize.y_; x++) {
            mapchip_.emplace_back(new IBlock);
        }
    }
}

void Sign::Update(void)
{

}

void Sign::Draw(void)
{
}

void Sign::PPC(YukiMapchipCollider* ptr)
{
    
}
