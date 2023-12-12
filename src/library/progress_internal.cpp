#include "progress_internal.hpp"

MaterialProgressDelegate::MaterialProgressDelegate(MaterialProgress *parent)
    : QObject(parent)
    , progress_(parent)
    , offset_(0)
{
    Q_ASSERT(parent);
}

MaterialProgressDelegate::~MaterialProgressDelegate()
{
}
