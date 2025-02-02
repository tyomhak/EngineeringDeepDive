#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>

// #include "Renderer.h"
// #include "ConvexHull.h"
#include "GrahamScan.h"
 
int main(int argc, char ** argv)
{
    std::unique_ptr<renderer::RenderEngine> engine(new renderer::GrahamScan());
    engine->run();
    return 0;
}