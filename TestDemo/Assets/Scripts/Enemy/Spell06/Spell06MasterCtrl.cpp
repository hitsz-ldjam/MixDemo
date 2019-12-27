#include "Spell06MasterCtrl.h"
#include "../../Prefabs/Prefab.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../Utils/ShootSphere.h"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../DmCtrl/DmStraightMoveCtrl.h"
#include "../../DmCtrl/DmStraightExpandCtrl.h"
//#include "../../DmCtrl/DmCurveExpandCtrl.h"
#include "../../StateMachine/StateMachine.h"
#include "../../GameMgr.h"

MX_IMPLEMENT_RTTI(Spell06MasterCtrl, Script)

Spell06MasterCtrl::Spell06MasterCtrl(HDmPool _bfPool)
    : bfPool(std::move(_bfPool)) {}

void Spell06MasterCtrl::forceClearDm() {
    for(auto& ctrl : ctrls) {
        auto expands = ctrl->getComponents<DmStraightExpandCtrl>();
        for(auto& expand : expands) {
            expand->clearAll();
        }
    }
}

void Spell06MasterCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, HSpell06MasterCtrl _this) {
        while(StateMachine::gameMgr->getState() == GameMgr::State::Spell6Exec) {
            if(_this) _this->shootBlueSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(.4));
            if(_this) _this->shootPurpleSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(.4));
            if(_this) _this->shootBlueSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(.4));
            if(_this) _this->shootPurpleSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(.4));
            if(_this) _this->shootBlueSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(.4));
            if(_this) _this->shootPurpleSphereImpl(); else return;

            yield_return(new Coroutine::WaitForSeconds(2.4));

            if(_this) _this->shootRedSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(1));
            if(_this) _this->shootRedSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(1));
            if(_this) _this->shootRedSphereImpl(); else return;
            yield_return(new Coroutine::WaitForSeconds(1));
            if(_this) _this->shootRedSphereImpl(); else return;

            yield_return(new Coroutine::WaitForSeconds(3));
        }
    }, THIS_HANDLE);
}

void Spell06MasterCtrl::update() {
    if(CLEAR_DM_STATES) {
        forceClearDm();
    }
}

void Spell06MasterCtrl::shootBlueSphereImpl() {
    auto ctrl = GameObject::Instantiate("BlueSphereMasterCtrl");
    ctrls.push_back(ctrl);
    auto ec1 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 4, 16, 4, 162);
    auto ec2 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 4, 8, 4, 162);
    auto ec3 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 4, 4, 4, 162);

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec1](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec2](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec3](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                           ec->add(_dm);
                       });
}

void Spell06MasterCtrl::shootPurpleSphereImpl() {
    auto ctrl = GameObject::Instantiate("PurpleSphereCtrl");
    ctrls.push_back(ctrl);
    auto ec1 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 4, 8, 4, 162);
    auto ec2 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 4, 4, 4, 162);

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       Quaternion::AngleAxis(Math::Constants::Pi / 20, transform()->up()) * transform()->getRotation(),
                       [&ec = ec1](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Purple());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       Quaternion::AngleAxis(Math::Constants::Pi / 20, transform()->up()) * transform()->getRotation(),
                       [&ec = ec2](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Purple());
                           ec->add(_dm);
                       });
}

void Spell06MasterCtrl::shootRedSphereImpl() {
    auto ctrl = GameObject::Instantiate("RedSphereCtrl");
    ctrls.push_back(ctrl);

    // todo
    //auto ec1 = ctrl->addComponent<DmCurveExpandCtrl>(5, 17, 4, 162);
    //auto ec2 = ctrl->addComponent<DmCurveExpandCtrl>(5, 12, 4, 162);
    //auto ec3 = ctrl->addComponent<DmCurveExpandCtrl>(5, 5, 4, 162);

    auto ec1 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 5, 17, 4, 162);
    auto ec2 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 5, 12, 4, 162);
    auto ec3 = ctrl->addComponent<DmStraightExpandCtrl>(bfPool, 5, 5, 4, 162);

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec1](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Red());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec2](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Red());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bfPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec3](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Red());
                           ec->add(_dm);
                       });
}
