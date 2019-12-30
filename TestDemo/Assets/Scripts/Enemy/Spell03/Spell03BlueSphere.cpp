#include "Spell03BlueSphere.h"
#include <utility>
#include "../../Utils/ShootRound.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../DmCtrl/DmStraightMoveCtrl.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../GameMgr.h"
#include "../../StateMachine/StateMachine.h"

MX_IMPLEMENT_RTTI(Spell03BlueSphere, Script)

Spell03BlueSphere::Spell03BlueSphere(HGameObject _player,
                                     HDmPool _pool)
    : player(std::move(_player)),
      pool(std::move(_pool)) {}

void Spell03BlueSphere::forceClearDm() {
    if(ctrlObj) {
        auto expands = ctrlObj->getComponents<DmStraightMoveCtrl>();
        for(auto& expand : expands) {
            expand->clearAll();
        }
    }
}

void Spell03BlueSphere::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, HSpell03BlueSphere _this) {
        auto ctrl = GameObject::Instantiate("debug master");
        _this->ctrlObj = ctrl;
        auto scrpOdd = ctrl->addComponent<DmStraightMoveCtrl>(_this->pool, 12);
        auto scrpEven = ctrl->addComponent<DmStraightMoveCtrl>(_this->pool, 8);

        const auto num = 18;
        const auto up = Vector3f::Up;
        auto delta = Quaternion::AngleAxis(Math::Constants::Pi / 18, up);

        while(StateMachine::gameMgr->getState() == GameMgr::State::Spell3Exec) {
            if(!_this || !_this->ctrlObj)
                return;
            Vector3f forward = _this->player->transform().getPosition() - _this->transform()->getPosition();
            ShootRound::Shoot(num,
                              _this->pool,
                              _this->transform()->getPosition(),
                              forward,
                              up, // todo
                              [&scrp = scrpOdd](const HGameObject& _dm) {
                                  _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::blueRimMat);
                                  scrp->add(_dm);
                              });

            yield_return(new Coroutine::WaitForSeconds(.3));

            if(!_this || !_this->ctrlObj)
                return;
            ShootRound::Shoot(num,
                              _this->pool,
                              _this->transform()->getPosition(),
                              delta * forward,
                              up, // todo
                              [&scrp = scrpEven](const HGameObject& _dm) {
                                  _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::blueRimMat);
                                  scrp->add(_dm);
                              });
            yield_return(new Coroutine::WaitForSeconds(1));
        }
    }, THIS_HANDLE);
}

void Spell03BlueSphere::update() {
    if(CLEAR_DM_STATES) {
        forceClearDm();
    }
}
