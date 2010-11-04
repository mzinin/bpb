#include "settings_manager.h"

SettingsManager::SettingsManager()
    : CollectStatistics(false)
    , UseNovaInvolution(false)
    , ConstructBasis(true)
{
}

SettingsManager& GetSettingsManager()
{
    static SettingsManager manager = SettingsManager();
    return manager;
}
