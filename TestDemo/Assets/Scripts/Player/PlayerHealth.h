#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "BombCtrl.h"

using namespace Mix;

class PlayerHealth final : public Script {
MX_DECLARE_RTTI

public:
    PlayerHealth() = default;
    ~PlayerHealth() = default;

    PlayerHealth(const int _playerNum);

    // todo
    void miss();

    int getPlayerNum() const noexcept { return playerNum; }

private:
    void awake() override;
    void start() override;
    void update() override;

    //static constexpr int maxPlayerNum = 8;
    int playerNum;

    HBombCtrl bombCtrl;
    HAudioSource asrc;
};

using HPlayerHealth = SceneObjectHandle<PlayerHealth>;
