#include <iostream>
#include "launcher.h"

int main(int argc, char *argv[])
{
    Launcher launcher;

    if (!launcher.Init(argc, argv))
    {
        return EXIT_FAILURE;
    }

    if (!launcher.Run())
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
