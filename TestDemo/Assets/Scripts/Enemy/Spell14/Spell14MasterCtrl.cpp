#include "Spell14MasterCtrl.h"
#include "../../Prefabs/Prefab.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../Utils/ShootCone.h"
#include "../../Utils/ShootRound.h"
#include "../../Utils/ShootSphere.h"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../DmCtrl/DmStraightMoveCtrl.h"
#include "../../DmCtrl/DmStraightExpandCtrl.h"
#include "../../DmCtrl/DmConeExpandCtrl.h"

MX_IMPLEMENT_RTTI(Spell14MasterCtrl, Script)

Spell14MasterCtrl::Spell14MasterCtrl(HGameObject _player,
    HGameObject _enemy,
    HDmPool _bigballPool,
    HDmPool _ballPool)
    : player(std::move(_player)),
    enemy(std::move(_enemy)),
    bigballPool(std::move(_bigballPool)),
    ballPool(std::move(_ballPool)) {}

void Spell14MasterCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, Spell14MasterCtrl* _this) {
        for (int j = 0; j < _this->ShootTimes; j++) {
            for (int i = 0 ; i < _this->ShootCone; i++) {
                _this->shootConeImpl1();
                yield_return(new Coroutine::WaitForSeconds(.2));
                _this->shootConeImpl2();
                yield_return(new Coroutine::WaitForSeconds(.2));
            }
            auto ctrl = GameObject::Instantiate("BlueSphereMasterCtrl");
            auto ec = ctrl->addComponent<DmStraightMoveCtrl>(8);

            ShootSphere::Shoot(ShootSphere::SphereType::Verts_42,
                _this->bigballPool,
                _this->transform()->getPosition(),
                _this->transform()->getRotation(),
                [&ec = ec](const HGameObject& _dm) {
                    _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                    ec->add(_dm);
                });
                
            yield_return(new Coroutine::WaitForSeconds(4));
        }
        }, this);
}

void Spell14MasterCtrl::update() {}

void Spell14MasterCtrl::shootConeImpl1() {
    auto ctrl = GameObject::Instantiate("YellowSphereCtrl");
    auto ball1 = ctrl->addComponent<DmConeExpandCtrl>(12, 16, player->transform().getPosition(), 1, 162);
    Vector3f locForward = enemy->transform().getPosition();
    Vector3f conePos = player->transform().getPosition();
    ShootCone::Shoot3(24,
        ballPool,
        transform()->getPosition(),
        conePos,
        locForward,
        transform()->getRotation(),
        [&ec = ball1](const HGameObject& _dm) {
            _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Yellow());
            ec->add(_dm);
        });

}
void Spell14MasterCtrl::shootConeImpl2() {
    auto ctrl = GameObject::Instantiate("PurpleSphereCtrl");
    auto ball1 = ctrl->addComponent<DmStraightExpandCtrl>(ballPool, 10, 14, 1.5, 162);
    Vector3f locForward =enemy->transform().getPosition();
    Vector3f conePos = player->transform().getPosition();
    ShootCone::Shoot2(24,
        ballPool,
        transform()->getPosition(),
        conePos,
        locForward,
        transform()->getRotation(),
        [&ec = ball1](const HGameObject& _dm) {
            _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Purple());
            ec->add(_dm);
        });

}
void Spell14MasterCtrl::setShootTimes(unsigned int _ShootTimes) {
    ShootTimes = _ShootTimes;
}
void Spell14MasterCtrl::setShootCone(unsigned int _ShootCone) {
    ShootCone = _ShootCone;
}
