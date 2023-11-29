#ifndef MATERIAL_TOGGLE_INTERNAL_H
#define MATERIAL_TOGGLE_INTERNAL_H

#include <QtMaterialWidgets/rippleoverlay.hpp>

#include <QtWidgets/QWidget>

class MaterialSwitch;
class MaterialSwitchThumb;
class MaterialSwitchTrack;

class MaterialSwitchRippleOverlay : public MaterialRippleOverlay
{
    Q_OBJECT

public:
    MaterialSwitchRippleOverlay(MaterialSwitchThumb *thumb,
                                  MaterialSwitchTrack *track,
                                  MaterialSwitch *parent);
    ~MaterialSwitchRippleOverlay();

protected Q_SLOTS:
    void addToggleRipple();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    QRect overlayGeometry() const override;

private:
    Q_DISABLE_COPY(MaterialSwitchRippleOverlay)

    MaterialSwitch      *const m_toggle;
    MaterialSwitchThumb *const m_thumb;
    MaterialSwitchTrack *const m_track;
};

class MaterialSwitchThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal shift WRITE setShift READ shift)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
    MaterialSwitchThumb(MaterialSwitch *parent);
    ~MaterialSwitchThumb();

    void setShift(qreal shift);
    inline qreal shift() const;

    inline qreal offset() const;

    inline void setThumbColor(const QColor &color);
    inline QColor thumbColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialSwitchThumb)

    void updateOffset();

    MaterialSwitch *const m_toggle;
    QColor         m_thumbColor;
    qreal          m_shift;
    qreal          m_offset;
};

inline qreal MaterialSwitchThumb::shift() const
{
    return m_shift;
}

inline qreal MaterialSwitchThumb::offset() const
{
    return m_offset;
}

inline void MaterialSwitchThumb::setThumbColor(const QColor &color)
{
    m_thumbColor = color;
    update();
}

inline QColor MaterialSwitchThumb::thumbColor() const
{
    return m_thumbColor;
}

class MaterialSwitchTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    MaterialSwitchTrack(MaterialSwitch *parent);
    ~MaterialSwitchTrack();

    void setTrackColor(const QColor &color);
    inline QColor trackColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MaterialSwitchTrack)

    MaterialSwitch *const m_toggle;
    QColor         m_trackColor;
};

inline QColor MaterialSwitchTrack::trackColor() const
{
    return m_trackColor;
}

#endif // MATERIAL_TOGGLE_INTERNAL_H
