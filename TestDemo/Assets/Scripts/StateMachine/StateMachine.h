#pragma once
#include "../../../../Mx/Definitions/MxDefinitions.h"

using namespace Mix;

class GameMgr;
class EnemyHealth;
class PlayerHealth;
class BombCtrl;

#define CLEAR_DM_STATES (StateMachine::playerState == StateMachine::PlayerState::PlayerLoseLife \
|| StateMachine::playerState == StateMachine::PlayerState::PlayerLoseLifeHandled \
|| StateMachine::bombState == StateMachine::BombState::BombTriggered)

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
        //BombHandled
    } bombState;

    static HGameObject player, enemy;

    static SceneObjectHandle<GameMgr> gameMgr;
    static SceneObjectHandle<EnemyHealth> enemyHealth;
    static SceneObjectHandle<PlayerHealth> playerHealth;
    static SceneObjectHandle<BombCtrl> playerBombCtrl;

    static void Update();

    StateMachine() = delete;

private:
};
