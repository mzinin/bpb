#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include "monom.h"

class Launcher;

class SettingsManager
{
private:
    bool CollectStatistics;
    bool UseNovaInvolution;
    bool PrintAnswer;
    bool PrintVersion;
    bool PrintHelp;
    Monom::Order MonomialOrder;

public:
    ~SettingsManager();

    bool GetCollectStatistics() const;
    bool GetUseNovaInvolution() const;
    bool GetPrintAnswer() const;
    bool GetPrintVersion() const;
    bool GetPrintHelp() const;
    Monom::Order GetMonomialOrder() const;

private:
    SettingsManager();

    void SetCollectStatisticsEnabled();
    void SetCollectStatisticsDisabled();

    void SetUseNovaInvolutionEnabled();
    void SetUseNovaInvolutionDisabled();

    void SetPrintAnswerEnabled();
    void SetPrintAnswerDisabled();

    void SetPrintVersionEnabled();
    void SetPrintVersionDisabled();

    void SetPrintHelpEnabled();
    void SetPrintHelpDisabled();

    void SetMonomialOrderLex();
    void SetMonomialOrderDegLex();
    void SetMonomialOrderDegRevLex();
    void SetMonomialOrderOldDRL();

    friend SettingsManager& GetSettingsManager();
    friend class Launcher;
};

SettingsManager& GetSettingsManager();


inline bool SettingsManager::GetCollectStatistics() const
{
    return CollectStatistics;
}

inline bool SettingsManager::GetUseNovaInvolution() const
{
    return UseNovaInvolution;
}

inline bool SettingsManager::GetPrintAnswer() const
{
    return PrintAnswer;
}

inline bool SettingsManager::GetPrintVersion() const
{
    return PrintVersion;
}

inline bool SettingsManager::GetPrintHelp() const
{
    return PrintHelp;
}

inline Monom::Order SettingsManager::GetMonomialOrder() const
{
    return MonomialOrder;
}

#endif // SETTINGS_MANAGER_H
