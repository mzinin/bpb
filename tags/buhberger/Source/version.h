#ifndef VERSION_H
#define VERSION_H

#define MAJOR_VESION 0
#define MINOR_VERSION 2
#define REVISION 3

class VersionInfo
{
private:
    unsigned major;
    unsigned minor;
    unsigned revision;

public:
    VersionInfo(unsigned initialMajor, unsigned initialMinor, unsigned initialRevision);
    unsigned GetMajor() const;
    unsigned GetMinor() const;
    unsigned GetRevision() const;
};

const VersionInfo& GetVersion();
#endif
