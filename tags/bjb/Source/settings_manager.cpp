#include "settings_manager.h"

SettingsManager::SettingsManager()
    : CollectStatistics(false)
    , PrintAnswer(false)
    , PrintVersion(false)
    , PrintHelp(false)
{
}

SettingsManager::~SettingsManager()
{
}

void SettingsManager::SetCollectStatisticsEnabled()
{
    CollectStatistics = true;
}

void SettingsManager::SetCollectStatisticsDisabled()
{
    CollectStatistics = false;
}

void SettingsManager::SetPrintAnswerEnabled()
{
    PrintAnswer = true;
}

void SettingsManager::SetPrintAnswerDisabled()
{
    PrintAnswer = false;
}

void SettingsManager::SetPrintVersionEnabled()
{
    PrintVersion = true;
}

void SettingsManager::SetPrintVersionDisabled()
{
    PrintVersion = false;
}

void SettingsManager::SetPrintHelpEnabled()
{
    PrintHelp = true;
}

void SettingsManager::SetPrintHelpDisabled()
{
    PrintHelp = false;
}

SettingsManager& GetSettingsManager()
{
    static SettingsManager manager = SettingsManager();
    return manager;
}