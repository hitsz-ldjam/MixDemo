#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../../../../Mx/Math/MxVector3.h"
#include "PlayerAdapter.h"
#include "ThirdCamera.h"

using namespace Mix;

class PlayerControl final : public Script {
MX_DECLARE_RTTI;
public:
    PlayerControl(HCamera _Hcamera)
        : mainCamera(std::move(_Hcamera)) { }

    ~PlayerControl() = default;

private:
    void start() override;

    void update() override;

    void fixedUpdate() override;

    Vector3f getDir();

    Vector3f dirFromGamepad();

    Vector3f dirFromKeyboard();

    SceneObjectHandle<PlayerAdapter> mAdapter;

    HCamera mainCamera;

    SceneObjectHandle<ThirdCamera> mThirdCamera;

};

using HPlayerControll = SceneObjectHandle<PlayerControl>;
