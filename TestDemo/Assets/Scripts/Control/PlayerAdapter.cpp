#include "PlayerControll.h"
#include "../Mx/Input/MxInput.h"
#include "../Mx/Component/Camera/MxCamera.h"
#include "../Mx/Log/MxLog.h"
#include "../Mx/Window/MxWindow.h"
#include "PlayerAdapter.h"

namespace Scripts {
	MX_IMPLEMENT_RTTI(PlayerAdapter, Script);

	void PlayerAdapter::move(const Vector3f& _dir) {
		auto moveDir = _dir.length() > 0.0f ? _dir.normalize() : Vector3f::Zero;

		mSmoothMove = Vector3f::Lerp(mSmoothMove, moveDir * mMoveSpeed, mAccelerate);
		mSmoothMove = Vector3f::Lerp(mSmoothMove, Vector3f::Zero, mDecelerate);
		transform()->translate(mSmoothMove.x, mSmoothMove.y, mSmoothMove.z, Space::World);

		int hDir = moveDir.x > 0.0f ? -1 : (moveDir.x < 0.0f ? 1 : 0);

	}

	float Clamp(float _clamp, float _x, float _y) {
		if (_clamp < _x) {
			return _x;
		}
		if (_clamp > _y) {
			return _y;
		}
	}

	void PlayerAdapter::attack() {
		//auto weapon = mGameObject->getComponent<...>();
		//if (weapon != nullptr)
		//	weapon->attack();
	}

	void PlayerAdapter::setMoveSpeed(float _speed) {
		mMoveSpeed = _speed;
	}

	void PlayerAdapter::awake() {
	}

	void PlayerAdapter::start() {
	}

	void PlayerAdapter::update() {
	}

	void PlayerAdapter::fixedUpdate() {
	}
}