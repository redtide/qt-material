#ifndef MATERIAL_PROGRESS_H
#define MATERIAL_PROGRESS_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QtWidgets/QProgressBar>

class MaterialProgressPrivate;

class QT_MATERIAL_EXPORT MaterialProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
    Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)

public:
    explicit MaterialProgress(QWidget* parent = nullptr);
    ~MaterialProgress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setProgressColor(const QColor &color);
    QColor progressColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialProgress)
    Q_DECLARE_PRIVATE(MaterialProgress)
};

#endif // MATERIAL_PROGRESS_H
