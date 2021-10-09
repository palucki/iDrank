#ifndef DRINQLIB_GLOBAL_H
#define DRINQLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DRINQLIB_LIBRARY)
#  define DRINQLIB_EXPORT Q_DECL_EXPORT
#else
#  define DRINQLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // DRINQLIB_GLOBAL_H
