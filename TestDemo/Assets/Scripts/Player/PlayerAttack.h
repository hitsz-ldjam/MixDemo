#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../Enemy/EnemyHealth.h"

using namespace Mix;

class PlayerAttack final : public Script {
MX_DECLARE_RTTI

public:
    PlayerAttack() = default;
    ~PlayerAttack() = default;

    PlayerAttack(HEnemyHealth _eh);

private:
    void start() override;
    void update() override;

    HEnemyHealth eh;
};

using HPlayerAttack = SceneObjectHandle<PlayerAttack>;
