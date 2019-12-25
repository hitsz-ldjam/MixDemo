#include "Spell03SwTail.h"
#include "Spell03BfMstRot.h"
#include "Spell03BfMstCtrl.h"
#include "../../Utils/ShootSphere.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"

MX_IMPLEMENT_RTTI(Spell03SwTail, Script)

Spell03SwTail::Spell03SwTail(HGameObject _player,
                             HDmPool _pool) : player(std::move(_player)),
                                              pool(std::move(_pool)) {}

void Spell03SwTail::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, Spell03SwTail* _this) {
        int cnt = 15;
        while(--cnt != 0) {
            yield_return(new Coroutine::WaitForSeconds(5.4f));
            _this->shootBf();
        }
    }, this);
}

void Spell03SwTail::update() { }

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

                           auto randVal = 0; // todo Random.Range(-20, 20)
                           _dm->transform().setLocalRotation(Quaternion::AngleAxis(randVal, Vector3f::Forward) * localRot);

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
    auto masterPos = player->transform().getPosition() + player->transform().forward() * 5;
    auto masterRot = Quaternion::Identity;

    const auto rotAxis = player->transform().getPosition() - masterPos; // todo
    const auto masterRotDelta = Quaternion::AngleAxis(Math::Radians(60.f), rotAxis);

    maxRadius = 7;
    shootSingleLayer(masterPos, masterRot, SimpleMaterials::Red(), maxRadius, forwardTime, rotSpeed, false);

    maxRadius = 5.5;
    shootSingleLayer(masterPos, masterRotDelta * masterRot, SimpleMaterials::Purple(), maxRadius, forwardTime, rotSpeed, true);

    maxRadius = 4.2;
    shootSingleLayer(masterPos, masterRot, SimpleMaterials::Blue(), maxRadius, forwardTime, rotSpeed, false);

    maxRadius = 3;
    shootSingleLayer(masterPos, masterRotDelta * masterRot, SimpleMaterials::Cyan(), maxRadius, forwardTime, rotSpeed, true);
}
