#pragma once
#include "../../../Mx/Component/Script/MxScript.h"
#include "Utils/SimpleMaterials.h"
#include "Utils/DmPool.h"

using namespace Mix;

class GameMgr final : public Script {
MX_DECLARE_RTTI

public:
    enum class State {
        Dead,
        Spell3Start,
        Spell3Exec,
        Spell3End,
        Spell6Start,
        Spell6Exec,
        Spell6End,
        Die,
        Win
    };

    GameMgr() = default;
    ~GameMgr() = default;

    GameMgr(HGameObject _player,
            HGameObject _enemy,
            HDmPool _ballPool,
            HDmPool _bigballPool,
            HDmPool _butterflyPool);

    auto getState() { return state; }

private:
    void awake() override;
    void start() override;
    void update() override;

    HGameObject player, enemy;
    HDmPool ballPool, bigballPool, butterflyPool;

    State state = State::Dead;

    std::vector<HComponent> stateComp;
};

using HGameMgr = SceneObjectHandle<GameMgr>;
