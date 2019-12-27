#include "StateMachine.h"
#include "../GameMgr.h"
#include "../Enemy/EnemyHealth.h"
#include "../Player/PlayerHealth.h"
#include "../../../../Mx/Scene/MxSceneObjectHandle.h"

StateMachine::PlayerState StateMachine::playerState = PlayerState::None;

StateMachine::BombState StateMachine::bombState = BombState::None;

HGameObject StateMachine::player, StateMachine::enemy;

HGameMgr StateMachine::gameMgr;
HEnemyHealth StateMachine::enemyHealth;
HPlayerHealth StateMachine::playerHealth;
HBombCtrl StateMachine::playerBombCtrl;

void StateMachine::Update() {}
