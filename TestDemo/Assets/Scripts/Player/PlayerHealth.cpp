#include "PlayerHealth.h"
#include "../StateMachine/StateMachine.h"

MX_IMPLEMENT_RTTI(PlayerHealth, Script)

PlayerHealth::PlayerHealth(HAudioSource _asrc)
    : asrc(std::move(_asrc)) {}

void PlayerHealth::miss() {
    if(StateMachine::playerState == StateMachine::PlayerState::None) {

        StateMachine::playerState = StateMachine::PlayerState::PlayerLoseLife;
    }
}

void PlayerHealth::start() {
    
}

void PlayerHealth::update() {
    
}
