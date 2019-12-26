#pragma once
#include "../../../Mx/Component/Script/MxScript.h"
#include "Utils/SimpleMaterials.h"
#include "Utils/DmPool.h"

using namespace Mix;

class GameMgr final : public Script {
MX_DECLARE_RTTI

public:
    GameMgr() = default;
    ~GameMgr() = default;

    GameMgr(HGameObject _player,
            HGameObject _enemy,
            HDmPool _ballPool,
            HDmPool _bigballPool);

private:
    void start() override;
    void update() override;

    HGameObject player, enemy;
    HDmPool ballPool, bigballPool;

    enum class State {
        Dead,
        Spell1Start,
        Spell1Con,
        Spell1End,
        Spell3Start,
        Spell3Con,
        Spell3End,
        Spell6Start,
        Spell6Con,
        Spell6End,
    } state = State::Dead;
};

using HGameMgr = SceneObjectHandle<GameMgr>;
