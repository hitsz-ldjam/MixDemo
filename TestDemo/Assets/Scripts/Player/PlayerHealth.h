#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class PlayerHealth final : public Script {
MX_DECLARE_RTTI

public:
    PlayerHealth() = default;
    ~PlayerHealth() = default;

    PlayerHealth(HAudioSource _asrc);

    void miss();

private:
    void start() override;
    void update() override;

    HAudioSource asrc;
};

using HPlayerHealth = SceneObjectHandle<PlayerHealth>;
