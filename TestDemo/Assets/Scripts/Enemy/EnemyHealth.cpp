#include "EnemyHealth.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(EnemyHealth, Script)

float EnemyHealth::getHealth() const { return health; }

void EnemyHealth::setHealth(float _d) { health = _d; }

void EnemyHealth::dealDamage(float _d) { health -= _d; }

float EnemyHealth::getTime() const { return timeCnt; }

void EnemyHealth::setTime(float _t) { timeCnt = _t; }

void EnemyHealth::start() { }

void EnemyHealth::update() {
    if(timeCnt <= 0) {
        timeCnt = 0;
        startCnt = false;
    }
    if(startCnt)
        timeCnt -= Time::DeltaTime();
}
