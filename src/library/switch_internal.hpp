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

    MaterialSwitch      *const toggle_;
    MaterialSwitchThumb *const thumb_;
    MaterialSwitchTrack *const track_;
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

    MaterialSwitch *const toggle_;
    QColor         thumbColor_;
    qreal          shift_;
    qreal          offset_;
};

inline qreal MaterialSwitchThumb::shift() const
{
    return shift_;
}

inline qreal MaterialSwitchThumb::offset() const
{
    return offset_;
}

inline void MaterialSwitchThumb::setThumbColor(const QColor &color)
{
    thumbColor_ = color;
    update();
}

inline QColor MaterialSwitchThumb::thumbColor() const
{
    return thumbColor_;
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

    MaterialSwitch *const toggle_;
    QColor         trackColor_;
};

inline QColor MaterialSwitchTrack::trackColor() const
{
    return trackColor_;
}

#endif // MATERIAL_TOGGLE_INTERNAL_H
