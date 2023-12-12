#ifndef MATERIAL_PROGRESS_INTERNAL_H
#define MATERIAL_PROGRESS_INTERNAL_H

#include <QtMaterialWidgets/progress.hpp>

class MaterialProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    MaterialProgressDelegate(MaterialProgress *parent);
    ~MaterialProgressDelegate();

    inline void setOffset(qreal offset);
    inline qreal offset() const;

private:
    Q_DISABLE_COPY(MaterialProgressDelegate)

    MaterialProgress *const progress_;
    qreal                     offset_;
};

inline void MaterialProgressDelegate::setOffset(qreal offset)
{
    offset_ = offset;
    progress_->update();
}

inline qreal MaterialProgressDelegate::offset() const
{
    return offset_;
}

#endif // MATERIAL_PROGRESS_INTERNAL_H
