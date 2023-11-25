#include "qtmaterialprogress_internal.hpp"

/*!
 *  \class QtMaterialProgressDelegate
 *  \internal
 */

QtMaterialProgressDelegate::QtMaterialProgressDelegate(QtMaterialProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_offset(0)
{
    Q_ASSERT(parent);
}

QtMaterialProgressDelegate::~QtMaterialProgressDelegate()
{
}
