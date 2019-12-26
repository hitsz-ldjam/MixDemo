#include "BombDmMove.h"
#include "../../../../Mx/Component/Transform/MxTransform.h"
#include "../../../../Mx/Time/MxTime.h"
#include "../StateMachine/StateMachine.h"
#include "../../../../Mx/GameObject/MxGameObject.h"

MX_IMPLEMENT_RTTI(BombDmMove, Script)

BombDmMove::BombDmMove(HDmPool _pool,
                       const float _maxRadius,
                       const float _expandTime,
                       const float _forwardSpeed,
                       const float _waitTime) : pool(std::move(_pool)),
                                                maxRadius(_maxRadius),
                                                expandTime(_expandTime),
                                                forwardSpeed(_forwardSpeed),
                                                waitTime(_waitTime),
                                                state(State::Dead),
                                                vel(2 * maxRadius / expandTime),
                                                acc(-vel / expandTime) {}

void BombDmMove::start() {
    center = transform()->getPosition();
    state = State::Expand;
}

void BombDmMove::update() {
    switch(state) {
        case State::Expand:
        {
            vel += acc * Time::DeltaTime();
            transform()->translate(0, 0, vel * Time::DeltaTime());
            if(vel <= 0)
                state = State::Wait;
            break;
        }

        case State::Wait:
        {
            auto rel = transform()->getPosition() - center;
            rel = Quaternion::AngleAxis(Math::Radians(60.f) * Time::DeltaTime(),
                                        StateMachine::enemy->transform().getPosition() - center) * rel;
            transform()->setPosition(center + rel);
            if(waitTime < 0)
                state = State::Forward;
            waitTime -= Time::DeltaTime();
            break;
        }

        case State::Forward:
        {
            transform()->setRotation(Quaternion::LookRotation(StateMachine::enemy->transform().getPosition() - transform()->getPosition()));
            transform()->translate(0, 0, forwardSpeed * Time::DeltaTime());
            if((transform()->getPosition() - StateMachine::enemy->transform().getPosition()).sqrLength() < 1)
                state = State::Die;
            break;
        }

        case State::Die:
        {
            pool->destoryDm(mGameObject);
            state = State::Dead;
            break;
        }

        default: break;
    }
}
