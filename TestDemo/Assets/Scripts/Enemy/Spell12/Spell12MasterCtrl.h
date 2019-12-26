#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../Utils/DmPool.h"

using namespace Mix;

class Spell12MasterCtrl final : public Script {
    MX_DECLARE_RTTI

public:
    Spell12MasterCtrl() = default;
    ~Spell12MasterCtrl() = default;

    Spell12MasterCtrl(HGameObject _player,
        HDmPool _pool,
        HDmPool _spool);

    void setShootTimes(unsigned int _ShootTimes);
    void setShootCone(unsigned int _ShootCone);

private:
    void start() override;
    void update() override;

    void shootConeImpl();

    unsigned int ShootTimes = 3;
    unsigned int ShootCone = 30;

    HGameObject player;
    HDmPool bigballPool;
    HDmPool ballPool;
};

using HSpell12MasterCtrl = SceneObjectHandle<Spell12MasterCtrl>;
