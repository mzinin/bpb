#include "version.h"

static VersionInfo Version(MAJOR_VESION, MINOR_VERSION, REVISION);

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
