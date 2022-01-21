#pragma once

#include <QObject>
#include <QString>
#include <drinq-lib_global.h>

class DRINQLIB_EXPORT Toast : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_text MEMBER m_text CONSTANT)

public:

    Toast(const QString& text = "", QObject* parent = nullptr);
    virtual ~Toast() override {};
public:
    QString m_text;
};


