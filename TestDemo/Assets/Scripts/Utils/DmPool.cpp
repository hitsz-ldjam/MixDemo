#include "DmPool.h"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../StateMachine/StateMachine.h"

MX_IMPLEMENT_RTTI(DmPool, Script)

DmPool::DmPool(std::shared_ptr<Prefab2> _danmaku,
               std::string _name,
               Tag _tag,
               size_t _initCap) : iterCache(0),
                                  dmPrefab(std::move(_danmaku)),
                                  name(std::move(_name)),
                                  tag(std::move(_tag)) {
    pool.reserve(_initCap);
    while(--_initCap) {
        auto dm = dmPrefab->instantiate(name, tag);
        dm->setActive(false);
        pool.emplace_back(std::move(dm));
    }
}

HGameObject DmPool::createDm() {
    // O(n)
    //for(const auto& dm : available) {
    //    if(!dm->activeSelf()) {
    //        dm->setActive(true);
    //        return dm;
    //    }
    //}
    //available.emplace_back(dmPrefab->instantiate(name, tag));
    //return available.back();

    auto lastPos = iterCache;
    do {
        auto& dm = pool[iterCache];
        if(!dm->activeSelf()) {
            dm->setActive(true);
            dm->setName(name);

            ++iterCache;
            if(iterCache == pool.size())
                iterCache = 0;
            return dm;
        }

        ++iterCache;
        if(iterCache == pool.size())
            iterCache = 0;
    }
    while(iterCache != lastPos);

    pool.emplace_back(dmPrefab->instantiate(name, tag));
    iterCache = 0;
    return pool.back();
}

// todo: check validity
void DmPool::destoryDm(const HGameObject& _dm) {
    if(_dm->getName() == "_-_")
        return;
    _dm->setName("_-_"); // magic flag
    toDestroy.push_back(_dm);
}

void DmPool::destoryAll() { }

void DmPool::lateUpdate() {
    for(const auto& dm : toDestroy) {
        dm->setActive(false);
        auto scrps = dm->getComponents<Script>();
        for(auto& scrp : scrps)
            dm->removeComponent(static_scene_object_cast<Component>(scrp));
        dm->transform().setPosition(Vector3f::Zero);
        dm->transform().setRotation(Quaternion::Identity);
    }

    //decltype(toDestory) empty(std::move(toDestory));
    toDestroy.clear();

    Vector3f src(0, 5, 15), //StateMachine::player->transform().getPosition(), 
             border(30, 25, 40);
    for(const auto& dm : pool) {
        if(!dm->activeSelf())
            continue;

        auto pos = dm->transform().getPosition();
        if(abs(pos.x - src.x) > border.x ||
           abs(pos.y - src.y) > border.y ||
           abs(pos.z - src.z) > border.z)
            destoryDm(dm);
    }
}
