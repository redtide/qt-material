#ifndef MATERIAL_SNACKBAR_P_H
#define MATERIAL_SNACKBAR_P_H

#include <QObject>
#include <QColor>

class MaterialSnackbar;
class MaterialSnackbarStateMachine;

class MaterialSnackbarPrivate
{
    Q_DISABLE_COPY(MaterialSnackbarPrivate)
    Q_DECLARE_PUBLIC(MaterialSnackbar)

public:
    MaterialSnackbarPrivate(MaterialSnackbar *q);
    ~MaterialSnackbarPrivate();

    void init();

    MaterialSnackbar             *const q_ptr;
    MaterialSnackbarStateMachine *stateMachine;
    qreal                        bgOpacity;
    QList<QString>               messages;
    int                          duration;
    int                          boxWidth;
    bool                         clickDismiss;

    bool                         useThemeColors;
    QColor                       backgroundColor;
    QColor                       textColor;
};

#endif // MATERIAL_SNACKBAR_P_H
