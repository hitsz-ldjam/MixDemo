#include "SimpleMaterials.h"
#include "../../../../Mx/Graphics/Texture/MxTexture.h"
#include "../../../../Mx/Graphics/MxGraphics.h"

std::shared_ptr<Material> SimpleMaterials::whiteMat,
                          SimpleMaterials::redMat,
                          SimpleMaterials::yellowMat,
                          SimpleMaterials::cyanMat,
                          SimpleMaterials::blueMat,
                          SimpleMaterials::purpleMat;

void SimpleMaterials::Init() {
    whiteMat = MatOfColor(Color::White);
    redMat = MatOfColor(Color::Red);
    yellowMat = MatOfColor(Color::Yellow);
    cyanMat = MatOfColor(Color::Cyan);
    blueMat = MatOfColor(Color::Blue);
    purpleMat = MatOfColor(Color(1, 0, 1, 1));
}

std::shared_ptr<Material> SimpleMaterials::MatOfColor(const Color& _color) {
    auto mat = std::make_shared<Material>(Graphics::Get()->findShader("Standard"));
    auto tex = std::make_shared<Texture2D>(2, 2, TextureFormat::R8G8B8A8_Unorm);
    Color32 color[] = {_color, _color, _color, _color};
    tex->setPixels(color, sizeof(color));
    tex->apply();
    mat->setTexture("diffuseTex", tex);
    return mat;
}
