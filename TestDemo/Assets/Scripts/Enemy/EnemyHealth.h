#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class EnemyHealth final : public Script {
MX_DECLARE_RTTI

public:
    EnemyHealth() = default;
    ~EnemyHealth() = default;

private:
    void start() override;
    void update() override;
};

using HEnemyHealth = SceneObjectHandle<EnemyHealth>;
