#include "CameraCtrl.h"
#include "../../../../Mx/GameObject/MxGameObject.h"

MX_IMPLEMENT_RTTI(CameraCtrl, Script)

CameraCtrl::CameraCtrl(HGameObject _target) : target(std::move(_target)) {}

void CameraCtrl::start() {
    //auto focusTarget = target->transform().getPosition();
    auto focusTarget = Vector3f(0, 0, 20);
    transform()->setPosition({20, 14, -10});
    transform()->setRotation(Quaternion::LookRotation(focusTarget - transform()->getPosition(),
                                                      transform()->up()));
}

void CameraCtrl::update() { }
