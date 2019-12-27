#include "DmCurveExpandCtrl.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../Mx/Time/MxTime.h"
#include "../../../../Mx/GameObject/MxGameObject.h"

MX_IMPLEMENT_RTTI(DmCurveExpandCtrl, Script)

DmCurveExpandCtrl::DmCurveExpandCtrl(const float _speedSlow,
                                     const float _speedExpand,
                                     const float _waitSec,
                                     const size_t _initCap)
    : speed(_speedSlow),
      speedExpand(_speedExpand),
      waitSec(_waitSec) {
    dmList.reserve(_initCap);
}

void DmCurveExpandCtrl::add(const HGameObject& _dm) {
    dmList.push_back(_dm);
}

void DmCurveExpandCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, HDmCurveExpandCtrl _this) {
        if(_this)
            yield_return(new Coroutine::WaitForSeconds(_this->waitSec));
        if(_this)
            _this->speed = _this->speedExpand;
    }, THIS_HANDLE);

    //Coroutine::startCoroutine([](MX_YIELD_HANDLE, DmStraightExpandCtrl* _this) {
    //    // bug prone
    //    while(true) {
    //        auto i = 0;
    //        for(const auto& dm : _this->dmList) {
    //            auto& trans = dm->transform();
    //            auto newPos = trans.getPosition() + trans.forward() * _this->speed * Time::DeltaTime();
    //            trans.setPosition(newPos);
    //            if(++i == _this->dmList.size() / 9) {
    //                i = 0;
    //                yield_return(nullptr);
    //            }
    //        }
    //    }
    //}, this);
}

void DmCurveExpandCtrl::update() {
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
