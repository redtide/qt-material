#ifndef MATERIAL_FAB_H
#define MATERIAL_FAB_H

#include "raisedbutton.hpp"
#include "dlimpexp.hpp"

class MaterialFloatingActionButtonPrivate;

class QT_MATERIAL_EXPORT MaterialFloatingActionButton : public MaterialRaisedButton
{
    Q_OBJECT
    Q_PROPERTY(bool       mini    WRITE setMini    READ isMini)
    Q_PROPERTY(Qt::Corner corner  WRITE setCorner  READ corner)
    Q_PROPERTY(int        xOffset WRITE setXOffset READ xOffset)
    Q_PROPERTY(int        yOffset WRITE setYOffset READ yOffset)

public:
    explicit MaterialFloatingActionButton(QWidget* parent = nullptr);
    explicit MaterialFloatingActionButton(const QIcon &icon, QWidget* parent = nullptr);
    ~MaterialFloatingActionButton();

    QSize sizeHint() const override;

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

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void updateClipPath() override;

private:
    Q_DISABLE_COPY(MaterialFloatingActionButton)
    Q_DECLARE_PRIVATE(MaterialFloatingActionButton)
};

#endif // MATERIAL_FAB_H
