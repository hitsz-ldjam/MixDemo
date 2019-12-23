#pragma once
#include "../../../../Mx/Graphics/MxMaterial.h"
#include "../../../../Mx/Math/MxColor.h"
#include <memory>

using namespace Mix;

class SimpleMaterials final {
public:
    // call after Graphic is loaded
    static void Init();

    // call after Graphic is loaded
    static std::shared_ptr<Material> MatOfColor(const Color& _color);

    static auto White() noexcept { return whiteMat; }
    static auto Red() noexcept { return redMat; }
    static auto Yellow() noexcept { return yellowMat; }
    static auto Cyan() noexcept { return cyanMat; }
    static auto Blue() noexcept { return blueMat; }
    static auto Purple() noexcept { return purpleMat; }

private:
    static std::shared_ptr<Material> whiteMat,
                                     redMat,
                                     yellowMat,
                                     cyanMat,
                                     blueMat,
                                     purpleMat;
};
