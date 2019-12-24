#pragma once
#include "../../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class Spell03SwTail final : public Script {
MX_DECLARE_RTTI

public:
    Spell03SwTail() = default;
    ~Spell03SwTail() = default;

private:
    void start() override;
    void update() override;
};

using HSpell03SwTail = SceneObjectHandle<Spell03SwTail>;
