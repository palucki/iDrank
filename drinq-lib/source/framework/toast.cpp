#include "toast.h"


Toast::Toast(const QString &text, const QVariant id, QObject* parent)
    : QObject(parent),
      m_text(text),
      m_id(id)
{
}

//Toast::~Toast()
//{

//}
