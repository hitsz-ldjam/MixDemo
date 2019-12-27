#include "PlayerAttack.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(PlayerAttack, Script)

PlayerAttack::PlayerAttack(HEnemyHealth _eh) : eh(std::move(_eh)) {}

void PlayerAttack::start() { }

void PlayerAttack::update() {
    // todo
    // magic
    static constexpr float dps = 45;
    eh->dealDamage(45 * Time::DeltaTime());
}
