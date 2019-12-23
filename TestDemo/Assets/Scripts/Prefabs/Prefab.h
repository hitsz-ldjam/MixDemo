#pragma once
#include "../../../../Mx/GameObject/MxGameObject.h"

namespace Mix {
    class Material;
}

using namespace Mix;

using ModelPath = std::string;
using TexturePaths = std::vector<std::string>;
using MaterialCache = std::vector<std::shared_ptr<Material>>;

/** @deprecated */
class Prefab {
public:
    virtual ~Prefab() = default;
    virtual HGameObject instantiate(const std::string& _name, const Tag& _tag = "") = 0;
};

class Prefab2 final {
public:
    Prefab2(const ModelPath& _modelPath,
            const TexturePaths& _texturePaths);

    Prefab2(const ModelPath& _modelPath,
            const TexturePaths& _texturePaths,
            std::function<void(const HGameObject&)> _addComp);

    ~Prefab2() = default;

    HGameObject instantiate(const std::string& _name, const Tag& _tag = "") const;

protected:
    std::shared_ptr<Model> model;
    MaterialCache mats;
    std::function<void(const HGameObject&)> addComp;
};
