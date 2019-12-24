#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class Spell03BfMstCtrl final : public Script {
MX_DECLARE_RTTI

public:
    Spell03BfMstCtrl() = default;
    ~Spell03BfMstCtrl() = default;

private:
    void start() override;
    void update() override;
};

using HSpell03BfMstCtrl = SceneObjectHandle<Spell03BfMstCtrl>;
