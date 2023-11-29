#ifndef MATERIAL_CIRCULARPROGRESS_INTERNAL_H
#define MATERIAL_CIRCULARPROGRESS_INTERNAL_H

#include <QtMaterialWidgets/circularprogress.hpp>

class MaterialCircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
    Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
    MaterialCircularProgressDelegate(MaterialCircularProgress *parent);
    ~MaterialCircularProgressDelegate();

    inline void setDashOffset(qreal offset);
    inline qreal dashOffset() const;

    inline void setDashLength(qreal length);
    inline qreal dashLength() const;

    inline void setAngle(int angle);
    inline int angle() const;

private:
    Q_DISABLE_COPY(MaterialCircularProgressDelegate)

    MaterialCircularProgress *const m_progress;
    qreal                             m_dashOffset;
    qreal                             m_dashLength;
    int                               m_angle;
};

inline void MaterialCircularProgressDelegate::setDashOffset(qreal offset)
{
    m_dashOffset = offset;
    m_progress->update();
}

inline qreal MaterialCircularProgressDelegate::dashOffset() const
{
    return m_dashOffset;
}

inline void MaterialCircularProgressDelegate::setDashLength(qreal length)
{
    m_dashLength = length;
    m_progress->update();
}

inline qreal MaterialCircularProgressDelegate::dashLength() const
{
    return m_dashLength;
}

inline void MaterialCircularProgressDelegate::setAngle(int angle)
{
    m_angle = angle;
    m_progress->update();
}

inline int MaterialCircularProgressDelegate::angle() const
{
    return m_angle;
}

#endif // MATERIAL_CIRCULARPROGRESS_INTERNAL_H
