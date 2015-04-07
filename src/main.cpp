#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif // __EMSCRIPTEN__

int main()
{
#ifdef __EMSCRIPTEN__
    EM_ASM( allReady() );
    std::cout << "HELLO EMSCRIPTEN" << std::endl;
#endif // __EMSCRIPTEN__
    return 0;
}
