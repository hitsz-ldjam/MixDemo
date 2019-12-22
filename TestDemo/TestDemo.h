#pragma once

#ifndef TESTDEMO_H_
#define TESTDEMO_H_

#include "../MxApplicationBase.h"

using namespace Mix;

class TestDemo final : public ApplicationBase {
public:
    std::string getAppName() const override;
    Version getAppVersion() const override;

private:
    void onMainSceneCreated() override;
};

#endif
