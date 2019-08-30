#pragma once

#include "monom.h"


class Launcher;

class SettingsManager
{
public:
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    bool collectStatistics() const;
    bool useNovaInvolution() const;
    bool printAnswer() const;
    bool printVersion() const;
    bool printHelp() const;
    Monom::Order monomialOrder() const;

private:
    SettingsManager() = default;

    void setCollectStatisticsEnabled();
    void setCollectStatisticsDisabled();

    void setUseNovaInvolutionEnabled();
    void setUseNovaInvolutionDisabled();

    void setPrintAnswerEnabled();
    void setPrintAnswerDisabled();

    void setPrintVersionEnabled();
    void setPrintVersionDisabled();

    void setPrintHelpEnabled();
    void setPrintHelpDisabled();

    void setMonomialOrderLex();
    void setMonomialOrderDegLex();
    void setMonomialOrderDegRevLex();

    friend SettingsManager& settingsManager();
    friend class Launcher;

private:
    bool collectStatistics_ = false;
    bool useNovaInvolution_ = false;
    bool printAnswer_ = false;
    bool printVersion_ = false;
    bool printHelp_ = false;
    Monom::Order monomialOrder_ = Monom::DegRevLex;
};


SettingsManager& settingsManager();


inline bool SettingsManager::collectStatistics() const
{
    return collectStatistics_;
}

inline bool SettingsManager::useNovaInvolution() const
{
    return useNovaInvolution_;
}

inline bool SettingsManager::printAnswer() const
{
    return printAnswer_;
}

inline bool SettingsManager::printVersion() const
{
    return printVersion_;
}

inline bool SettingsManager::printHelp() const
{
    return printHelp_;
}

inline Monom::Order SettingsManager::monomialOrder() const
{
    return monomialOrder_;
}
