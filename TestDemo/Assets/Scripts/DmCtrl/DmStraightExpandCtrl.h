#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../Utils/DmPool.h"

using namespace Mix;

class DmStraightExpandCtrl final : public Script {
MX_DECLARE_RTTI

public:
    DmStraightExpandCtrl() = default;
    ~DmStraightExpandCtrl() = default;

    // todo: must be the same pool
    DmStraightExpandCtrl(HDmPool _pool,
                         const float _speedSlow,
                         const float _speedExpand,
                         const float _waitSec,
                         const size_t _initCap = 0);

    void add(const HGameObject& _dm);

    void clearAll();

private:
    void start() override;
    void update() override;
    void lateUpdate() override;

    std::vector<HGameObject> dmList;
    float speed, speedExpand, waitSec;
    HDmPool pool;
};

using HDmStraightExpandCtrl = SceneObjectHandle<DmStraightExpandCtrl>;
