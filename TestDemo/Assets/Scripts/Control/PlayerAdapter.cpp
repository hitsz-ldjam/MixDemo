#include "PlayerAdapter.h"
#include "PlayerControl.h"
#include "../../../../Mx/Component/Transform/MxTransform.h"
#include "../../../../Mx/Input/MxInput.h"


MX_IMPLEMENT_RTTI(PlayerAdapter, Script);

void PlayerAdapter::move(const Vector3f& _dir) {
    auto moveDir = _dir.length() > 0.0f ? _dir.normalize() : Vector3f::Zero;
    float mMoveSpeed = mHMoveSpeed;

    if(Input::Get()->isButtonHold(ButtonCode::RShift) || Input::Get()->isButtonHold(ButtonCode::LShift)) {
        mMoveSpeed = mLMoveSpeed;
    }

    mSmoothMove = Vector3f::Lerp(mSmoothMove, moveDir * mMoveSpeed, mAccelerate);
    mSmoothMove = Vector3f::Lerp(mSmoothMove, Vector3f::Zero, mDecelerate);
    transform()->translate(mSmoothMove.x, mSmoothMove.y, mSmoothMove.z, Space::Self);

    int hDir = moveDir.x > 0.0f ? -1 : (moveDir.x < 0.0f ? 1 : 0);

}


void PlayerAdapter::attack() {
    //auto weapon = mGameObject->getComponent<...>();
    //if (weapon != nullptr)
    //	weapon->attack();
}

void PlayerAdapter::setHMoveSpeed(float _Hspeed) {
    mHMoveSpeed = _Hspeed;
}

void PlayerAdapter::setLMoveSpeed(float _Lspeed) {
    mLMoveSpeed = _Lspeed;
}

void PlayerAdapter::awake() { }

void PlayerAdapter::start() { }

void PlayerAdapter::update() { }

void PlayerAdapter::fixedUpdate() { }
