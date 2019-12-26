#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class DmStraightMoveSingle final : public Script {
MX_DECLARE_RTTI

public:
    DmStraightMoveSingle() = default;
    ~DmStraightMoveSingle() = default;

    float speed = 0;

private:
    void start() override;
    void update() override;
};

using HDmStraightMoveSingle = SceneObjectHandle<DmStraightMoveSingle>;
