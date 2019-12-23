#include "PrefabUilts.h"
#include "../../../../Mx/Graphics/Texture/MxTexture.h"
#include "../../../../Mx/Graphics/MxMaterial.h"
#include "../../../../Mx/Graphics/MxGraphics.h"
#include "../../../../Mx/Resource/Model/MxModel.h"
#include "../../../../Mx/Resource/MxResourceLoader.h"
#include "../../../../Mx/Component/Renderer/MxRenderer.h"

HGameObject PrefabUtils::CreateGameObjFromModel(const std::string& _name,
                                                const std::string& _modelPath,
                                                const std::vector<std::string>& _texturePaths) {
    auto obj = ResourceLoader::Get()->load<Model>(_modelPath)->genDefaultGameObjects(_name);

    std::vector<std::shared_ptr<Material>> mats;
    mats.reserve(_texturePaths.size());
    for(auto& path : _texturePaths) {
        auto mat = std::make_shared<Material>(Graphics::Get()->findShader("Standard"));
        mat->setTexture("diffuseTex", ResourceLoader::Get()->load<Texture>(path));
        mats.emplace_back(std::move(mat));
    }

    obj->addComponent<Renderer>()->setMaterials(std::move(mats));
    return obj;
}
