#include "TestScript.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"

MX_IMPLEMENT_RTTI(TestScript, Script)

void TestScript::start() {
    Coroutine::startCoroutine([] (MX_YIELD_HANDLE) {
        while(1) {
            printf("Hz NB\n");
            yield_return(new Coroutine::WaitForSeconds(1));
        }
    });
}

void TestScript::update() {

}
