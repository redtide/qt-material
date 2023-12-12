#ifndef MATERIAL_AVATAR_H
#define MATERIAL_AVATAR_H

#include "dlimpexp.hpp"

#include <QIcon>
#include <QtWidgets/QWidget>

class MaterialAvatarPrivate;

class QT_MATERIAL_EXPORT MaterialAvatar : public QWidget
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialAvatar)
    Q_DECLARE_PRIVATE(MaterialAvatar)

    Q_PROPERTY(QIcon   icon    READ icon   WRITE setIcon)
    Q_PROPERTY(QChar   letter  READ letter WRITE setLetter)
    Q_PROPERTY(QPixmap pixmap  READ pixmap WRITE setPixmap)
    Q_PROPERTY(int     size    READ size   WRITE setSize)

public:
    explicit MaterialAvatar(QWidget* parent = nullptr);
    explicit MaterialAvatar(const QIcon&   icon,   QWidget* parent = nullptr);
    explicit MaterialAvatar(const QPixmap& pixmap, QWidget* parent = nullptr);
    explicit MaterialAvatar(const QChar&   letter, QWidget* parent = nullptr);
    ~MaterialAvatar();

    enum AvatarType {
        AvatarIcon,
        AvatarLetter,
        AvatarPixmap
    };
    Q_ENUM(AvatarType)

    QSize sizeHint() const override;

    void setSize(int size);
    int size() const;

    void setLetter(const QChar& letter);
    QChar letter() const;

    void setPixmap(const QPixmap& pixmap);
    QPixmap pixmap() const;

    void setIcon(const QIcon& icon);
    QIcon icon() const;

    AvatarType type() const;

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    const QScopedPointer<MaterialAvatarPrivate> d_ptr;
};

#endif // MATERIAL_AVATAR_H
