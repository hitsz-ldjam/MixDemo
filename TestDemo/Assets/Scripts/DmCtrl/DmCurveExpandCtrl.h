#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class DmCurveExpandCtrl final : public Script {
MX_DECLARE_RTTI

public:
    DmCurveExpandCtrl() = default;
    ~DmCurveExpandCtrl() = default;

private:
    void start() override;
    void update() override;
};

using HDmCurveExpandCtrl = SceneObjectHandle<DmCurveExpandCtrl>;
