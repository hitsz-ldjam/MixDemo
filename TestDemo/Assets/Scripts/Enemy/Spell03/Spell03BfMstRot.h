#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../../../../Mx/Math/MxVector3.h"

using namespace Mix;

class Spell03BfMstRot final : public Script {
MX_DECLARE_RTTI

public:
    Spell03BfMstRot() = default;
    ~Spell03BfMstRot() = default;

    Spell03BfMstRot(const float _rotSpeed, const Vector3f& _rotAxis);

private:
    void start() override;
    void update() override;

    float rotSpeed;
    Vector3f rotAxis;
};

using HSpell03BfMstRot = SceneObjectHandle<Spell03BfMstRot>;
