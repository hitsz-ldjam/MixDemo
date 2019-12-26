#pragma once
#include "../../../../Mx/Definitions/MxDefinitions.h"

using namespace Mix;

class StateMachine final {
public:
    static enum class PlayerState {
        None,
        PlayerLoseLife,
        PlayerLoseLifeHandled,
        PlayerDie
    } playerState;

    static enum class BombState {
        None,
        BombTriggered,
        BombHandled
    } bombState;

    static HGameObject player, enemy;

    static void Update();

    StateMachine() = delete;

private:
};
