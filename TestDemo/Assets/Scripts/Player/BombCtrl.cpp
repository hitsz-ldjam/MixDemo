#include "BombCtrl.h"
#include "BombDmMove.h"
#include "../StateMachine/StateMachine.h"
#include "../Utils/SimpleMaterials.h"
#include "../../../../Mx/Input/MxInput.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../Mx/Component/Renderer/MxRenderer.h"
#include "../../../../Mx/Time/MxTime.h"

BombCtrl::BombCtrl(HDmPool _pool) : pool(std::move(_pool)),
                                    bombTimeCnt(bombTime),
                                    bombCnt(maxBombNum) {}

int BombCtrl::getBombNum() {
    return bombCnt;
}

void BombCtrl::resumeBomb() {
    bombCnt = maxBombNum;
}

void BombCtrl::update() {
    if(StateMachine::bombState != StateMachine::BombState::None) {
        if(bombTimeCnt <= 0) {
            bombTimeCnt = bombTime;
            StateMachine::bombState = StateMachine::BombState::None;
        }
        bombTimeCnt -= Time::DeltaTime();
    }

    if(bombCnt && Input::Get()->isButtonDown(ButtonCode::X)) {
        if(StateMachine::bombState == StateMachine::BombState::None
           && StateMachine::playerState == StateMachine::PlayerState::None) {
            --bombCnt;

            StateMachine::bombState = StateMachine::BombState::BombTriggered;

            auto upAxis = -StateMachine::player->transform().forward();
            auto forwardAxis = StateMachine::player->transform().right();
            auto delta = Quaternion::AngleAxis(Math::Radians(60.f), upAxis);

            std::shared_ptr<Material> mats[] = {
                SimpleMaterials::redMat,
                SimpleMaterials::greenMat,
                SimpleMaterials::blueMat,
                SimpleMaterials::redMat,
                SimpleMaterials::greenMat,
                SimpleMaterials::blueMat
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
