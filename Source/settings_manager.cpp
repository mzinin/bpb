#include "settings_manager.h"

SettingsManager::SettingsManager()
    : CollectStatistics(false)
    , UseNovaInvolution(false)
    , ConstructBasis(true)
    , PrintAnswer(false)
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
