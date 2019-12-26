#include "DmPool.h"
#include "../../../../Mx/GameObject/MxGameObject.h"

MX_IMPLEMENT_RTTI(DmPool, Script)

DmPool::DmPool(std::shared_ptr<Prefab2> _danmaku,
               std::string _name,
               Tag _tag,
               size_t _initCap) : iterCache(0),
                                  dmPrefab(std::move(_danmaku)),
                                  name(std::move(_name)),
                                  tag(std::move(_tag)) {
    available.reserve(_initCap);
    while(--_initCap) {
        auto dm = dmPrefab->instantiate(name, tag);
        dm->setActive(false);
        available.emplace_back(std::move(dm));
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
        auto& dm = available[iterCache];
        if(!dm->activeSelf()) {
            dm->setActive(true);

            ++iterCache;
            if(iterCache == available.size())
                iterCache = 0;
            return dm;
        }

        ++iterCache;
        if(iterCache == available.size())
            iterCache = 0;
    }
    while(iterCache != lastPos);

    available.emplace_back(dmPrefab->instantiate(name, tag));
    iterCache = 0;
    return available.back();
}

void DmPool::destoryDm(const HGameObject& _dm) {
    // todo: check validity
    toDestory.push_back(_dm);
}

void DmPool::lateUpdate() {
    for(const auto& dm : toDestory) {
        dm->setActive(false);
        auto scrps = dm->getComponents<Script>();
        for(auto& scrp : scrps)
            dm->removeComponent(static_scene_object_cast<Component>(scrp));
    }

    //decltype(toDestory) empty(std::move(toDestory));
    toDestory.clear();
}
