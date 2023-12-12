#ifndef MATERIAL_SLIDER_INTERNAL_H
#define MATERIAL_SLIDER_INTERNAL_H

#include <QtMaterialWidgets/overlaywidget.hpp>

#include <QStateMachine>

class MaterialSlider;
class MaterialSliderThumb;
class MaterialSliderTrack;

class MaterialSliderStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    MaterialSliderStateMachine(MaterialSlider *slider,
                                 MaterialSliderThumb *thumb,
                                 MaterialSliderTrack *track);
    ~MaterialSliderStateMachine();

    void setupProperties();

private:
    Q_DISABLE_COPY(MaterialSliderStateMachine)

    MaterialSlider      *const slider_;
    MaterialSliderThumb *const thumb_;
    MaterialSliderTrack *const track_;
    QState              *const topState_;
    QState              *const fstState_;
    QState              *const sndState_;
    QState              *const inactiveState_;
    QState              *const focusState_;
    QState              *const slidingState_;
    QState              *const pulseOutState_;
    QState              *const pulseInState_;
    QState              *const minState_;
    QState              *const normalState_;
};

class MaterialSliderThumb : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal diameter WRITE setDiameter READ diameter)
    Q_PROPERTY(qreal borderWidth WRITE setBorderWidth READ borderWidth)
    Q_PROPERTY(QColor borderColor WRITE setBorderColor READ borderColor)
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(QColor haloColor WRITE setHaloColor READ haloColor)

public:
    explicit MaterialSliderThumb(MaterialSlider *slider);
    ~MaterialSliderThumb();

    inline void setDiameter(qreal diameter);
    inline qreal diameter() const;

    inline void setBorderWidth(qreal width);
    inline qreal borderWidth() const;

    inline void setBorderColor(const QColor &color);
    inline QColor borderColor() const;

    inline void setFillColor(const QColor &color);
    inline QColor fillColor() const;

    inline void setHaloSize(qreal size);
    inline qreal haloSize() const;

    inline void setHaloColor(const QColor &color);
    inline QColor haloColor() const;

    inline void setOffset(int offset);
    inline int offset() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Q_DISABLE_COPY(MaterialSliderThumb)

    const MaterialSlider *const slider_;
    QColor               borderColor_;
    QColor               fillColor_;
    QColor               haloColor_;
    qreal                borderWidth_;
    qreal                diameter_;
    qreal                haloSize_;
    int                  offset_;
};

inline void MaterialSliderThumb::setDiameter(qreal diameter)
{
    diameter_ = diameter;
    update();
}

inline qreal MaterialSliderThumb::diameter() const
{
    return diameter_;
}

inline void MaterialSliderThumb::setBorderWidth(qreal width)
{
    borderWidth_ = width;
    update();
}

inline qreal MaterialSliderThumb::borderWidth() const
{
    return borderWidth_;
}

inline void MaterialSliderThumb::setBorderColor(const QColor &color)
{
    borderColor_ = color;
    update();
}

inline QColor MaterialSliderThumb::borderColor() const
{
    return borderColor_;
}

inline void MaterialSliderThumb::setFillColor(const QColor &color)
{
    fillColor_ = color;
    update();
}

inline QColor MaterialSliderThumb::fillColor() const
{
    return fillColor_;
}

inline void MaterialSliderThumb::setHaloSize(qreal size)
{
    haloSize_ = size;
    update();
}

inline qreal MaterialSliderThumb::haloSize() const
{
    return haloSize_;
}

inline void MaterialSliderThumb::setHaloColor(const QColor &color)
{
    haloColor_ = color;
    update();
}

inline QColor MaterialSliderThumb::haloColor() const
{
    return haloColor_;
}

inline void MaterialSliderThumb::setOffset(int offset)
{
    offset_ = offset;
    update();
}

inline int MaterialSliderThumb::offset() const
{
    return offset_;
}

class MaterialSliderTrack : public MaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)

public:
    explicit MaterialSliderTrack(MaterialSliderThumb *thumb, MaterialSlider *slider);
    ~MaterialSliderTrack();

    inline void setFillColor(const QColor &color);
    inline QColor fillColor() const;

    inline void setTrackWidth(int width);
    inline int trackWidth() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialSliderTrack)

    const MaterialSlider *const slider_;
    MaterialSliderThumb  *const thumb_;
    QColor                        fillColor_;
    int                           m_trackWidth;
};

inline void MaterialSliderTrack::setFillColor(const QColor &color)
{
    fillColor_ = color;
    update();
}

inline QColor MaterialSliderTrack::fillColor() const
{
    return fillColor_;
}

void MaterialSliderTrack::setTrackWidth(int width)
{
    m_trackWidth = width;
    update();
}

int MaterialSliderTrack::trackWidth() const
{
    return m_trackWidth;
}

static constexpr int SliderMargin { 10 };

#endif // MATERIAL_SLIDER_INTERNAL_H
