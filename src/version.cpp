#include "current_version.h"
#include "version.h"


namespace
{
    const VersionInfo version(MAJOR_VESION, MINOR_VERSION, REVISION);
}

VersionInfo::VersionInfo(unsigned major, unsigned minor, unsigned revision)
    : major_(major)
    , minor_(minor)
    , revision_(revision)
{
}

unsigned VersionInfo::major() const
{
  return major_;
}

unsigned VersionInfo::minor() const
{
  return minor_;
}

unsigned VersionInfo::revision() const
{
  return revision_;
}

const VersionInfo& currentVersion()
{
  return version;
}
