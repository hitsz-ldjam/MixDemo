#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../Utils/DmPool.h"

using namespace Mix;

class Spell06MasterCtrl final : public Script {
MX_DECLARE_RTTI

public:
    Spell06MasterCtrl() = default;
    ~Spell06MasterCtrl() = default;

    Spell06MasterCtrl(HDmPool _bfPool);

    void forceClearDm();

private:
    void start() override;
    void update() override;

    void shootBlueSphereImpl();
    void shootPurpleSphereImpl();
    void shootRedSphereImpl();

    HDmPool bfPool;
    std::vector<HGameObject> ctrls;
};

using HSpell06MasterCtrl = SceneObjectHandle<Spell06MasterCtrl>;
