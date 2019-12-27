#pragma once
#include "../Utils/DmPool.h"
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

// add this to player
class BombCtrl final : public Script {
public:
    BombCtrl() = default;
    ~BombCtrl() = default;

    BombCtrl(HDmPool _pool);

    int getBombNum();

    void resumeBomb();

private:
    void update() override;

    HDmPool pool;

    static constexpr float bombTime = 5;
    float bombTimeCnt;

    static constexpr int maxBombNum = 3;
    int bombCnt;

    constexpr static float maxRadius = 3,
                           expandTime = 0.5,
                           forwardSpeed = 30,
                           waitTime = 0,
                           waitTimeStep = 0.2;
};

using HBombCtrl = SceneObjectHandle<BombCtrl>;
