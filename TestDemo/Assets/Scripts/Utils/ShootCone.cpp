#include "ShootCone.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include <random>
#include "../../../../Mx/Time/MxTime.h"
#include "../../../../Mx/Log/MxLog.h"

int times = Time::RealTime();

std::default_random_engine e(times);

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
void ShootCone::Shoot2(const int _num,
	HDmPool& _pool,
	const Vector3f& _pos,
	const Vector3f& _conepos,
	const Vector3f& _forward,
	const Quaternion& _rot,
	const std::function<void(const HGameObject&)>& _setup) {
	auto delta1 = Quaternion(0, 0, 0, 0);
	auto delta2 = Quaternion(0, 0, 0, 0);
	Vector3f forward = _conepos - _forward;
	Vector3f conepos = (_conepos + _forward) / 2;
	for (auto i = 0; i < _num; ++i) {
		auto dm = _pool->createDm();
		Vector3f pos = _pos + 3*Vector3f::Up;
		dm->transform().setPosition(pos);
		dm->transform().rotateAround(_forward, forward,i * Math::Constants::Pi2 / _num);
		dm->transform().lookAt(conepos);
		_setup(dm);
	}
}
void ShootCone::Shoot3(const int _num,
	HDmPool& _pool,
	const Vector3f& _pos,
	const Vector3f& _conepos,
	const Vector3f& _forward,
	const Quaternion& _rot,
	const std::function<void(const HGameObject&)>& _setup) {
	Vector3f forward = (_conepos - _forward) / 2;
	Vector3f conepos = (_conepos + _forward) / 2;
	const auto delta = Quaternion::AngleAxis(Math::Constants::Pi2 / _num, forward);
	Vector3f up = 3*Vector3f::Up;
	for (auto i = 0; i < _num; ++i) {
		auto dm = _pool->createDm();
		dm->transform().setPosition(_pos);
		dm->transform().setRotation(Quaternion::LookRotation(up + forward, forward));
		_setup(dm);
		up = delta * up;
	}
}

