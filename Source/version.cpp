#include "version.h"

static VersionInfo Version(0, 5, 3);

VersionInfo::VersionInfo():
    major(0),
    minor(0),
    revision(0)
{
}

VersionInfo::VersionInfo(unsigned initialMajor, unsigned initialMinor, unsigned initialRevision):
    major(initialMajor),
    minor(initialMinor),
    revision(initialRevision)
{
}

unsigned VersionInfo::GetMajor() const
{
  return major;
}

unsigned VersionInfo::GetMinor() const
{
  return minor;
}

unsigned VersionInfo::GetRevision() const
{
  return revision;
}

const VersionInfo& GetVersion()
{
  return Version;
}
