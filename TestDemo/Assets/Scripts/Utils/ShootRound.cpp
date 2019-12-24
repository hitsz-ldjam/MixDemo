#include "ShootRound.h"

void ShootRound::Shoot(const int _num,
                       HDmPool& _pool,
                       const Vector3f& _pos,
                       const Vector3f& _forward,
                       const Vector3f& _up,
                       const std::function<void(const HGameObject&)>& _setup) {
    const auto delta = Quaternion::AngleAxis(Math::Constants::Pi2 / _num, _up);
    auto forward = _forward;
    for(auto i = 0; i < _num; ++i) {
        auto dm = _pool->createDm();
        dm->transform().setPosition(_pos);
        dm->transform().setRotation(Quaternion::LookRotation(forward, _up));
        _setup(dm);
        forward = delta * forward;
    }
}
