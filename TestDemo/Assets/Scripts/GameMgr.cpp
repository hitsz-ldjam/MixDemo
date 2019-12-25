#include "GameMgr.h"
#include "Prefabs/Prefab.h"
#include "Utils/SimpleMaterials.h"
#include "Enemy/Spell06/Spell06MasterCtrl.h"
#include "Enemy/Spell03/Spell03BlueSphere.h"
#include "Enemy/Spell03/Spell03SwTail.h"

MX_IMPLEMENT_RTTI(GameMgr, Script)

GameMgr::GameMgr(HGameObject _player,
                 HGameObject _enemy,
                 HDmPool _ballPool,
                 HDmPool _bigballPool)
    : player(std::move(_player)),
      enemy(std::move(_enemy)),
      ballPool(std::move(_ballPool)),
      bigballPool(std::move(_bigballPool)) {}

void GameMgr::start() {
    // todo: state machine
    //enemy->addComponent<Spell06MasterCtrl>(bigballPool);
    enemy->addComponent<Spell03BlueSphere>(player, bigballPool);
    enemy->addComponent<Spell03SwTail>(player, ballPool);
}

void GameMgr::update() { }
