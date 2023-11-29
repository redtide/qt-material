#include "progress_internal.hpp"

/*!
 *  \class MaterialProgressDelegate
 *  \internal
 */

MaterialProgressDelegate::MaterialProgressDelegate(MaterialProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_offset(0)
{
    Q_ASSERT(parent);
}

MaterialProgressDelegate::~MaterialProgressDelegate()
{
}
