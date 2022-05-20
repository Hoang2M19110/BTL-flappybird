
#pragma once

#include "lib.h"
//#include <vector>

using namespace std;

class land : LTexture
{
public:
    void init();

    void Free();

    void render();

    void update();

private:
    position landPosition;
};
