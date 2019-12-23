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
            HDmPool _bigballPool);

private:
    void start() override;
    void update() override;

    HGameObject player, enemy;
    HDmPool bigballPool;
};

using HGameMgr = SceneObjectHandle<GameMgr>;
