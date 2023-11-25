#pragma once

#include <QtCore/qglobal.h>

#if defined(QT_MATERIAL_LIBRARY)
#  define QT_MATERIAL_EXPORT Q_DECL_EXPORT
#else
#  define QT_MATERIAL_EXPORT Q_DECL_IMPORT
#endif
