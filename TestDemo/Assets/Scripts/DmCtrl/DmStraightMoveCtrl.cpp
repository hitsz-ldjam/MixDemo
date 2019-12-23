#include "DmStraightMoveCtrl.h"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(DmStraightMoveCtrl, Script)

void DmStraightMoveCtrl::start() { }

void DmStraightMoveCtrl::update() {
    for(const auto& dm : dmList) {
        auto& trans = dm->transform();
        auto newPos = trans.getPosition() + trans.forward() * speed * Time::DeltaTime();
        trans.setPosition(newPos);
    }
}
