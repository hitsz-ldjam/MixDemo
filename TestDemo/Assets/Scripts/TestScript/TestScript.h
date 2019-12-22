#pragma once

#ifndef TESTSCRIPT_H_
#define TESTSCRIPT_H_

#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class TestScript final : public Script {
MX_DECLARE_RTTI

public:
    TestScript() = default;
    ~TestScript() = default;

private:
    void start() override;
    void update() override;
};

using HTestScript = SceneObjectHandle<TestScript>;

#endif
