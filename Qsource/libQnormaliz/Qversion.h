#ifndef NMZ_VERSION_H
#define NMZ_VERSION_H

#define NMZ_VERSION_MAJOR  3
#define NMZ_VERSION_MINOR  1
#define NMZ_VERSION_PATCH  4
#define NMZ_VERSION        3.1.4
#define NMZ_RELEASE (NMZ_VERSION_MAJOR * 10000 + NMZ_VERSION_MINOR * 100 + NMZ_VERSION_PATCH)

namespace libQnormaliz {
inline unsigned int getVersion()
{
    return NMZ_RELEASE;
}

} //end namespace libQnormaliz

#endif // NMZ_VERSION_H
