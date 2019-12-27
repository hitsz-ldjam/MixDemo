#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

// todo
class DmCurveExpandCtrl final : public Script {
MX_DECLARE_RTTI

public:
    DmCurveExpandCtrl() = default;
    ~DmCurveExpandCtrl() = default;

    DmCurveExpandCtrl(const float _speedSlow,
                      const float _speedExpand,
                      const float _waitSec,
                      const size_t _initCap = 0);

    void add(const HGameObject& _dm);

private:
    void start() override;
    void update() override;

    std::vector<HGameObject> dmList;
    float speed, speedExpand, waitSec;
};

using HDmCurveExpandCtrl = SceneObjectHandle<DmCurveExpandCtrl>;
