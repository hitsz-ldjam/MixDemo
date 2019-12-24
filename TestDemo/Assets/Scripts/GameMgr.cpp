#include "GameMgr.h"
#include "Prefabs/Prefab.h"
#include "Utils/SimpleMaterials.h"
#include "Enemy/Spell06/Spell06MasterCtrl.h"
#include "Enemy/Spell03/Spell03BlueSphere.h"

MX_IMPLEMENT_RTTI(GameMgr, Script)

GameMgr::GameMgr(HGameObject _player,
                 HGameObject _enemy,
                 HDmPool _bigballPool)
    : player(std::move(_player)),
      enemy(std::move(_enemy)),
      bigballPool(std::move(_bigballPool)) {}

void GameMgr::start() {
    // todo: state machine
    //enemy->addComponent<Spell06MasterCtrl>(bigballPool);
    enemy->addComponent<Spell03BlueSphere>(player, bigballPool);
}

void GameMgr::update() { }
