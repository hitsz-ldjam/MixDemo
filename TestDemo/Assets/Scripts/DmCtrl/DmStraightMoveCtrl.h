#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class DmStraightMoveCtrl final : public Script {
MX_DECLARE_RTTI

public:
    DmStraightMoveCtrl() = default;
    ~DmStraightMoveCtrl() = default;

    DmStraightMoveCtrl(const float _speed) : speed(_speed) {}

private:
    void start() override;
    void update() override;

    float speed;
    std::vector<HGameObject> dmList;
};

using HDmStraightMoveCtrl = SceneObjectHandle<DmStraightMoveCtrl>;
