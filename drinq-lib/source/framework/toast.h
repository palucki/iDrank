#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <drinq-lib_global.h>

class DRINQLIB_EXPORT Toast : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_text MEMBER m_text CONSTANT)
    Q_PROPERTY(QVariant id MEMBER m_id CONSTANT)

public:

    Toast(const QString& text = "", const QVariant id = {}, QObject* parent = nullptr);
    virtual ~Toast() override {};
public:
    QString m_text;
    QVariant m_id;
};


