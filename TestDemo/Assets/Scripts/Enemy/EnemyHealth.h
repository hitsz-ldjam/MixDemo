#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class EnemyHealth final : public Script {
MX_DECLARE_RTTI

public:
    EnemyHealth() = default;
    ~EnemyHealth() = default;

    float getHealth() const;
    // note: this script only stores and does not alter health info
    void setHealth(float _d);
    void dealDamage(float _d);

    float getTime() const;
    void setTime(float _t);

    void startCounting() { startCnt = true; }

private:
    void start() override;
    void update() override;

    float health = 0,
          /*time,*/
          timeCnt = 0;

    bool startCnt = false;
};

using HEnemyHealth = SceneObjectHandle<EnemyHealth>;
