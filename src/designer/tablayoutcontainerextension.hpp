#pragma once

#include <QtDesigner/QDesignerContainerExtension>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE

class MaterialTabLayout;

class QMWTabLayoutContainerExtension: public QObject, public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    explicit QMWTabLayoutContainerExtension(MaterialTabLayout* widget, QObject* parent);

    int      count()                                  const override;
    QWidget* widget(int index)                        const override;

    int      currentIndex()                           const override;
    void     setCurrentIndex(int index)               override;
#if QT_VERSION >= 0x060000
    bool     canAddWidget()                           const override;
    bool     canRemove(int index)                     const override;
#endif
    void     addWidget(QWidget* widget)               override;
    void     insertWidget(int index, QWidget* widget) override;
    void     remove(int index)                        override;

private:
    MaterialTabLayout* tablayout_;
};
