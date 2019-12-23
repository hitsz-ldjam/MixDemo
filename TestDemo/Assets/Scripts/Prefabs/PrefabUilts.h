#pragma once

#include "../../../../Mx/Definitions/MxDefinitions.h"
#include <string>
#include <vector>

using namespace Mix;

class PrefabUtils final {
public:
    /** @deprecated */
    static HGameObject CreateGameObjFromModel(const std::string& _name,
                                              const std::string& _modelPath,
                                              const std::vector<std::string>& _texturePaths);
};
