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

    MaterialCircularProgress *const progress_;
    qreal                             dashOffset_;
    qreal                             dashLength_;
    int                               angle_;
};

inline void MaterialCircularProgressDelegate::setDashOffset(qreal offset)
{
    dashOffset_ = offset;
    progress_->update();
}

inline qreal MaterialCircularProgressDelegate::dashOffset() const
{
    return dashOffset_;
}

inline void MaterialCircularProgressDelegate::setDashLength(qreal length)
{
    dashLength_ = length;
    progress_->update();
}

inline qreal MaterialCircularProgressDelegate::dashLength() const
{
    return dashLength_;
}

inline void MaterialCircularProgressDelegate::setAngle(int angle)
{
    angle_ = angle;
    progress_->update();
}

inline int MaterialCircularProgressDelegate::angle() const
{
    return angle_;
}

#endif // MATERIAL_CIRCULARPROGRESS_INTERNAL_H
