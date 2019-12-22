#include "TestDemo.h"
#include "../Mx/GameObject/MxGameObject.h"
#include "Assets/Scripts/TestScript/TestScript.h"

std::string TestDemo::getAppName() const { return std::string("TestDemo"); }

Version TestDemo::getAppVersion() const { return Version(1, 0, 0); }

void TestDemo::onMainSceneCreated() {
    auto obj = GameObject::Instantiate("Hz NB");
    obj->addComponent<TestScript>();
}
