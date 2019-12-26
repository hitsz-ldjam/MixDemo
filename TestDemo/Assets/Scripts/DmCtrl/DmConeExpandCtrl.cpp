#include "DmConeExpandCtrl.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(DmConeExpandCtrl, Script)

DmConeExpandCtrl::DmConeExpandCtrl(const float _speedSlow,
    const float _speedExpand,
    Vector3f _PlayerPos,
    const float _waitSec,
    const size_t _initCap) : speed(_speedSlow),
    speedExpand(_speedExpand),
    PlayerPos(_PlayerPos),
    waitSec(_waitSec) {
    dmList.reserve(_initCap);
}

void DmConeExpandCtrl::add(const HGameObject& _dm) {
    dmList.push_back(_dm);
}

void DmConeExpandCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, DmConeExpandCtrl* _this) {
        yield_return(new Coroutine::WaitForSeconds(_this->waitSec));
        _this->speed = 0;
        for (const auto& dm : _this->dmList) {
            auto& trans = dm->transform();
            trans.transform()->lookAt(_this->PlayerPos + Vector3f::Up);
        }
        //yield_return(new Coroutine::WaitForSeconds(0.2));
        _this->speed = _this->speedExpand;
        }, this);
}

    void DmConeExpandCtrl::update() {
        for (const auto& dm : dmList) {
            auto& trans = dm->transform();
            Vector3f pos = trans.getPosition() + trans.forward() * speed * Time::DeltaTime();
            trans.setPosition(pos);
        }
    }
