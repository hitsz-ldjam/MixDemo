#include "DmStraightMoveSingle.h"
#include "../../../../Mx/Component/Transform/MxTransform.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(DmStraightMoveSingle, Script)

void DmStraightMoveSingle::start() { }

void DmStraightMoveSingle::update() {
    transform()->translate(Vector3f(0, 0, speed * Time::DeltaTime()));
}
