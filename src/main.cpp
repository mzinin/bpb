#include "launcher.h"

#include <cstdlib>


int main(int argc, char* argv[])
{
    Launcher launcher;

    if (!launcher.init(argc, argv))
    {
        return EXIT_FAILURE;
    }

    if (!launcher.run())
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
