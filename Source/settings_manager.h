#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

class SettingsManager
{
public:
    bool CollectStatistics;
    bool UseNovaInvolution;
    bool ConstructBasis;
    bool PrintAnswer;

public:
    ~SettingsManager();

private:
    SettingsManager();

friend SettingsManager& GetSettingsManager();
};

SettingsManager& GetSettingsManager();

#endif // SETTINGS_MANAGER_H
