#include "Spell03BfMstCtrl.h"
#include "../../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(Spell03BfMstCtrl, Script)

Spell03BfMstCtrl::Spell03BfMstCtrl(const Vector3f& _forwardDir,
                                   const float _maxRadius,
                                   const float _forwardTime,
                                   HDmPool& _pool) : forwardDir(_forwardDir),
                                                     maxRadius(_maxRadius),
                                                     forwardTime(_forwardTime),
                                                     pool(_pool),
                                                     state(State::Forward),
                                                     vel(2 * maxRadius / forwardTime),
                                                     acc(-vel / forwardTime) {}

void Spell03BfMstCtrl::add(const HGameObject& _dm) {
    dmList.push_back(_dm);
}

void Spell03BfMstCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, Spell03BfMstCtrl* _this) {
        _this->state = State::Forward;
        yield_return(new Coroutine::WaitForSeconds(_this->forwardTime));
        _this->state = State::Backward;
        yield_return(new Coroutine::WaitForSeconds(_this->forwardTime - 0.05f)); // magic
        _this->state = State::Die;
    }, this);
}

void Spell03BfMstCtrl::update() {
    vel += acc * Time::DeltaTime();

    switch(state) {
            // todo bug
        case State::Forward:
        case State::Backward:
        {
            for(auto& dm : dmList) {
                dm->transform().translate(Vector3f(0, 0, vel * Time::DeltaTime()));
                //auto& pos = dm->transform().getLocalPosition();
                //dm->transform().setLocalPosition(pos + vel * Time::DeltaTime() * forwardDir);
            }
            break;
        }

            //case State::Backward:
            //{
            //    for(auto& dm : dmList) {
            //        auto& pos = dm->transform().getLocalPosition();
            //        dm->transform().setLocalPosition(pos + vel * Time::DeltaTime() * forwardDir);
            //    }
            //    break;
            //}

        case State::Die:
        {
            for(auto& dm : dmList) {
                pool->destoryDm(dm);
            }
            state = State::Dead;
            break;
        }

        default: break;
    }
}
