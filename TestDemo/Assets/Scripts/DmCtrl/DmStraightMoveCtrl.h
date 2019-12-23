#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class DmStraightMoveCtrl final : public Script {
MX_DECLARE_RTTI

public:
    DmStraightMoveCtrl() = default;
    ~DmStraightMoveCtrl() = default;

    DmStraightMoveCtrl(const float _speed) : speed(_speed) {}

    void add(const HGameObject& _dm);

private:
    void update() override;

    float speed;
    std::vector<HGameObject> dmList;
};

using HDmStraightMoveCtrl = SceneObjectHandle<DmStraightMoveCtrl>;
