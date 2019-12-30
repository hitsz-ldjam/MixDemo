#include "SimpleMaterials.h"
#include "../../../../Mx/Graphics/Texture/MxTexture.h"
#include "../../../../Mx/Graphics/MxGraphics.h"

std::shared_ptr<Material> SimpleMaterials::whiteMat,
SimpleMaterials::redMat,
SimpleMaterials::yellowMat,
SimpleMaterials::greenMat,
SimpleMaterials::cyanMat,
SimpleMaterials::blueMat,
SimpleMaterials::purpleMat,
SimpleMaterials::blueRimMat,
SimpleMaterials::greenRimMat,
SimpleMaterials::redRimMat,
SimpleMaterials::purpleRimMat,

SimpleMaterials::redMatofBf,
SimpleMaterials::blueMatofBf,
SimpleMaterials::purpleMatofBf;

void SimpleMaterials::Init() {
    whiteMat = MatOfColor(Color::White);
    redMat = MatOfColor(Color(231 / 255.f, 34 / 255.f, 34 / 255.f, 1));
    yellowMat = MatOfColor(Color::Yellow);
    greenMat = MatOfColor(Color::Green);
    cyanMat = MatOfColor(Color(47 / 255.f, 1, 241 / 255.f, 1));
    blueMat = MatOfColor(Color(0, 74 / 255.f, 1, 1));
    purpleMat = MatOfColor(Color(240 / 255.f, 61 / 255.f, 243 / 255.f, 1));

    greenRimMat = MatOfColorWithRim(Color::Green);
    redRimMat = MatOfColorWithRim(Color(231 / 255.f, 34 / 255.f, 34 / 255.f, 1));
    blueRimMat = MatOfColorWithRim(Color(0, 0, 178 / 255.f, 1));
    purpleRimMat = MatOfColorWithRim(Color(155 / 255.f, 0, 178 / 255.f, 1));

    blueMatofBf = MatOfColor(Color(0, 74 / 255.f, 1, 1));
    purpleMatofBf = MatOfColor(Color(240 / 255.f, 61 / 255.f, 243 / 255.f, 1));
    redMatofBf = MatOfColor(Color(231 / 255.f, 34 / 255.f, 34 / 255.f, 1));
}

std::shared_ptr<Material> SimpleMaterials::MatOfColor(const Color& _color) {
    auto mat = std::make_shared<Material>(Graphics::Get()->findShader("Standard"));
    auto tex = std::make_shared<Texture2D>(2, 2, TextureFormat::R8G8B8A8_Unorm);
    Color32 color[] = { _color, _color, _color, _color };
    tex->setPixels(color, sizeof(color));
    tex->apply();
    mat->setTexture("diffuseTex", tex);
    mat->setGPUInstancing(true);
    return mat;
}

std::shared_ptr<Material> SimpleMaterials::MatOfColorWithRim(const Color& _color) {
    auto mat = std::make_shared<Material>(Graphics::Get()->findShader("BallShader"));
    mat->setVector("mainColor", Vector4f::One);
    mat->setVector("rimColor", _color.toVector4f());
    mat->setFloat("rimPower", 1.0f);
    mat->setFloat("rimIntensity", 20.0f);
    //mat->setFloat("factorMin", 0);
    //mat->setFloat("factorMax", 0.57f);
    mat->setGPUInstancing(true);
    return mat;
}
