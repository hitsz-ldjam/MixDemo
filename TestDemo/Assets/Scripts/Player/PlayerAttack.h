#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class PlayerAttack final : public Script {
MX_DECLARE_RTTI

public:
    PlayerAttack() = default;
    ~PlayerAttack() = default;

private:
    void start() override;
    void update() override;
};

using HPlayerAttack = SceneObjectHandle<PlayerAttack>;
