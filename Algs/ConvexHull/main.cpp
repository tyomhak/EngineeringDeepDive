#include <memory>

// #include "Renderer.h"
// #include "ConvexHull.h"
#include "GrahamScan.h"
#include "QuickHull.h"
 
int main(int argc, char ** argv)
{
    bool use_graham_scan = false;
    
    std::unique_ptr<renderer::ConvexHull> convex_hull_solver{nullptr};
    if (use_graham_scan)
        convex_hull_solver.reset(new renderer::QuickHull());
    else
        convex_hull_solver.reset(new renderer::GrahamScan());

    convex_hull_solver->run();
    return 0;
}