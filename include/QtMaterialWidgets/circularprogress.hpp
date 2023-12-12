#ifndef MATERIAL_CIRCULARPROGRESS_H
#define MATERIAL_CIRCULARPROGRESS_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QtWidgets/QProgressBar>

class MaterialCircularProgressPrivate;

class QT_MATERIAL_EXPORT MaterialCircularProgress : public QProgressBar
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialCircularProgress)
    Q_DECLARE_PRIVATE(MaterialCircularProgress)

    Q_PROPERTY(Material::ProgressType progressType READ progressType WRITE setProgressType)
    Q_PROPERTY(qreal                  lineWidth    READ lineWidth    WRITE setLineWidth)
    Q_PROPERTY(qreal                  size         READ size         WRITE setSize)

public:
    explicit MaterialCircularProgress(QWidget* parent = nullptr);
    ~MaterialCircularProgress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setLineWidth(qreal width);
    qreal lineWidth() const;

    void setSize(int size);
    int size() const;

    QSize sizeHint() const override;

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialCircularProgressPrivate> d_ptr;
};

#endif // MATERIAL_CIRCULARPROGRESS_H
