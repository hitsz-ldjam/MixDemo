#include "ShootSphere.h"
#include "../../../../Mx/GameObject/MxGameObject.h"

void ShootSphere::Shoot_162_20(HDmPool& _pool,
                               const Vector3f& _pos,
                               const Quaternion& _rot,
                               const std::function<void(const HGameObject&)>& _setup) {
    //               hard coded
    for(auto i = 2; i < 486; i += 3) {
        auto dm = _pool->createDm();
        dm->transform().setPosition(_pos);

        Vector3 forward(sphereData_162_20[i - 2], sphereData_162_20[i - 1], sphereData_162_20[i]);
        dm->transform().setRotation(_rot * Quaternion::LookRotation(forward));

        _setup(dm);
    }
}
