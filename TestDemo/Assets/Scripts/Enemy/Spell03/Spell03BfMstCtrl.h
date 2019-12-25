#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../../../../Mx/Math/MxVector3.h"
#include "../../Utils/DmPool.h"

using namespace Mix;

class Spell03BfMstCtrl final : public Script {
MX_DECLARE_RTTI

public:
    Spell03BfMstCtrl() = default;
    ~Spell03BfMstCtrl() = default;

    Spell03BfMstCtrl(const Vector3f& _forwardDir,
                     const float _maxRadius,
                     const float _forwardTime,
                     HDmPool& _pool);

    void add(const HGameObject& _dm);

private:
    void start() override;
    void update() override;

    Vector3f forwardDir;
    float maxRadius;
    float forwardTime;
    HDmPool pool;

    enum class State {
        Dead,
        Forward,
        Backward,
        Die
    };

    State state;
    float vel, acc;
    std::vector<HGameObject> dmList;
};

using HSpell03BfMstCtrl = SceneObjectHandle<Spell03BfMstCtrl>;
