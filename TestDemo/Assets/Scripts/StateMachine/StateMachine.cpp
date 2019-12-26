#include "StateMachine.h"
#include "../../../../Mx/Scene/MxSceneObjectHandle.h"

StateMachine::PlayerState StateMachine::playerState = PlayerState::None;

StateMachine::BombState StateMachine::bombState = BombState::None;

HGameObject StateMachine::player, StateMachine::enemy;

void StateMachine::Update() {

}
