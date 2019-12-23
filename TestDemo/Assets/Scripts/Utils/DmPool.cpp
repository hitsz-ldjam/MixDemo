#include "DmPool.h"
#include "../../../../Mx/GameObject/MxGameObject.h"

MX_IMPLEMENT_RTTI(DmPool, Script)

DmPool::DmPool(std::shared_ptr<Prefab2> _danmaku,
               std::string _name,
               Tag _tag,
               size_t _initCap) : dmPrefab(std::move(_danmaku)),
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
    // O(n^2)
    for(const auto& dm : pool) {
        if(!dm->activeSelf()) {
            dm->setActive(true);
            return dm;
        }
    }
    pool.emplace_back(dmPrefab->instantiate(name, tag));
    return pool.back();
}

void DmPool::destoryDm(HGameObject _dm) {
    //std::find
    _dm->setActive(false);
}
