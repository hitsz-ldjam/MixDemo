#include "PlayerHealth.h"
#include "../StateMachine/StateMachine.h"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../Mx/Resource/Audio/MxAudioClip.h"
#include "../../../../Mx/Component/AudioSource/MxAudioSource.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(PlayerHealth, Script)

PlayerHealth::PlayerHealth(const int _playerNum) : playerNum(_playerNum) {}

void PlayerHealth::miss() {
    if(StateMachine::playerState == StateMachine::PlayerState::None) {
        asrc->resume();
        asrc->setPosition(0);
        asrc->resume();

        --playerNum;
        if(playerNum < 0) {
            StateMachine::playerState = StateMachine::PlayerState::PlayerDie;
            StateMachine::enemy->getComponent<AudioSource>()->pause();
            return;
        }

        bombCtrl->resumeBomb();
        StateMachine::playerState = StateMachine::PlayerState::PlayerLoseLife;
    }
}

void PlayerHealth::awake() {
    auto clip = std::make_shared<AudioClip>("TestDemo/Assets/Audio/biu.wav");
    clip->load();
    asrc = mGameObject->addComponent<AudioSource>(clip, false);
    asrc->setVolume(1.4);

    StateMachine::playerState = StateMachine::PlayerState::None;
}

void PlayerHealth::start() {
    bombCtrl = mGameObject->getComponent<BombCtrl>();
}

void PlayerHealth::update() {
    static float timer = 5;
    switch(StateMachine::playerState) {
        case StateMachine::PlayerState::None: break;

        case StateMachine::PlayerState::PlayerLoseLife:
        {
            timer = 5;
            StateMachine::playerState = StateMachine::PlayerState::PlayerLoseLifeHandled;
        }
        break;

        case StateMachine::PlayerState::PlayerLoseLifeHandled:
        {
            if(timer < 0)
                StateMachine::playerState = StateMachine::PlayerState::None;
            timer -= Time::DeltaTime();
        }
        break;

        case StateMachine::PlayerState::PlayerDie: break;

        default: break;
    }
}
