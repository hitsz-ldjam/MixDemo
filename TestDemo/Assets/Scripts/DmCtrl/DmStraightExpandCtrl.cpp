#include "DmStraightExpandCtrl.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(DmStraightExpandCtrl, Script)

DmStraightExpandCtrl::DmStraightExpandCtrl(HDmPool _pool,
                                           const float _speedSlow,
                                           const float _speedExpand,
                                           const float _waitSec,
                                           const size_t _initCap)
    : speed(_speedSlow),
      speedExpand(_speedExpand),
      waitSec(_waitSec),
      pool(std::move(_pool)) {
    dmList.reserve(_initCap);
}

void DmStraightExpandCtrl::add(const HGameObject& _dm) {
    dmList.push_back(_dm);
}

void DmStraightExpandCtrl::clearAll() {
    for(const auto& dm : dmList)
        pool->destoryDm(dm);
}

void DmStraightExpandCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, HDmStraightExpandCtrl _this) {
        if(_this)
            yield_return(new Coroutine::WaitForSeconds(_this->waitSec));
        if(_this)
            _this->speed = _this->speedExpand;
    }, THIS_HANDLE);
}

void DmStraightExpandCtrl::update() {
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

void DmStraightExpandCtrl::lateUpdate() {}
