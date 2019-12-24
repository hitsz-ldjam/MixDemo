#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../Utils/DmPool.h"

using namespace Mix;

class Spell03BlueSphere final : public Script {
MX_DECLARE_RTTI

public:
    Spell03BlueSphere() = default;
    ~Spell03BlueSphere() = default;

    Spell03BlueSphere(HGameObject _player,
                      HDmPool _pool);

private:
    void start() override;
    void update() override;

    HGameObject player;
    HDmPool pool;
};

using HSpell03BlueSphere = SceneObjectHandle<Spell03BlueSphere>;
