#pragma once

#include "../Mx/Component/Script/MxScript.h"
#include "../Mx/GameObject/MxGameObject.h"
#include "../Mx/Component/Camera/MxCamera.h"
#include "../Mx/Scene/MxSceneManager.h"
#include "../Mx/Math/MxVector.h"
#include "../Mx/Utils/MxEvent.h"
#include "../MxApplicationBase.h"



	using namespace Mix;

	class  PlayerAdapter;

	class PlayerControll:public Script {
		MX_DECLARE_RTTI;
		public:
			PlayerControll(HCamera _Hcamera)
				:mainCamera(std::move(_Hcamera)) {
			}
			~PlayerControll() = default;

		private:
			void start() override;

			void update() override;

			void fixedUpdate() override;

			Vector3f getDir();

			Vector3f dirFromGamepad();
			
			Vector3f dirFromKeyboard();

			SceneObjectHandle<PlayerAdapter> mAdapter;

			HCamera mainCamera;

	};
	using HPlayerControll = SceneObjectHandle<PlayerControll>;