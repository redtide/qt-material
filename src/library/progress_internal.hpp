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

    MaterialProgress *const m_progress;
    qreal                     m_offset;
};

inline void MaterialProgressDelegate::setOffset(qreal offset)
{
    m_offset = offset;
    m_progress->update();
}

inline qreal MaterialProgressDelegate::offset() const
{
    return m_offset;
}

#endif // MATERIAL_PROGRESS_INTERNAL_H
