#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"
#include "../../Utils/DmPool.h"
#include "../../../../../Mx/Math/MxRandom.h"

using namespace Mix;

// add this to enemy
class Spell03SwTail final : public Script {
MX_DECLARE_RTTI

public:
    Spell03SwTail() = default;
    ~Spell03SwTail() = default;

    Spell03SwTail(HGameObject _player,
                  HDmPool _pool);

    void forceClearDm();

private:
    void start() override;
    void update() override;

    HGameObject shootSingleLayer(const Vector3f& _masterPos,
                                 const Quaternion& _masterRot,
                                 const std::shared_ptr<Material>& _mat,
                                 const float _maxRadius,
                                 const float _forwardTime,
                                 const float _rotSpeed,
                                 const bool _clockWise);

    void shootBf();

    HGameObject player;
    HDmPool pool; // pool for bf dm
    Random rnd;
    std::vector<HGameObject> masters;
};

using HSpell03SwTail = SceneObjectHandle<Spell03SwTail>;
