#include "ShootCone.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include <random>
#include "../../../../Mx/Time/MxTime.h"

std::default_random_engine e;
std::uniform_int_distribution<int> u(0, 291);

void ShootCone::Shoot( 
    HDmPool& _pool,
    const Vector3f& _pos,
    const Quaternion& _rot,
    const std::function<void(const HGameObject&)>& _setup) {
    auto length = 291 * 3;
    const float* data = ComeData;

     auto dm = _pool->createDm();
     dm->transform().setPosition(_pos);

     Vector3 forward(data[u(e)], data[u(e) + 1], data[u(e) + 2]);
     dm->transform().setRotation(_rot * Quaternion::Euler(forward));

     _setup(dm);
    
}
