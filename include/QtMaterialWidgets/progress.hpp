#ifndef MATERIAL_PROGRESS_H
#define MATERIAL_PROGRESS_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QtWidgets/QProgressBar>

class MaterialProgressPrivate;

class QT_MATERIAL_EXPORT MaterialProgress : public QProgressBar
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialProgress)
    Q_DECLARE_PRIVATE(MaterialProgress)

    Q_PROPERTY(Material::ProgressType progressType READ progressType WRITE setProgressType)

public:
    explicit MaterialProgress(QWidget* parent = nullptr);
    ~MaterialProgress();

    void setProgressType(Material::ProgressType type);
    Material::ProgressType progressType() const;

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    const QScopedPointer<MaterialProgressPrivate> d_ptr;
};

#endif // MATERIAL_PROGRESS_H
