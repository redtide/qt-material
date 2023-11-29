#include "circularprogress_internal.hpp"

/*!
 *  \class MaterialCircularProgressDelegate
 *  \internal
 */

MaterialCircularProgressDelegate::MaterialCircularProgressDelegate(MaterialCircularProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_dashOffset(0),
      m_dashLength(89),
      m_angle(0)
{
    Q_ASSERT(parent);
}

MaterialCircularProgressDelegate::~MaterialCircularProgressDelegate()
{
}
