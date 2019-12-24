#pragma once
#include "../../../../Mx/Math/MxVector3.h"
#include "../../../../Mx/Math/MxQuaternion.h"
#include "DmPool.h"

using namespace Mix;

class ShootRound final {
public:
    static void Shoot(const int _num,
                      HDmPool& _pool,
                      const Vector3f& _pos,
                      //const Quaternion& _rot, // not used
                      const Vector3f& _forward,
                      const Vector3f& _up,
                      const std::function<void(const HGameObject&)>& _setup = [](auto&) {});
};
