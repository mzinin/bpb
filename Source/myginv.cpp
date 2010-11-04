#include <iostream>

#include "launcher.h"
#include "settings_manager.h"

int main(int argc, char *argv[])
{
    Launcher launcher;

    if (!launcher.Init(argc, argv))
    {
        return EXIT_FAILURE;
    }

    if (GetSettingsManager().ConstructBasis)
    {
        if (!launcher.Run())
        {
            return EXIT_FAILURE;
        }
        launcher.PrintResult();
    }

    return EXIT_SUCCESS;
}
