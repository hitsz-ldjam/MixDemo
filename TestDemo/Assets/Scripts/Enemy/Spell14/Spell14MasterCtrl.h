#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../Utils/DmPool.h"

using namespace Mix;

class Spell14MasterCtrl final : public Script {
    MX_DECLARE_RTTI

public:
    Spell14MasterCtrl() = default;
    ~Spell14MasterCtrl() = default;

    Spell14MasterCtrl(HGameObject _player,
        HGameObject _enemy,
        HDmPool _pool,
        HDmPool _spool);

    void setShootTimes(unsigned int _ShootTimes);
    void setShootCone(unsigned int _ShootCone);

private:
    void start() override;
    void update() override;

    void shootConeImpl1();
    void shootConeImpl2();

    unsigned int ShootTimes = 10;
    unsigned int ShootCone = 1;

    HGameObject enemy;
    HGameObject player;
    HDmPool bigballPool;
    HDmPool ballPool;
};

using HSpell14MasterCtrl = SceneObjectHandle<Spell14MasterCtrl>;
