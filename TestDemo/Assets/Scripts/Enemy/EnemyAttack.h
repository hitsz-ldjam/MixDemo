#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class EnemyAttack final : public Script {
MX_DECLARE_RTTI

public:
    EnemyAttack() = default;
    ~EnemyAttack() = default;

private:
    void start() override;
    void update() override;
};

using HEnemyAttack = SceneObjectHandle<EnemyAttack>;
