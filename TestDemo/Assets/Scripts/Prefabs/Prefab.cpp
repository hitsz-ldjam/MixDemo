#include "Prefab.h"
#include "../../../../Mx/Graphics/Texture/MxTexture.h"
#include "../../../../Mx/Graphics/MxMaterial.h"
#include "../../../../Mx/Graphics/MxGraphics.h"
#include "../../../../Mx/Resource/Model/MxModel.h"
#include "../../../../Mx/Resource/MxResourceLoader.h"
#include "../../../../Mx/Component/Renderer/MxRenderer.h"

Prefab2::Prefab2(const ModelPath& _modelPath, const TexturePaths& _texturePaths)
    : Prefab2(_modelPath, _texturePaths, [](auto&) {}) {}

Prefab2::Prefab2(const ModelPath& _modelPath,
                 const TexturePaths& _texturePaths,
                 std::function<void(const HGameObject&)> _addComp)
    : model(ResourceLoader::Get()->load<Model>(_modelPath)),
      addComp(std::move(_addComp)) {
    mats.reserve(_texturePaths.size());
    for(auto& path : _texturePaths) {
        auto mat = std::make_shared<Material>(Graphics::Get()->findShader("Standard"));
        mat->setTexture("diffuseTex", ResourceLoader::Get()->load<Texture>(path));
        mats.emplace_back(std::move(mat));
    }
}

HGameObject Prefab2::instantiate(const std::string& _name, const Tag& _tag) const {
    auto obj = model->genDefaultGameObjects(_name, _tag);
    obj->addComponent<Renderer>()->setMaterials(mats);
    addComp(obj);
    return obj;
}
