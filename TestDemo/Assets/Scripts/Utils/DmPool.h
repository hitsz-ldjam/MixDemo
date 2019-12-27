#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../Prefabs/Prefab.h"

using namespace Mix;

/**
 *  @warning use with caution
 *  @todo
 *  @bug This is not a pool actually.
 */
class DmPool final : public Script {
MX_DECLARE_RTTI

public:
    // for simplification. DO NOT use default constructed pool
    DmPool() = default;
    ~DmPool() = default;

    DmPool(std::shared_ptr<Prefab2> _danmaku,
           std::string _name,
           Tag _tag,
           size_t _initCap = 0);

    HGameObject createDm();

    // should only be called in Update()
    void destoryDm(const HGameObject& _dm);
    void destoryAll(); // not impled yet

    auto& getPool() { return pool; }

private:
    void lateUpdate() override;

    std::vector<HGameObject> pool, toDestroy;
    size_t iterCache;

    std::shared_ptr<Prefab2> dmPrefab;
    std::string name;
    Tag tag;
};

using HDmPool = SceneObjectHandle<DmPool>;
