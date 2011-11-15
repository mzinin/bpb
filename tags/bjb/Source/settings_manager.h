#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

class Launcher;

class SettingsManager
{
public:
    ~SettingsManager();

    bool GetCollectStatistics() const;
    bool GetUseNovaInvolution() const;
    bool GetPrintAnswer() const;
    bool GetPrintVersion() const;
    bool GetPrintHelp() const;

private:
    SettingsManager();
    SettingsManager(const SettingsManager&);
    SettingsManager& operator=(const SettingsManager&);

    void SetCollectStatisticsEnabled();
    void SetCollectStatisticsDisabled();
    
    void SetPrintAnswerEnabled();
    void SetPrintAnswerDisabled();

    void SetPrintVersionEnabled();
    void SetPrintVersionDisabled();

    void SetPrintHelpEnabled();
    void SetPrintHelpDisabled();

    friend SettingsManager& GetSettingsManager();
    friend class Launcher;
    
private:
    bool CollectStatistics;
    bool PrintAnswer;
    bool PrintVersion;
    bool PrintHelp;
};

SettingsManager& GetSettingsManager();


inline bool SettingsManager::GetCollectStatistics() const
{
    return CollectStatistics;
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

#endif // SETTINGS_MANAGER_H