#include "PlayerControll.h"

#include "../../../../Mx/Input/MxInput.h"
#include "../../../../Mx/Component/Camera/MxCamera.h"
#include "../../../../Mx/Window/MxWindow.h"
#include "PlayerAdapter.h"


	MX_IMPLEMENT_RTTI(PlayerControll, Script);
	
	void PlayerControll::start() {
		mAdapter = mGameObject->getComponent<PlayerAdapter>();
		auto mainCamera = SceneManager::Get()->getActiveScene()->getMainCamera();
	}
	void PlayerControll::update() {
		mAdapter->move(getDir());

		//mAdapter->attack();
	}

	void PlayerControll::fixedUpdate() {
	}

	Vector3f PlayerControll::getDir() {
		auto dir = dirFromKeyboard() + dirFromGamepad();
		return !(dir.length() > 0.0f) ? Vector3f::Zero : dir.normalize();
	}

	Vector3f PlayerControll::dirFromGamepad() {
		auto dir2f = Input::Get()->getGamepadLeftStickAxis();

		float camera_y = mainCamera->transform()->getLocalRotation().toEuler().y ;

		Vector3f dirh;
		if (Input::Get()->isButtonHold(ButtonCode::Gamepad_X)) {
			dirh += Vector3f::Up;
		}
		if (Input::Get()->isButtonHold(ButtonCode::Gamepad_B)) {
			dirh += Vector3f::Down;
		}
		auto dir = Vector3f(dir2f.x, dirh.y, dir2f.y);

		dir = Quaternion().Euler(0.0f, camera_y, 0.0f) *  dir;
		transform()->setRotation(Quaternion().Euler(0.0f, camera_y, 0.0f));

		return !(dir.length() > 0.0f) ? Vector3f::Zero : dir.normalize();
	}

	Vector3f PlayerControll::dirFromKeyboard() {
		Vector3f dir;

		float camera_y = mainCamera->transform()->getLocalRotation().toEuler().y ;
		if (Input::Get()->isButtonHold(ButtonCode::W)) {
			dir += Vector3f::Forward;
		}
		if (Input::Get()->isButtonHold(ButtonCode::A)) {
			dir += Vector3f::Left;
		}
		if (Input::Get()->isButtonHold(ButtonCode::S)) {
			dir += Vector3f::Back;
		}
		if (Input::Get()->isButtonHold(ButtonCode::D)) {
			dir += Vector3f::Right;
		}
		if (Input::Get()->isButtonHold(ButtonCode::Space)) {
			dir += Vector3f::Up;
		}
		if (Input::Get()->isButtonHold(ButtonCode::LCtrl)) {
			dir += Vector3f::Down;
		}
		if (Input::Get()->isButtonHold(ButtonCode::RCtrl)) {
			dir += Vector3f::Down;
		}

		dir = Quaternion().Euler(0.0f, camera_y, 0.0f) * dir;
		transform()->setRotation(Quaternion().Euler(0.0f, camera_y, 0.0f));

		return dir.length() > 0.0f ? dir.normalize() : Vector3f::Zero;
	}
