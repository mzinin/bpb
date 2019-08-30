#include "settings_manager.h"


void SettingsManager::setCollectStatisticsEnabled()
{
    collectStatistics_ = true;
}

void SettingsManager::setCollectStatisticsDisabled()
{
    collectStatistics_ = false;
}

void SettingsManager::setUseNovaInvolutionEnabled()
{
    useNovaInvolution_ = true;
}

void SettingsManager::setUseNovaInvolutionDisabled()
{
    useNovaInvolution_ = false;
}

void SettingsManager::setPrintAnswerEnabled()
{
    printAnswer_ = true;
}

void SettingsManager::setPrintAnswerDisabled()
{
    printAnswer_ = false;
}

void SettingsManager::setPrintVersionEnabled()
{
    printVersion_ = true;
}

void SettingsManager::setPrintVersionDisabled()
{
    printVersion_ = false;
}

void SettingsManager::setPrintHelpEnabled()
{
    printHelp_ = true;
}

void SettingsManager::setPrintHelpDisabled()
{
    printHelp_ = false;
}

void SettingsManager::setMonomialOrderLex()
{
    monomialOrder_ = Monom::Lex;
}

void SettingsManager::setMonomialOrderDegLex()
{
    monomialOrder_ = Monom::DegLex;
}

void SettingsManager::setMonomialOrderDegRevLex()
{
    monomialOrder_ = Monom::DegRevLex;
}

SettingsManager& settingsManager()
{
    static SettingsManager manager;
    return manager;
}
