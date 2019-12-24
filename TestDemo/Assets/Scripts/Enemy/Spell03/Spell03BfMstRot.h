#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class Spell03BfMstRot final : public Script {
MX_DECLARE_RTTI

public:
    Spell03BfMstRot() = default;
    ~Spell03BfMstRot() = default;

private:
    void start() override;
    void update() override;
};

using HSpell03BfMstRot = SceneObjectHandle<Spell03BfMstRot>;
