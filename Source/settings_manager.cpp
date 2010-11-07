#include "settings_manager.h"

SettingsManager::SettingsManager()
    : CollectStatistics(false)
    , UseNovaInvolution(false)
    , PrintAnswer(false)
    , PrintVersion(false)
    , PrintHelp(false)
{
}

SettingsManager::~SettingsManager()
{
}

SettingsManager& GetSettingsManager()
{
    static SettingsManager manager = SettingsManager();
    return manager;
}
