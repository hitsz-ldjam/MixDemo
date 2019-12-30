#include "DmStraightMoveCtrl.h"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(DmStraightMoveCtrl, Script)

void DmStraightMoveCtrl::add(const HGameObject& _dm) {
    dmList.push_back(_dm);
}

void DmStraightMoveCtrl::clearAll() {
    for(const auto& dm : dmList)
        pool->destoryDm(dm);
}

void DmStraightMoveCtrl::update() {
    for(auto i = 0u; i < dmList.size();) {
        auto& dm = dmList[i];
        if(dm->getName() == "_-_") {
            dm = dmList.back(); // todo: Is self assigning safe?
            dmList.erase(dmList.end() - 1);
            continue;
        }
        auto& trans = dm->transform();
        auto newPos = trans.getPosition() + trans.forward() * speed * Time::DeltaTime();
        trans.setPosition(newPos);
        ++i;
    }
}
