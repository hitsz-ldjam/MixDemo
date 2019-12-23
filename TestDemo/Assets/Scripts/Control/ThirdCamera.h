#pragma once

#include "../Mx/Component/Script/MxScript.h"
#include "../Mx/GameObject/MxGameObject.h"
#include "../Mx/Math/MxVector.h"
#include "../Mx/Utils/MxEvent.h"
#include "../MxApplicationBase.h"


namespace Scripts {
	using namespace Mix;

	class  PlayerAdapter;

	class ThirdCamera:public Script{
		MX_DECLARE_RTTI;
	public:
		~ThirdCamera() = default ;
		
	private:

		float freeDistance = 5.0f;

		float minDistance = 2.5f;

		float maxDistance = 8.0f;

		bool canControlDistance = true;

		float distanceSpeed = 1.0f;

		float rotateSpeed = 1.0f;

		float TargetBodyRotateLerp = 0.3f;

		HGameObject CameraPivot;

		bool CanControlDirection = true;

		Vector3f PredictCameraPosition;

		Vector3f offset;

		float maxDepression = 80.0f;

		float maxEvelation = 80.0f;

		void start() override;

		void update() override;

		void fixedUpdate() override;

		void  FreeCamera();

		SceneObjectHandle<PlayerAdapter> mAdapter;

	};

}