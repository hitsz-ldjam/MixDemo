#include "GameMgr.h"
#include "Prefabs/Prefab.h"
#include "Utils/SimpleMaterials.h"
#include "StateMachine/StateMachine.h"
#include "Player/PlayerHealth.h"
#include "Enemy/Spell06/Spell06MasterCtrl.h"
#include "Enemy/Spell03/Spell03BlueSphere.h"
#include "Enemy/Spell03/Spell03SwTail.h"
#include "Enemy/EnemyHealth.h"
#include "../../../Mx/Input/MxInput.h"
#include "../../../Mx/Resource/Audio/MxAudioClip.h"
#include "../../../Mx/Component/AudioSource/MxAudioSource.h"
#include "../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(GameMgr, Script)

#define AddStateComp(x) stateComp.emplace_back(static_scene_object_cast<Component>((x)))

GameMgr::GameMgr(HGameObject _player,
                 HGameObject _enemy,
                 HDmPool _ballPool,
                 HDmPool _bigballPool,
                 HDmPool _butterflyPool)
    : player(std::move(_player)),
      enemy(std::move(_enemy)),
      ballPool(std::move(_ballPool)),
      bigballPool(std::move(_bigballPool)),
      butterflyPool(std::move(_butterflyPool)) {}

void GameMgr::awake() {}

void GameMgr::start() {
    // todo
    {
        auto clip = std::make_shared<AudioClip>("TestDemo/Assets/Audio/bgm.flac");
        clip->load();
        enemy->addComponent<AudioSource>(clip, true, true)->setVolume(0.75);
    }

    state = State::Spell3Start;
}

void GameMgr::update() {
    static float timer = 0;

    // for demo
    if(Input::Get()->isButtonDown(ButtonCode::R)) {
        player->getComponent<PlayerHealth>()->miss();
    }
    if(Input::Get()->isButtonDown(ButtonCode::N)) {
        StateMachine::enemyHealth->setTime(0);
        StateMachine::enemyHealth->setHealth(0);
    }

    // todo: use ui
    if(Input::Get()->isButtonDown(ButtonCode::Tab)) {
        printf("********\nplay: %d\nbomb: %d\nenemy health: %f\nenemy time: %f\n********\n\n",
               StateMachine::playerHealth->getPlayerNum(),
               StateMachine::playerBombCtrl->getBombNum(),
               StateMachine::enemyHealth->getHealth(),
               StateMachine::enemyHealth->getTime());
    }

    auto cleanComps = [&]() {
        for(auto& comp : stateComp)
            enemy->removeComponent(comp);
        stateComp.clear();
    };

    if(StateMachine::playerState == StateMachine::PlayerState::PlayerDie) {
        cleanComps();
        state = State::Die;
    }

    switch(state) {
        case State::Dead:
            break;

        case State::Spell3Start:
        {
            // todo: show sensu

            AddStateComp(enemy->addComponent<Spell03BlueSphere>(player, bigballPool));
            AddStateComp(enemy->addComponent<Spell03SwTail>(player, butterflyPool));
            StateMachine::enemyHealth->setTime(30);
            StateMachine::enemyHealth->setHealth(2000);
            StateMachine::enemyHealth->startCounting();
            state = State::Spell3Exec;
            break;
        }

        case State::Spell3Exec:
        {
            if(StateMachine::enemyHealth->getHealth() <= 0 || StateMachine::enemyHealth->getTime() <= 0) {
                timer = 3;
                cleanComps();
                state = State::Spell3End;
            }
        }
        break;

        case State::Spell3End:
        {
            if(timer <= 0)
                state = State::Spell6Start;
            timer -= Time::DeltaTime();
        }
        break;

        case State::Spell6Start:
        {
            AddStateComp(enemy->addComponent<Spell06MasterCtrl>(butterflyPool));
            StateMachine::enemyHealth->setTime(60);
            StateMachine::enemyHealth->setHealth(-1);
            StateMachine::enemyHealth->startCounting();
            state = State::Spell6Exec;
        }
        break;

        case State::Spell6Exec:
        {
            if(StateMachine::enemyHealth->getTime() <= 0) {
                timer = 3;
                cleanComps();
                state = State::Spell6End;
            }
        }
        break;

        case State::Spell6End:
        {
            if(timer <= 0)
                state = State::Win;
            timer -= Time::DeltaTime();
        }
        break;

        case State::Die:
        {
            // todo: image
            puts("--- Chuang Yi ---");
        }

        case State::Win:
        {
            // todo: display img
            puts("--- Congratulations ---");
        }

        default: ;
    }
}
