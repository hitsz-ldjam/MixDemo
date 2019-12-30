#include "PlayerControl.h"
#include "PlayerAdapter.h"
#include "../../../../Mx/Input/MxInput.h"
#include "../../../../Mx/Math/MxQuaternion.h"
#include "../../../../Mx/Scene/MxSceneManager.h"
#include "../../../../Mx/Component/Camera/MxCamera.h"


MX_IMPLEMENT_RTTI(PlayerControl, Script);

void PlayerControl::start() {
    mAdapter = mGameObject->getComponent<PlayerAdapter>();
    auto mainCamera = SceneManager::Get()->getActiveScene()->getMainCamera();
    auto camera = SceneManager::Get()->getActiveScene()->getMainCamera()->getGameObject();
    mThirdCamera = camera->getComponent<ThirdCamera>();
}

void PlayerControl::update() {
    mAdapter->move(getDir());

    //mAdapter->attack();
}

void PlayerControl::fixedUpdate() { }

Vector3f PlayerControl::getDir() {
    auto dir = dirFromKeyboard() + dirFromGamepad();
    return !(dir.length() > 0.0f) ? Vector3f::Zero : dir.normalize();
}

Vector3f PlayerControl::dirFromGamepad() {
    auto dir2f = Input::Get()->getGamepadLeftStickAxis();



    Vector3f dirh;
    if(Input::Get()->isButtonHold(ButtonCode::Gamepad_X)) {
        dirh += Vector3f::Up;
    }
    if(Input::Get()->isButtonHold(ButtonCode::Gamepad_B)) {
        dirh += Vector3f::Down;
    }
    if ((Input::Get()->getGamepadLeftStickAxis() != Vector2f::Zero) ||
        Input::Get()->isButtonHold(ButtonCode::Gamepad_X) ||
        Input::Get()->isButtonHold(ButtonCode::Gamepad_B) ) {
        mThirdCamera->isCanControlDirection(true);
    }
    else
    {
        mThirdCamera->isCanControlDirection(false);
    }
    auto dir = Vector3f(dir2f.x, dirh.y, dir2f.y);



    return !(dir.length() > 0.0f) ? Vector3f::Zero : dir.normalize();
}

Vector3f PlayerControl::dirFromKeyboard() {
    Vector3f dir;

    if(Input::Get()->isButtonHold(ButtonCode::W)) {
        dir += Vector3f::Forward;
    }
    if(Input::Get()->isButtonHold(ButtonCode::A)) {
        dir += Vector3f::Left;
    }
    if(Input::Get()->isButtonHold(ButtonCode::S)) {
        dir += Vector3f::Back;
    }
    if(Input::Get()->isButtonHold(ButtonCode::D)) {
        dir += Vector3f::Right;
    }
    if (Input::Get()->isButtonHold(ButtonCode::D) ||
        Input::Get()->isButtonHold(ButtonCode::S) ||
        Input::Get()->isButtonHold(ButtonCode::A) ||
        Input::Get()->isButtonHold(ButtonCode::W)) {
        mThirdCamera->isCanControlDirection(true);
    }
    else
    {
        mThirdCamera->isCanControlDirection(false);
    }
    /*if(Input::Get()->isButtonHold(ButtonCode::Space)) {
        dir += Vector3f::Up;
    }
    if(Input::Get()->isButtonHold(ButtonCode::LCtrl)) {
        dir += Vector3f::Down;
    }
    if(Input::Get()->isButtonHold(ButtonCode::RCtrl)) {
        dir += Vector3f::Down;
    }*/



    return dir.length() > 0.0f ? dir.normalize() : Vector3f::Zero;
}
