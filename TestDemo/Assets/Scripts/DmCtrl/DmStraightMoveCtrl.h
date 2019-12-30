#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../Utils/DmPool.h"

using namespace Mix;

class DmStraightMoveCtrl final : public Script {
MX_DECLARE_RTTI

public:
    DmStraightMoveCtrl() = default;
    ~DmStraightMoveCtrl() = default;

    DmStraightMoveCtrl(HDmPool _poo,
                       const float _speed) : speed(_speed),
                                             pool(std::move(_poo)) {}

    void add(const HGameObject& _dm);
    void clearAll();

private:
    void update() override;

    float speed;
    std::vector<HGameObject> dmList;
    HDmPool pool;
};

using HDmStraightMoveCtrl = SceneObjectHandle<DmStraightMoveCtrl>;
