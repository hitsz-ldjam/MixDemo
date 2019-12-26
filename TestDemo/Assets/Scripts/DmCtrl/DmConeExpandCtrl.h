#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../../../../Mx/Math/MxVector.h"

using namespace Mix;

class DmConeExpandCtrl final : public Script {
    MX_DECLARE_RTTI

public:
    DmConeExpandCtrl() = default;
    ~DmConeExpandCtrl() = default;

    DmConeExpandCtrl(const float _speedSlow,
        const float _speedExpand,
        Vector3f _PlayerPos,
        const float _waitSec,
        const size_t _initCap = 0);

    void add(const HGameObject& _dm);

private:
    void start() override;
    void update() override;

    std::vector<HGameObject> dmList;
    float speed, speedExpand, waitSec;
    Vector3f PlayerPos;
};

using HDmConeExpandCtrl = SceneObjectHandle<DmConeExpandCtrl>;