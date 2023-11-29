#ifndef MATERIAL_AVATAR_H
#define MATERIAL_AVATAR_H

#include "defs.hpp"
#include "dlimpexp.hpp"

#include <QIcon>
#include <QtWidgets/QWidget>

class MaterialAvatarPrivate;

class QT_MATERIAL_EXPORT MaterialAvatar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor textColor       WRITE setTextColor       READ textColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(int    size            WRITE setSize            READ size)
    Q_PROPERTY(QChar  letter          WRITE setLetter          READ letter)
    Q_PROPERTY(QImage image           WRITE setImage           READ image)
    Q_PROPERTY(QIcon  icon            WRITE setIcon            READ icon)

public:
    explicit MaterialAvatar(QWidget *parent = nullptr);
    explicit MaterialAvatar(const QIcon  &icon,   QWidget* parent = nullptr);
    explicit MaterialAvatar(const QChar  &letter, QWidget* parent = nullptr);
    explicit MaterialAvatar(const QImage &image,  QWidget* parent = nullptr);
    ~MaterialAvatar();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QSize sizeHint() const override;

    void setSize(int size);
    int size() const;

    void setLetter(const QChar& letter);
    QChar letter() const;

    void setImage(const QImage& image);
    QImage image() const;

    void setIcon(const QIcon& icon);
    QIcon icon() const;

    Material::AvatarType type() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MaterialAvatarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MaterialAvatar)
    Q_DECLARE_PRIVATE(MaterialAvatar)
};

#endif // MATERIAL_AVATAR_H
