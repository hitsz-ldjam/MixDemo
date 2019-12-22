#pragma once

#ifndef TESTDEMO_H_
#define TESTDEMO_H_

#include "../MxApplicationBase.h"
#include "../Mx/Definitions/MxDefinitions.h"

using namespace Mix;

class TestDemo final : public ApplicationBase {
public:
    static HGameObject CreateGameObjFromModel(const std::string& _name,
                                              const std::string& _modelPath,
                                              const std::vector<std::string>& _texturePaths);

    std::string getAppName() const override;
    Version getAppVersion() const override;

private:
    void onMainSceneCreated() override;
};

#endif
