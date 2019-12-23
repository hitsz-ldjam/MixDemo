#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../Utils/DmPool.h"

using namespace Mix;

class Spell06MasterCtrl final : public Script {
MX_DECLARE_RTTI

public:
    Spell06MasterCtrl() = default;
    ~Spell06MasterCtrl() = default;

    Spell06MasterCtrl(HDmPool _bigballPool);

private:
    void start() override;
    void update() override;

    void shootBlueSphereImpl();

    HDmPool bigballPool;
};

using HSpell06MasterCtrl = SceneObjectHandle<Spell06MasterCtrl>;
