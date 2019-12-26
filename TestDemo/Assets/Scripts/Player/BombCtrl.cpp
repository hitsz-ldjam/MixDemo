#include "BombCtrl.h"
#include "BombDmMove.h"
#include "../StateMachine/StateMachine.h"
#include "../Utils/SimpleMaterials.h"
#include "../../../../Mx/Input/MxInput.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../Mx/Time/MxTime.h"

BombCtrl::BombCtrl(HDmPool _pool) : pool(std::move(_pool)) {}

void BombCtrl::update() {
    if(StateMachine::bombState != StateMachine::BombState::None) {
        if(bombTimeCnt <= 0) {
            bombTimeCnt = bombTime;
            StateMachine::bombState = StateMachine::BombState::None;
        }
        bombTimeCnt -= Time::DeltaTime();
    }

    if(Input::Get()->isButtonDown(ButtonCode::X)) {
        if(StateMachine::bombState == StateMachine::BombState::None) {
            StateMachine::bombState = StateMachine::BombState::BombTriggered;

            auto upAxis = -StateMachine::player->transform().forward();
            auto forwardAxis = StateMachine::player->transform().right();
            auto delta = Quaternion::AngleAxis(Math::Radians(60.f), upAxis);

            std::shared_ptr<Material> mats[] = {
                SimpleMaterials::Red(),
                SimpleMaterials::Green(),
                SimpleMaterials::Blue(),
                SimpleMaterials::Red(),
                SimpleMaterials::Green(),
                SimpleMaterials::Blue()
            };

            for(int i = 0; i < 6; ++i) {
                auto& playerTrans = StateMachine::player->transform();
                auto dm = pool->createDm();
                dm->transform().setPosition(playerTrans.getPosition() + playerTrans.forward() * 5);
                dm->transform().setRotation(Quaternion::LookRotation(forwardAxis, upAxis));

                dm->getComponent<Renderer>()->setMaterial(mats[i]);

                auto scrp = dm->addComponent<BombDmMove>(pool,
                                                         maxRadius,
                                                         expandTime,
                                                         forwardSpeed,
                                                         waitTime + waitTimeStep * i);

                forwardAxis = delta * forwardAxis;
            }
        }
    }
}
