#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class CameraCtrl final : public Script {
MX_DECLARE_RTTI

public:
    CameraCtrl() = default;
    ~CameraCtrl() = default;

    CameraCtrl(HGameObject _target);

private:
    void start() override;
    void update() override;

    HGameObject target;
};

using HCameraCtrl = SceneObjectHandle<CameraCtrl>;
