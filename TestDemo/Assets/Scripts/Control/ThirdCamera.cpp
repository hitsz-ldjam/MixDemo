#include "ThirdCamera.h"
#include "PlayerAdapter.h"
#include "../../../../Mx/Math/MxQuaternion.h"
#include "../../../../Mx/Input/MxInput.h"
#include "../../../../Mx/Component/Transform/MxTransform.h"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../Mx/Log/MxLog.h"

MX_IMPLEMENT_RTTI(ThirdCamera, Script);

void ThirdCamera::start() {

    mAdapter = mGameObject->getComponent<PlayerAdapter>();

    offset = transform()->getPosition() - CameraPivot->transform().getPosition();
}

void ThirdCamera::update() {
    FreeCamera();
}

void ThirdCamera::fixedUpdate() { }

void ThirdCamera::FreeCamera() {
    offset = offset.normalize() * freeDistance;

    transform()->setPosition(Vector3f::Lerp(transform()->getPosition(),
        CameraPivot->transform().getPosition() + offset, 1.0f));

    if (CanControlDirection) {
        Vector3f cam = transform()->getPosition();
        Vector3f TargetBodyNextRotation = CameraPivot->transform().getPosition() - cam;
        TargetBodyNextRotation.y = 0;
        Quaternion TargetBodyCurrentRotation = CameraPivot->transform().getRotation();
        if (TargetBodyNextRotation != Vector3f::Zero) {
            CameraPivot->transform().setRotation(Quaternion::LookRotation(TargetBodyNextRotation));
        }
    }
    //Log::Info("%1%", Input::Get()->getMousePositionDelta().x);
    if(canControlDistance) {
        float ScrollWheel = Input::Get()->getAxis(AxisCode::Mouse_WheelY);
        //if (Input::Get().getAxis(Mouse_WheelY)) {
        //	ScrollWheel
        //}
        freeDistance -= ScrollWheel * distanceSpeed;
    }


    float eulerX = transform()->getLocalRotation().toEuler().x;
    float inputY = Input::Get()->getMousePositionDelta().y;

    Vector3f Right = CameraPivot->transform().getPosition() - transform()->getPosition();
    Right.y = 0;
    Vector3f NewRight(Right.z, 0, -Right.x);

    //Mixcatch( Input::Get()->getMousePositionDelta().x);
    transform()->rotateAround(CameraPivot->transform().getPosition(),  
                                                                         Vector3f::Up, rotateSpeed * Input::Get()->getMousePositionDelta().x);


     transform()->rotateAround(CameraPivot->transform().getPosition() + fouces, 
                                                                         NewRight, rotateSpeedy * inputY);
    



    if (transform()->getLocalRotation().z) {
        float rotx = transform()->getLocalRotation().x;
        float roty = transform()->getLocalRotation().y;

        transform()->setLocalRotation(Quaternion::Euler(Vector3f(rotx, roty, 0.0f)));
    }

    transform()->lookAt(CameraPivot->transform().getPosition() + fouces);
    
    offset = transform()->getPosition() - CameraPivot->transform().getPosition();
    offset = offset.normalize() * freeDistance;
    transform()->setPosition(CameraPivot->transform().getPosition() + offset);
}

void ThirdCamera::Mixcatch(float _m) {
    mix += rotateSpeed * _m;
    if (mix >= 1.57f||
        mix<=-1.57f) {
        transform()->rotateAround(CameraPivot->transform().getPosition(),
            Vector3f::Up, -0.01f * Input::Get()->getMousePositionDelta().x);
    }
    else
    {
        setrotateSpeed(0.01f);
    }
}

float ThirdCamera::Clamp(float _clamp, float _x, float _y) {
    if(_clamp < _x) {
        return _x;
    }
    if(_clamp > _y) {
        return _y;
    }
    return _clamp;
}

float ThirdCamera::Angle(Vector3f _a, Vector3f _b) {
    float z = _a.z - _b.z;
    float y = _a.y - _b.y;
    float x = _a.x - _b.x;
    float Ag = atan2(abs(z), sqrt(x * x + y * y));
    return Ag;
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

void ThirdCamera::setrotateSpeedy(float _rotateSpeedy) {
    rotateSpeedy = _rotateSpeedy;
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
