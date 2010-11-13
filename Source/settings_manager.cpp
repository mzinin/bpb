#include "settings_manager.h"

SettingsManager::SettingsManager()
    : CollectStatistics(false)
    , UseNovaInvolution(false)
    , PrintAnswer(false)
    , PrintVersion(false)
    , PrintHelp(false)
    , MonomialOrder(Monom::DegRevLex)
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

void SettingsManager::SetUseNovaInvolutionEnabled()
{
    UseNovaInvolution = true;
}

void SettingsManager::SetUseNovaInvolutionDisabled()
{
    UseNovaInvolution = false;
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

void SettingsManager::SetMonomialOrderLex()
{
    MonomialOrder = Monom::Lex;
}

void SettingsManager::SetMonomialOrderDegLex()
{
    MonomialOrder = Monom::DegLex;
}

void SettingsManager::SetMonomialOrderDegRevLex()
{
    MonomialOrder = Monom::DegRevLex;
}

void SettingsManager::SetMonomialOrderOldDRL()
{
    MonomialOrder = Monom::OldDRL;
}


SettingsManager& GetSettingsManager()
{
    static SettingsManager manager = SettingsManager();
    return manager;
}
