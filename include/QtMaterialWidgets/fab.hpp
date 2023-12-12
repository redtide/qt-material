#ifndef MATERIAL_FAB_H
#define MATERIAL_FAB_H

#include "raisedbutton.hpp"
#include "dlimpexp.hpp"

class MaterialFloatingActionButtonPrivate;

class QT_MATERIAL_EXPORT MaterialFloatingActionButton : public MaterialRaisedButton
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialFloatingActionButton)
    Q_DECLARE_PRIVATE(MaterialFloatingActionButton)

    Q_PROPERTY(bool       isMini  READ isMini  WRITE setMini)
    Q_PROPERTY(Qt::Corner corner  READ corner  WRITE setCorner)
    Q_PROPERTY(int        xOffset READ xOffset WRITE setXOffset)
    Q_PROPERTY(int        yOffset READ yOffset WRITE setYOffset)

public:
    explicit MaterialFloatingActionButton(QWidget* parent = nullptr);
    explicit MaterialFloatingActionButton(const QIcon& icon, QWidget* parent = nullptr);
    ~MaterialFloatingActionButton();

    void setMini(bool state);
    bool isMini() const;

    void setCorner(Qt::Corner corner);
    Qt::Corner corner() const;

    void setOffset(int x, int y);
    QSize offset() const;

    void setXOffset(int x);
    int xOffset() const;

    void setYOffset(int y);
    int yOffset() const;

    QSize sizeHint() const override;

protected:
    bool event(QEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    void updateClipPath() override;
};

#endif // MATERIAL_FAB_H
