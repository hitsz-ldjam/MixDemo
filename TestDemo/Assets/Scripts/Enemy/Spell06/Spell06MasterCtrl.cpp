#include "Spell06MasterCtrl.h"
#include "../../Prefabs/Prefab.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../Utils/ShootSphere.h"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../DmCtrl/DmStraightMoveCtrl.h"
#include "../../DmCtrl/DmStraightExpandCtrl.h"

MX_IMPLEMENT_RTTI(Spell06MasterCtrl, Script)

Spell06MasterCtrl::Spell06MasterCtrl(HDmPool _bigballPool)
    : bigballPool(std::move(_bigballPool)) {}

void Spell06MasterCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, Spell06MasterCtrl* _this) {
        _this->shootBlueSphereImpl();
        yield_return(new Coroutine::WaitForSeconds(.4));
        _this->shootPurpleSphereImpl();
    }, this);
}

void Spell06MasterCtrl::update() {}

void Spell06MasterCtrl::shootBlueSphereImpl() {
    auto ctrl = GameObject::Instantiate("BlueSphereMasterCtrl");
    auto ec1 = ctrl->addComponent<DmStraightExpandCtrl>(3, 12, 3, 162);
    auto ec2 = ctrl->addComponent<DmStraightExpandCtrl>(3, 6, 3, 162);
    auto ec3 = ctrl->addComponent<DmStraightExpandCtrl>(3, 3, 3, 162);

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bigballPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec1](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bigballPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec2](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bigballPool,
                       transform()->getPosition(),
                       transform()->getRotation(),
                       [&ec = ec3](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                           ec->add(_dm);
                       });
}

void Spell06MasterCtrl::shootPurpleSphereImpl() {
    auto ctrl = GameObject::Instantiate("PurpleSphereCtrl");
    auto ec1 = ctrl->addComponent<DmStraightExpandCtrl>(3, 6, 3, 162);
    auto ec2 = ctrl->addComponent<DmStraightExpandCtrl>(3, 3, 3, 162);

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bigballPool,
                       transform()->getPosition(),
                       Quaternion::AngleAxis(Math::Constants::Pi / 20, transform()->up()) * transform()->getRotation(),
                       [&ec = ec1](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Purple());
                           ec->add(_dm);
                       });

    ShootSphere::Shoot(ShootSphere::SphereType::Verts_162,
                       bigballPool,
                       transform()->getPosition(),
                       Quaternion::AngleAxis(Math::Constants::Pi / 20, transform()->up()) * transform()->getRotation(),
                       [&ec = ec2](const HGameObject& _dm) {
                           _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Purple());
                           ec->add(_dm);
                       });
}
