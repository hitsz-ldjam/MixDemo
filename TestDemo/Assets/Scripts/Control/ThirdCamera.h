#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../../../../Mx/Math/MxVector3.h"


using namespace Mix;

class PlayerAdapter;

class ThirdCamera final : public Script {
MX_DECLARE_RTTI;
public:
    ThirdCamera(HGameObject _CameraPivot)
        : CameraPivot(std::move(_CameraPivot)) { };

    ~ThirdCamera() = default ;

    void setfreeDistance(float _freeDistance);

    void setminDistance(float _minDistance);

    void setmaxDistance(float _maxDistance);

    void iscanControlDistance(bool _canControlDistance);

    void setdistanceSpeed(float _distanceSpeed);

    void setrotateSpeed(float _rotateSpeed);

    void setTargetBodyRotateLerp(float _TargetBodyRotateLerp);

    void isCanControlDirection(bool _CanControlDirection);

    void setmaxDepression(float _maxDepression);

    void setmaxEvelation(float _maxEvelation);

    float Clamp(float _clamp, float _x, float _y);

private:

    float freeDistance = 5.0f;

    float minDistance = 2.5f;

    float maxDistance = 6.0f;

    bool canControlDistance = true;

    float distanceSpeed = 1.0f;

    float rotateSpeed = .01f;

    float TargetBodyRotateLerp = 0.3f;

    HGameObject CameraPivot;

    bool CanControlDirection = false;

    Vector3f PredictCameraPosition;

    Vector3f offset;

    float maxDepression = 8.0f;

    float maxEvelation = 8.0f;

    void start() override;

    void update() override;

    void fixedUpdate() override;

    void FreeCamera();

    SceneObjectHandle<PlayerAdapter> mAdapter;

};

using HThirdCamera = SceneObjectHandle<ThirdCamera>;
