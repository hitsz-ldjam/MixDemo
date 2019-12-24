#include "ShootSphere.h"

void ShootSphere::Shoot(const SphereType _type,
                        HDmPool& _pool,
                        const Vector3f& _pos,
                        const Quaternion& _rot,
                        const std::function<void(const HGameObject&)>& _setup) {
    auto length = 0;
    const float* data = nullptr;
    switch(_type) {
        case SphereType::Verts_642:
            length = 642 * 3;
            data = sphereData_642_40;
            break;

        case SphereType::Verts_162:
            length = 162 * 3;
            data = sphereData_162_20;
            break;

        case SphereType::Verts_42:
            length = 42 * 3;
            data = sphereData_42_10;
            break;

        case SphereType::Verts_12:
            length = 12 * 3;
            data = sphereData_12;
            break;

        default: break;
    }

    for(auto i = 2; i < length; i += 3) {
        auto dm = _pool->createDm();
        dm->transform().setPosition(_pos);

        Vector3 forward(data[i - 2], data[i - 1], data[i]);
        // ???
        dm->transform().setRotation(_rot * Quaternion::LookRotation(forward));

        _setup(dm);
    }
}
