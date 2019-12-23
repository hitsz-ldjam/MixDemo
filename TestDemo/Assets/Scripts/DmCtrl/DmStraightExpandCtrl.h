#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class DmStraightExpandCtrl final : public Script {
MX_DECLARE_RTTI

public:
    DmStraightExpandCtrl() = default;
    ~DmStraightExpandCtrl() {
        puts("DmStarightExpandCtrl DTOR");
        system("pause");
    };

    DmStraightExpandCtrl(const float _speedSlow,
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

using HDmStraightExpandCtrl = SceneObjectHandle<DmStraightExpandCtrl>;
