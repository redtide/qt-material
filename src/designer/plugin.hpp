#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

#include <QIcon>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class QMWCustomWidgetInterface : public QDesignerCustomWidgetInterface
{
public:
    QMWCustomWidgetInterface() = default;
    ~QMWCustomWidgetInterface() = default;

    QString name()          const override { return name_; }
    QString group()         const override { return QLatin1String("Material Widgets"); }
    QString includeFile()   const override { return include_; }
    QString toolTip()       const override { return QString(); }
    QString whatsThis()     const override { return QString(); }
    QString domXml()        const override { return xml_; }
    QIcon   icon()          const override { return icon_; }
    bool    isContainer()   const override { return false; }
    bool    isInitialized() const override { return true; }

protected:
    QString name_;
    QString include_;
    QString xml_;
    QIcon   icon_;
};
//======================================================================================================
// AppBar
//======================================================================================================
struct QMWAppBarInterface : public QMWCustomWidgetInterface
{
    explicit QMWAppBarInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// AutoComplete
//======================================================================================================
struct QMWAutoCompleteInterface : public QMWCustomWidgetInterface
{
    explicit QMWAutoCompleteInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// Avatar
//======================================================================================================
struct QMWAvatarInterface : public QMWCustomWidgetInterface
{
    explicit QMWAvatarInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// Badge
//======================================================================================================
struct QMWBadgeInterface : public QMWCustomWidgetInterface
{
    explicit QMWBadgeInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// CheckBox
//======================================================================================================
struct QMWCheckBoxInterface : public QMWCustomWidgetInterface
{
    explicit QMWCheckBoxInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// CircularProgress
//======================================================================================================
struct QMWCircularProgressInterface : public QMWCustomWidgetInterface
{
    explicit QMWCircularProgressInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// Dialog
//======================================================================================================
struct QMWDialogInterface : public QMWCustomWidgetInterface
{
    explicit QMWDialogInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// Drawer
//======================================================================================================
struct QMWDrawerInterface : public QMWCustomWidgetInterface
{
    explicit QMWDrawerInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// FloatingActionButton
//======================================================================================================
struct QMWFabInterface : public QMWCustomWidgetInterface
{
    explicit QMWFabInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// FlatButton
//======================================================================================================
struct QMWFlatButtonInterface : public QMWCustomWidgetInterface
{
    explicit QMWFlatButtonInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// IconButton
//======================================================================================================
struct QMWIconButtonInterface : public QMWCustomWidgetInterface
{
    explicit QMWIconButtonInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// Progress
//======================================================================================================
struct QMWProgressInterface : public QMWCustomWidgetInterface
{
    explicit QMWProgressInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// RadioButton
//======================================================================================================
struct QMWRadioButtonInterface : public QMWCustomWidgetInterface
{
    explicit QMWRadioButtonInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// RaisedButton
//======================================================================================================
struct QMWRaisedButtonInterface : public QMWCustomWidgetInterface
{
    explicit QMWRaisedButtonInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// ScrollBar
//======================================================================================================
#if 0
struct QMWScrollBarInterface : public QMWCustomWidgetInterface
{
    explicit QMWScrollBarInterface();
    QWidget* createWidget(QWidget* parent) override;
};
#endif
//======================================================================================================
// Slider
//======================================================================================================
struct QMWSliderInterface : public QMWCustomWidgetInterface
{
    explicit QMWSliderInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// Snackbar
//======================================================================================================
struct QMWSnackbarInterface : public QMWCustomWidgetInterface
{
    explicit QMWSnackbarInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// Switch
//======================================================================================================
struct QMWSwitchInterface : public QMWCustomWidgetInterface
{
    explicit QMWSwitchInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// TextField
//======================================================================================================
struct QMWTextFieldInterface : public QMWCustomWidgetInterface
{
    explicit QMWTextFieldInterface();
    QWidget* createWidget(QWidget* parent) override;
};
//======================================================================================================
// TabLayout
//======================================================================================================
class QMWTabLayoutInterface : public QObject, public QMWCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit QMWTabLayoutInterface(QObject *parent = nullptr);

    QWidget* createWidget(QWidget* parent) override;
    bool     isContainer() const override { return true; }
    void     initialize(QDesignerFormEditorInterface* formEditor) override;
    bool     isInitialized() const override { return initialized_; }

private Q_SLOTS:
    void currentIndexChanged(int);
    void currentTabTitleChanged(const QString&);

private:
    bool initialized_ = false;
};
//======================================================================================================
// All
//======================================================================================================
class QMWCustomWidgetCollectionInterface
    : public QObject
    , public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")

public:
    QMWCustomWidgetCollectionInterface(QObject *parent = nullptr);
    ~QMWCustomWidgetCollectionInterface() override;
    QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> plugins_;
};
