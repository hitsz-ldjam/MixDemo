#include "ThirdCamera.h"
#include "../Mx/Input/MxInput.h"
#include "../Mx/Component/Camera/MxCamera.h"
#include "../Mx/Log/MxLog.h"
#include "../Mx/Window/MxWindow.h"
#include "PlayerAdapter.h"
#include "../Mx/Math/MxMath.h"

namespace Scripts {
	MX_IMPLEMENT_RTTI(ThirdCamera, Script);

	void ThirdCamera::start() {

		mAdapter = mGameObject->getComponent<ThirdCamera>;
		
		offset = transform()->getPosition - CameraPivot->transform.position;
	}

	void ThirdCamera::update() {
		FreeCamera();
	}

	void ThirdCamera::fixedUpdate() {
	}

	void ThirdCamera::FreeCamera() {
		offset = offset.normalize() * freeDistance;

		transform()->setPosition = Vector3f::Lerp(transform()->getPosition, CameraPivot->transform.position + offset, 1.0f);

		if (CanControlDirection) {
			Quaternion TargetBodyCurrentRotation = CameraPivot->transform.rotation;
			CameraPivot->transform.rotation = Quaternion().lerp(Quaternion().Euler(Vector3f(CameraPivot->transform.localEulerAngles.x, transform()->getLocalRotation().Euler.y , CameraPivot->transform.localEulerAngles.z)), TargetBodyRotateLerp);
		}

		if (canControlDistance)
		{
			float ScrollWheel = Input::Get()->getAxis(AxisCode::Mouse_WheelY);
			//if (Input::Get().getAxis(Mouse_WheelY)) {
			//	ScrollWheel
			//}
			freeDistance -= ScrollWheel * distanceSpeed;
		}
		freeDistance = mAdapter->Clamp(freeDistance, minDistance, maxDistance);

		transform()->lookAt(CameraPivot->transform.position);

		float eulerX = transform()->getLocalRotation().Euler.x;
		float inputY = Input::Get()->getMousePosition().y;

		transform()->rotateAround(CameraPivot->transform.position, Vector3f::Up, rotateSpeed * Input::Get()->getMousePosition().x);

		if (eulerX > maxDepression&& eulerX < 90)
		{
			if (inputY > 0)
				transform()->rotateAround(CameraPivot->transform.position, Vector3f::Right, -rotateSpeed * inputY);
		}
		else if (eulerX < 360 - maxEvelation && eulerX > 270)
		{
			if (inputY < 0)
				transform()->rotateAround(CameraPivot->transform.position, Vector3f::Right, -rotateSpeed * inputY);
		}
		else
		{

			transform()->rotateAround(CameraPivot->transform.position, Vector3f::Right, -rotateSpeed * inputY);

		}

		offset = transform()->getPosition - CameraPivot->transform.position;
		offset = offset.normalize() * freeDistance;
		transform()->setPosition = CameraPivot->transform.position + offset;
	}

}
