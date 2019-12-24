#include "Spell03BlueSphere.h"
#include <utility>
#include "../../Utils/ShootRound.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../DmCtrl/DmStraightMoveCtrl.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"

MX_IMPLEMENT_RTTI(Spell03BlueSphere, Script)

Spell03BlueSphere::Spell03BlueSphere(HGameObject _player,
                                     HDmPool _pool)
    : player(std::move(_player)),
      pool(std::move(_pool)) {}

void Spell03BlueSphere::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, Spell03BlueSphere* _this) {
        auto ctrl = GameObject::Instantiate("debug master");
        auto scrpOdd = ctrl->addComponent<DmStraightMoveCtrl>(6);
        auto scrpEven = ctrl->addComponent<DmStraightMoveCtrl>(4);

        const auto num = 18;
        const auto up = Vector3f::Up;
        auto delta = Quaternion::AngleAxis(Math::Constants::Pi / 18, up);

        for(int i = 0; i < 3; ++i) {
            auto forward = _this->player->transform().getPosition() - _this->transform()->getPosition();
            ShootRound::Shoot(num,
                              _this->pool,
                              _this->transform()->getPosition(),
                              forward,
                              up, // todo
                              [&scrp = scrpOdd](const HGameObject& _dm) {
                                  _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                                  scrp->add(_dm);
                              });

            yield_return(new Coroutine::WaitForSeconds(.3));

            ShootRound::Shoot(num,
                              _this->pool,
                              _this->transform()->getPosition(),
                              delta * forward,
                              up, // todo
                              [&scrp = scrpEven](const HGameObject& _dm) {
                                  _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                                  scrp->add(_dm);
                              });
            yield_return(new Coroutine::WaitForSeconds(1));
        }
    }, this);

}

void Spell03BlueSphere::update() { }
