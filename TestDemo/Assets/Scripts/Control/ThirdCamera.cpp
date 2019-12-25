#include "ThirdCamera.h"
#include "../Mx/Input/MxInput.h"
#include "../Mx/Component/Camera/MxCamera.h"
#include "../Mx/Log/MxLog.h"
#include "../Mx/Window/MxWindow.h"
#include "../Mx/Math/MxQuaternion.h"
#include "PlayerAdapter.h"
#include "../Mx/Math/MxMath.h"

	MX_IMPLEMENT_RTTI(ThirdCamera, Script);

	void ThirdCamera::start() {

		mAdapter = mGameObject->getComponent<PlayerAdapter>();
		
		offset = transform()->getPosition() - CameraPivot->transform().getPosition();
	}

	void ThirdCamera::update() {
		FreeCamera();
	}

	void ThirdCamera::fixedUpdate() {
	}

	void ThirdCamera::FreeCamera() {
		offset = offset.normalize() * freeDistance;

		transform()->setPosition( Vector3f::Lerp(transform()->getPosition(), CameraPivot->transform().getPosition() + offset, 1.0f ));

		if (CanControlDirection) {
			Quaternion TargetBodyCurrentRotation = CameraPivot->transform().getRotation();
		    
			CameraPivot->transform().rotate(Quaternion().Euler(Vector3f(CameraPivot->transform().getLocalRotation().x, transform()->getLocalRotation().y , CameraPivot->transform().getLocalRotation().z)));
		}

		if (canControlDistance)
		{
			float ScrollWheel = Input::Get()->getAxis(AxisCode::Mouse_WheelY);
			//if (Input::Get().getAxis(Mouse_WheelY)) {
			//	ScrollWheel
			//}
			freeDistance -= ScrollWheel * distanceSpeed;
		}

		transform()->lookAt(CameraPivot->transform().getPosition());

		float eulerX = transform()->getLocalRotation().x;
		float inputY = Input::Get()->getMousePositionDelta().y;

		transform()->rotateAround(CameraPivot->transform().getPosition(), Vector3f::Up, rotateSpeed * Input::Get()->getMousePositionDelta().x);

		if (eulerX > maxDepression&& eulerX < 90)
		{
			if (inputY > 0)
				transform()->rotateAround(CameraPivot->transform().getPosition(), Vector3f::Right, -rotateSpeed * inputY);
		}
		else if (eulerX < 360 - maxEvelation && eulerX > 270)
		{
			if (inputY < 0)
				transform()->rotateAround(CameraPivot->transform().getPosition(), Vector3f::Right, -rotateSpeed * inputY);
		}
		else
		{

			transform()->rotateAround(CameraPivot->transform().getPosition(), Vector3f::Right, -rotateSpeed * inputY);

		}

		offset = transform()->getPosition() - CameraPivot->transform().getPosition();
		offset = offset.normalize() * freeDistance;
		transform()->setPosition (CameraPivot->transform().getPosition() + offset);
	}

	float ThirdCamera::Clamp(float _clamp, float _x, float _y) {
		if (_clamp < _x) {
			return _x;
		}
		if (_clamp > _y) {
			return _y;
		}
	}

	void ThirdCamera::setfreeDistance(float _freeDistance) {
		freeDistance = _freeDistance;
	}

	void ThirdCamera::setminDistance(float _minDistance) {
		minDistance = _minDistance;
	}

	void ThirdCamera::setmaxDistance(float _maxDistance) {
		maxDistance = _maxDistance;
	}

	void ThirdCamera::iscanControlDistance(bool _canControlDistance) {
		canControlDistance = _canControlDistance;
	}

	void ThirdCamera::setdistanceSpeed(float _distanceSpeed) {
		distanceSpeed = _distanceSpeed;
	}

	void ThirdCamera::setrotateSpeed(float _rotateSpeed) {
		rotateSpeed = _rotateSpeed;
	}

	void ThirdCamera::setTargetBodyRotateLerp(float _TargetBodyRotateLerp) {
		TargetBodyRotateLerp = _TargetBodyRotateLerp;
	}

	void ThirdCamera::isCanControlDirection(bool _CanControlDirection) {
		CanControlDirection = _CanControlDirection;
	}

	void ThirdCamera::setmaxDepression(float _maxDepression) {
		maxDepression = _maxDepression;
	}

	void ThirdCamera::setmaxEvelation(float _maxEvelation) {
		maxEvelation = _maxEvelation;
	}


