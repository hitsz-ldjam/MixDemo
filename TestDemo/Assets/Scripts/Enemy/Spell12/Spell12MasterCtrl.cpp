#include "Spell12MasterCtrl.h"
#include "../../Prefabs/Prefab.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../Utils/ShootCone.h"
#include "../../Utils/ShootRound.h"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../DmCtrl/DmStraightMoveCtrl.h"
#include "../../DmCtrl/DmStraightExpandCtrl.h"

MX_IMPLEMENT_RTTI(Spell12MasterCtrl, Script)

Spell12MasterCtrl::Spell12MasterCtrl(HGameObject _player,
    HDmPool _bigballPool,
    HDmPool _ballPool)
    : player(std::move(_player)),
    bigballPool(std::move(_bigballPool)) ,
    ballPool(std::move(_ballPool)) {}

void Spell12MasterCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, Spell12MasterCtrl* _this) {
        for (int j = 0; j < _this->ShootTimes; j++) {
            for (int i = 0; i < _this->ShootCone; i++) {
                _this->shootConeImpl();
                yield_return(new Coroutine::WaitForSeconds(.12));
            }
            auto ctrl = GameObject::Instantiate("PurpleSphereCtrl");
            auto ball = ctrl->addComponent<DmStraightMoveCtrl>(6);

            const auto num = 36;
            const auto up = Vector3f::Up;

            auto forward = _this->player->transform().getPosition() - _this->transform()->getPosition();
            ShootRound::Shoot(num,
                _this->bigballPool,
                _this->transform()->getPosition(),
                forward,
                up, // todo
                [&scrp = ball](const HGameObject& _dm) {
                    _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Purple());
                    scrp->add(_dm);
                });
            yield_return(new Coroutine::WaitForSeconds(3));
        }
        }, this);
}

void Spell12MasterCtrl::update() {}

void Spell12MasterCtrl::shootConeImpl() {
    auto ctrl = GameObject::Instantiate("PurpleSphereCtrl");
    auto ball1 = ctrl->addComponent<DmStraightExpandCtrl>(3, 12, 3, 162);
        ShootCone::Shoot(ballPool,
            transform()->getPosition(),
            transform()->getRotation(),
            [&ec = ball1](const HGameObject& _dm) {
                _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                ec->add(_dm);
            });
    
}
void Spell12MasterCtrl::setShootTimes(unsigned int _ShootTimes) {
    ShootTimes = _ShootTimes;
}
void Spell12MasterCtrl::setShootCone(unsigned int _ShootCone) {
    ShootCone = _ShootCone;
}
