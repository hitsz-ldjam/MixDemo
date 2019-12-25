#include "Spell03BfMstRot.h"
#include "../../../../../Mx/Component/Transform/MxTransform.h"
#include "../../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(Spell03BfMstRot, Script)

Spell03BfMstRot::Spell03BfMstRot(const float _rotSpeed,
                                 const Vector3f& _rotAxis) : rotSpeed(_rotSpeed),
                                                             rotAxis(_rotAxis) {}

void Spell03BfMstRot::start() { }

void Spell03BfMstRot::update() {
    transform()->rotate(rotAxis, rotSpeed * Time::DeltaTime());
}
