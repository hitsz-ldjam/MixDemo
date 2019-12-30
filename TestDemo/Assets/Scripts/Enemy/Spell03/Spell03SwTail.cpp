#include "Spell03SwTail.h"
#include "Spell03BfMstRot.h"
#include "Spell03BfMstCtrl.h"
#include "../../Utils/ShootSphere.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../GameMgr.h"
#include "../../StateMachine/StateMachine.h"
#include "../../../../../Mx/Math/MxRandom.h"

MX_IMPLEMENT_RTTI(Spell03SwTail, Script)

void Spell03SwTail::forceClearDm() {
    //for(auto& ctrl : ctrls) {
    //    auto expands = ctrl->getComponents<DmStraightExpandCtrl>();
    //    for(auto& expand : expands) {
    //        expand->clearAll();
    //    }
    //}
}

Spell03SwTail::Spell03SwTail(HGameObject _player,
                             HDmPool _pool) : player(std::move(_player)),
                                              pool(std::move(_pool)),
                                              rnd(9) {}

void Spell03SwTail::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, HSpell03SwTail _this) {
        while(StateMachine::gameMgr->getState() == GameMgr::State::Spell3Exec) {
            yield_return(new Coroutine::WaitForSeconds(5.4f));
            if(_this) _this->shootBf();
            else return;
        }
    }, THIS_HANDLE);
}

void Spell03SwTail::update() {
    if(CLEAR_DM_STATES) {
        masters.clear();
    }
}

HGameObject Spell03SwTail::shootSingleLayer(const Vector3f& _masterPos,
                                            const Quaternion& _masterRot,
                                            const std::shared_ptr<Material>& _mat,
                                            const float _maxRadius,
                                            const float _forwardTime,
                                            const float _rotSpeed,
                                            const bool _clockWise) {
    auto master = GameObject::Instantiate("Spell03BfMaster");
    master->transform().setPosition(_masterPos);
    master->transform().setRotation(_masterRot);
    auto ctrl = master->addComponent<Spell03BfMstCtrl>(Vector3f(),
                                                       _maxRadius,
                                                       _forwardTime,
                                                       pool);

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_42,
                       pool,
                       _masterPos,
                       _masterRot,
                       [&](const HGameObject& _dm) {
                           _dm->setParent(master);
                           auto& localRot = _dm->transform().getLocalRotation();

                           auto randVal = rnd.getRange(-20.f, 20.f);
                           randVal = Math::Radians(randVal);
                           _dm->transform().setLocalRotation(Quaternion::AngleAxis(randVal, Vector3f::Forward) * localRot);
                           _dm->transform().setLocalScale(Vector3f(2.0f));
                           _dm->getComponent<Renderer>()->setMaterial(_mat); // todo

                           ctrl->add(_dm);
                       });

    master->addComponent<Spell03BfMstRot>((_clockWise ? _rotSpeed : -_rotSpeed),
                                          player->transform().getPosition() - master->transform().getPosition());

    return master;
}

void Spell03SwTail::shootBf() {
    float forwardTime = 1.7f,
          maxRadius = 7,
          rotSpeed = Math::Radians(70.f);

    // todo: prediction
    auto masterPos = player->transform().getPosition() + player->transform().forward() * 10;
    auto masterRot = Quaternion::Identity;

    const auto rotAxis = player->transform().getPosition() - masterPos; // todo
    const auto masterRotDelta = Quaternion::AngleAxis(Math::Radians(60.f), rotAxis);

    maxRadius = 7;
    auto master = shootSingleLayer(masterPos, masterRot, SimpleMaterials::redMatofBf, maxRadius, forwardTime, rotSpeed, false);
    masters.push_back(master);

    maxRadius = 5.5;
    shootSingleLayer(masterPos, masterRotDelta * masterRot, SimpleMaterials::purpleMatofBf, maxRadius, forwardTime, rotSpeed, true);
    masters.push_back(master);

    maxRadius = 4.2;
    shootSingleLayer(masterPos, masterRot, SimpleMaterials::blueMatofBf, maxRadius, forwardTime, rotSpeed, false);
    masters.push_back(master);

    maxRadius = 3;
    shootSingleLayer(masterPos, masterRotDelta * masterRot, SimpleMaterials::Cyan(), maxRadius, forwardTime, rotSpeed, true);
    masters.push_back(master);
}
