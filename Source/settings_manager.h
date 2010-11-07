#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

class SettingsManager
{
private:
    bool CollectStatistics;
    bool UseNovaInvolution;
    bool PrintAnswer;
    bool PrintVersion;
    bool PrintHelp;

public:
    ~SettingsManager();

    void SetCollectStatisticsEnabled();
    void SetCollectStatisticsDisabled();
    bool GetCollectStatistics() const;

    void SetUseNovaInvolutionEnabled();
    void SetUseNovaInvolutionDisabled();
    bool GetUseNovaInvolution() const;

    void SetPrintAnswerEnabled();
    void SetPrintAnswerDisabled();
    bool GetPrintAnswer() const;

    void SetPrintVersionEnabled();
    void SetPrintVersionDisabled();
    bool GetPrintVersion() const;

    void SetPrintHelpEnabled();
    void SetPrintHelpDisabled();
    bool GetPrintHelp() const;

private:
    SettingsManager();

friend SettingsManager& GetSettingsManager();
};

SettingsManager& GetSettingsManager();


inline void SettingsManager::SetCollectStatisticsEnabled()
{
    CollectStatistics = true;
}

inline void SettingsManager::SetCollectStatisticsDisabled()
{
    CollectStatistics = false;
}

inline bool SettingsManager::GetCollectStatistics() const
{
    return CollectStatistics;
}

inline void SettingsManager::SetUseNovaInvolutionEnabled()
{
    UseNovaInvolution = true;
}

inline void SettingsManager::SetUseNovaInvolutionDisabled()
{
    UseNovaInvolution = false;
}

inline bool SettingsManager::GetUseNovaInvolution() const
{
    return UseNovaInvolution;
}

inline void SettingsManager::SetPrintAnswerEnabled()
{
    PrintAnswer = true;
}

inline void SettingsManager::SetPrintAnswerDisabled()
{
    PrintAnswer = false;
}

inline bool SettingsManager::GetPrintAnswer() const
{
    return PrintAnswer;
}

inline void SettingsManager::SetPrintVersionEnabled()
{
    PrintVersion = true;
}

inline void SettingsManager::SetPrintVersionDisabled()
{
    PrintVersion = false;
}

inline bool SettingsManager::GetPrintVersion() const
{
    return PrintVersion;
}

inline void SettingsManager::SetPrintHelpEnabled()
{
    PrintHelp = true;
}

inline void SettingsManager::SetPrintHelpDisabled()
{
    PrintHelp = false;
}

inline bool SettingsManager::GetPrintHelp() const
{
    return PrintHelp;
}

#endif // SETTINGS_MANAGER_H
