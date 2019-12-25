#include "TestDemo.h"
#include "../Mx/GameObject/MxGameObject.h"
#include "../Mx/Scene/MxScene.h"
#include "../Mx/Scene/MxSceneManager.h"
#include "../Mx/Component/Camera/MxCamera.h"

#include "Assets/Scripts/Prefabs/PrefabUilts.h"
#include "Assets/Scripts/Prefabs/Prefab.h"
#include "Assets/Scripts/Camera/CameraCtrl.h"
#include "Assets/Scripts/GameMgr.h"
#include "Assets/Scripts/Utils/DmPool.h"
#include "Assets/Scripts/Utils/SimpleMaterials.h"
#include "Assets/Scripts/Control/ThirdCamera.h"
#include "Assets/Scripts/Control/PlayerControl.h"

std::string TestDemo::getAppName() const { return std::string("TestDemo"); }

Version TestDemo::getAppVersion() const { return Version(1, 0, 0); }

void TestDemo::onMainSceneCreated() {
    // utils
    SimpleMaterials::Init();

    // prefabs
    auto bigballPrefab = std::make_shared<Prefab2>("TestDemo/Assets/Models/bigball/BigBall.gltf", TexturePaths{});

    // player
    auto player = GameObject::Instantiate("player", "player");
    {
        auto reimu = PrefabUtils::CreateGameObjFromModel("reimu",
                                                         "TestDemo/Assets/Models/reimu/reimu.gltf",
                                                         {
                                                             "TestDemo/Assets/Models/reimu/te3.png",
                                                             "TestDemo/Assets/Models/reimu/te1.png",
                                                             "TestDemo/Assets/Models/reimu/te2.png"
                                                         });
        reimu->transform().rotate({0, 1, 0}, Math::Constants::Pi);
        reimu->setParent(player);
    }

    // enemy
    auto enemy = GameObject::Instantiate("enemy", "enemy");
    {
        auto yuyuko = PrefabUtils::CreateGameObjFromModel("yuyuko",
                                                          "TestDemo/Assets/Models/reimu/reimu.gltf",
                                                          {
                                                              "TestDemo/Assets/Models/reimu/te3_blue.png",
                                                              "TestDemo/Assets/Models/reimu/te1.png",
                                                              "TestDemo/Assets/Models/reimu/te2.png"
                                                          });
        yuyuko->transform().rotate({0, 1, 0}, Math::Constants::Pi);
        yuyuko->setParent(enemy);
    }
    enemy->transform().setPosition({0, 0, 25});
    enemy->transform().rotate({0, 1, 0}, -Math::Constants::Pi);

    // GameMgr
    auto gameMgr = GameObject::Instantiate("GameMgr");
    auto bigballPool = gameMgr->addComponent<DmPool>(bigballPrefab, "", "bigball", 1000);
    gameMgr->addComponent<GameMgr>(player, enemy, bigballPool);

    // camera
    auto camera = SceneManager::Get()->getActiveScene()->getMainCamera()->getGameObject();
    //camera->addComponent<CameraCtrl>(player);

    camera->transform().setPosition({0, 0, -20});
    camera->addComponent<ThirdCamera>(player);
    player->addComponent<PlayerAdapter>();
    player->addComponent<PlayerControl>(camera->getComponent<Camera>());
}
