#include "TestDemo.h"
#include "../Mx/GameObject/MxGameObject.h"
#include "../Mx/Resource/MxResourceLoader.h"
#include "../Mx/Resource/Model/MxModel.h"
#include "../Mx/Scene/MxScene.h"
#include "../Mx/Scene/MxSceneManager.h"
#include "../Mx/Component/Camera/MxCamera.h"
#include "../Mx/Component/Renderer/MxRenderer.h"
#include "../Mx/Graphics/MxGraphics.h"
#include "../Mx/Graphics/MxMaterial.h"
#include "../Mx/Graphics/Texture/MxTexture.h"

#include "Assets/Scripts/TestScript/TestScript.h"

HGameObject TestDemo::CreateGameObjFromModel(const std::string& _name,
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

std::string TestDemo::getAppName() const { return std::string("TestDemo"); }

Version TestDemo::getAppVersion() const { return Version(1, 0, 0); }

void TestDemo::onMainSceneCreated() {
    auto player = CreateGameObjFromModel("reimu",
                                         "TestDemo/Assets/Models/reimu/reimu.gltf",
                                         {
                                             "TestDemo/Assets/Models/reimu/te3.png",
                                             "TestDemo/Assets/Models/reimu/te1.png",
                                             "TestDemo/Assets/Models/reimu/te2.png"
                                         });
    player->transform().translate(0, 0, 5);

    auto camera = SceneManager::Get()->getActiveScene()->getMainCamera();
    camera->transform()->setPosition(Vector3f::Zero);
    camera->transform()->setRotation(Quaternion::LookRotation(Vector3f::Forward));
}
