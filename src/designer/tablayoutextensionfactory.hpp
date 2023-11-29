#pragma once

#include <QtDesigner/QExtensionFactory>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE

class QMWTabLayoutExtensionFactory : public QExtensionFactory
{
    Q_OBJECT

public:
    explicit QMWTabLayoutExtensionFactory(QExtensionManager* parent = nullptr);

protected:
    QObject* createExtension(QObject* object, const QString& iid, QObject* parent) const override;
};
