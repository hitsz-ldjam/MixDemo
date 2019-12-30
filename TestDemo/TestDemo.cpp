#include "TestDemo.h"
#include "../Mx/GameObject/MxGameObject.h"
#include "../Mx/Scene/MxScene.h"
#include "../Mx/Scene/MxSceneManager.h"
#include "../Mx/Component/Camera/MxCamera.h"
#include "../Mx/Component/AudioListener/MxAudioListener.h"
#include "../ThirdPartyLibs/imgui/imgui.h"

#include "Assets/Scripts/Prefabs/PrefabUilts.h"
#include "Assets/Scripts/Prefabs/Prefab.h"
#include "Assets/Scripts/Camera/CameraCtrl.h"
#include "Assets/Scripts/GameMgr.h"
#include "Assets/Scripts/Utils/DmPool.h"
#include "Assets/Scripts/Utils/SimpleMaterials.h"
#include "Assets/Scripts/Control/ThirdCamera.h"
#include "Assets/Scripts/Control/PlayerControl.h"
#include "Assets/Scripts/StateMachine/StateMachine.h"
#include "Assets/Scripts/Player/BombCtrl.h"
#include "Assets/Scripts/Player/PlayerHealth.h"
#include "Assets/Scripts/Enemy/EnemyHealth.h"
#include "Assets/Scripts/Enemy/EnemyAttack.h"
#include "Assets/Scripts/Player/PlayerAttack.h"
#include "../Mx/Engine/MxPlatform.h"

std::string TestDemo::getAppName() const { return std::string("TestDemo"); }

Version TestDemo::getAppVersion() const { return Version(1, 0, 0); }

void TestDemo::onMainSceneCreated() {
    // utils
    SimpleMaterials::Init();
    Platform::SetRelativeMouseMode(true);
    Platform::HideCursor();

    // prefabs
    auto ballPrefab = std::make_shared<Prefab2>("TestDemo/Assets/Models/ball/ball_0.3_smooth.gltf", TexturePaths{});
    auto bigballPrefab = std::make_shared<Prefab2>("TestDemo/Assets/Models/bigball/BigBall.gltf", TexturePaths{});
    auto butterflyPrefab = std::make_shared<Prefab2>("TestDemo/Assets/Models/butterfly/butterfly_fixed.gltf", TexturePaths{});

    // GameMgr
    auto gameMgr = GameObject::Instantiate("GameMgr");

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
        reimu->transform().rotate({ 0, 1, 0 }, Math::Constants::Pi);
        reimu->setParent(player);
    }

    StateMachine::player = player;

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
        yuyuko->transform().rotate({ 0, 1, 0 }, Math::Constants::Pi);
        yuyuko->setParent(enemy);
    }
    enemy->transform().setPosition({ 0, 0, 25 });
    enemy->transform().rotate({ 0, 1, 0 }, -Math::Constants::Pi);

    StateMachine::enemy = enemy;

    // camera
    auto camera = SceneManager::Get()->getActiveScene()->getMainCamera()->getGameObject();
    camera->transform().setPosition({ 0, 0, -20 });

    // addComponents
    // 642 -> 5k
    auto ballPool = gameMgr->addComponent<DmPool>(ballPrefab, "", "ball", 1000);
    auto bigballPool = gameMgr->addComponent<DmPool>(bigballPrefab, "", "bigball", 1000);
    auto playerBigballPool = gameMgr->addComponent<DmPool>(bigballPrefab, "", "player_bigball", 8);
    // 162 -> 2.5k+
    auto butterflyPool = gameMgr->addComponent<DmPool>(butterflyPrefab, "", "butterfly", 2500);
    StateMachine::gameMgr = gameMgr->addComponent<GameMgr>(player,
                                                           enemy,
                                                           ballPool,
                                                           bigballPool,
                                                           butterflyPool);

    //camera->addComponent<CameraCtrl>(player);
    camera->addComponent<ThirdCamera>(player);
    camera->addComponent<AudioListener>();

    // todo
    StateMachine::playerBombCtrl = player->addComponent<BombCtrl>(playerBigballPool);
    StateMachine::playerHealth = player->addComponent<PlayerHealth>(5);
    player->addComponent<PlayerAttack>();
    // ...
    player->addComponent<PlayerAdapter>();
    player->addComponent<PlayerControl>(camera->getComponent<Camera>());

    StateMachine::enemyHealth = enemy->addComponent<EnemyHealth>();
    //enemy->addComponent<EnemyAttack>();
}

void TestDemo::onGUI() {
    ImGui::ShowDemoWindow();
}
