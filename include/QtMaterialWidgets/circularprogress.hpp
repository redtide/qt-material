#ifndef MATERIAL_CIRCULARPROGRESS_H
#define MATERIAL_CIRCULARPROGRESS_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QtWidgets/QProgressBar>

class MaterialCircularProgressPrivate;

class QT_MATERIAL_EXPORT MaterialCircularProgress : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(Material::ProgressType progressType   WRITE setProgressType   READ progressType)
    Q_PROPERTY(bool                   useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(qreal                  lineWidth      WRITE setLineWidth      READ lineWidth)
    Q_PROPERTY(qreal                  size           WRITE setSize           READ size)
    Q_PROPERTY(QColor                 color          WRITE setColor          READ color)

public:
    explicit MaterialCircularProgress(QWidget* parent = nullptr);
    ~MaterialCircularProgress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setLineWidth(qreal width);
    qreal lineWidth() const;

    void setSize(int size);
    int size() const;

    void setColor(const QColor &color);
    QColor color() const;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialCircularProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialCircularProgress)
    Q_DECLARE_PRIVATE(MaterialCircularProgress)
};

#endif // MATERIAL_CIRCULARPROGRESS_H
