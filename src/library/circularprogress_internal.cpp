#include "circularprogress_internal.hpp"

MaterialCircularProgressDelegate::MaterialCircularProgressDelegate(MaterialCircularProgress *parent)
    : QObject(parent)
    , progress_(parent)
    , dashOffset_(0)
    , dashLength_(89)
    , angle_(0)
{
    Q_ASSERT(parent);
}

MaterialCircularProgressDelegate::~MaterialCircularProgressDelegate()
{
}
