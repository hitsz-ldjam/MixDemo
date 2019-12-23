#include "Spell06MasterCtrl.h"
#include "../../Prefabs/Prefab.h"
#include "../../Utils/SimpleMaterials.h"
#include "../../Utils/ShootSphere.h"
#include "../../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../DmCtrl/DmStraightMoveCtrl.h"
#include "../../DmCtrl/DmStraightExpandCtrl.h"

MX_IMPLEMENT_RTTI(Spell06MasterCtrl, Script)

Spell06MasterCtrl::Spell06MasterCtrl(HDmPool _bigballPool)
    : bigballPool(std::move(_bigballPool)) {}

void Spell06MasterCtrl::start() {
    shootBlueSphereImpl();
}

void Spell06MasterCtrl::update() {}

void Spell06MasterCtrl::shootBlueSphereImpl() {
    auto ctrl = GameObject::Instantiate("BlueSphereCtrl");
    auto ec1 = ctrl->addComponent<DmStraightExpandCtrl>(3, 12, 3, 162);
    auto ec2 = ctrl->addComponent<DmStraightExpandCtrl>(3, 6, 3, 162);
    auto ec3 = ctrl->addComponent<DmStraightExpandCtrl>(3, 3, 3, 162);

    ShootSphere::Shoot_162_20(bigballPool,
                              transform()->getPosition(),
                              transform()->getRotation(),
                              [&ec = ec1](const HGameObject& _dm) {
                                  _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Blue());
                                  ec->add(_dm);
                              });

    ShootSphere::Shoot_162_20(bigballPool,
                              transform()->getPosition(),
                              transform()->getRotation(),
                              [&ec = ec2](const HGameObject& _dm) {
                                  _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Purple());
                                  ec->add(_dm);
                              });

    ShootSphere::Shoot_162_20(bigballPool,
                              transform()->getPosition(),
                              transform()->getRotation(),
                              [&ec = ec3](const HGameObject& _dm) {
                                  _dm->getComponent<Renderer>()->setMaterial(SimpleMaterials::Cyan());
                                  ec->add(_dm);
                              });
}
