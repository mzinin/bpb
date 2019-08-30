#pragma once

#ifdef major
#undef major
#endif

#ifdef minor
#undef minor
#endif


class VersionInfo
{
public:
    VersionInfo(unsigned major, unsigned minor, unsigned revision);

    unsigned major() const;
    unsigned minor() const;
    unsigned revision() const;

private:
    const unsigned major_;
    const unsigned minor_;
    const unsigned revision_;
};

const VersionInfo& currentVersion();
