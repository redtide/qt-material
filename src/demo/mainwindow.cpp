#include "mainwindow.hpp"
#include "demoform.hpp"

#include "appbarsettingseditor.hpp"
#include "autocompletesettingseditor.hpp"
#include "avatarsettingseditor.hpp"
#include "badgesettingseditor.hpp"
#include "checkboxsettingseditor.hpp"
#include "circularprogresssettingseditor.hpp"
#include "dialogsettingseditor.hpp"
#include "drawersettingseditor.hpp"
#include "fabsettingseditor.hpp"
#include "flatbuttonsettingseditor.hpp"
#include "iconbuttonsettingseditor.hpp"
#include "progresssettingseditor.hpp"
#include "radiobuttonsettingseditor.hpp"
#include "raisedbuttonsettingseditor.hpp"
#include "scrollbarsettingseditor.hpp"
#include "slidersettingseditor.hpp"
#include "snackbarsettingseditor.hpp"
#include "tabssettingseditor.hpp"
#include "textfieldsettingseditor.hpp"
#include "switchsettingseditor.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    widget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    QListWidget *list = new QListWidget;

    layout->addWidget(list);
    layout->addLayout(stack);

    layout->setStretch(1, 2);

    setCentralWidget(widget);

    PluginDemoForm *pluginFrm = new PluginDemoForm;

    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    SwitchSettingsEditor *switch_ = new SwitchSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    AppBarSettingsEditor *appBar = new AppBarSettingsEditor;
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;

    stack->addWidget(pluginFrm);
    stack->addWidget(appBar);
    stack->addWidget(autocomplete);
    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(checkbox);
    stack->addWidget(circularProgress);
    stack->addWidget(dialog);
    stack->addWidget(drawer);
    stack->addWidget(fab);
    stack->addWidget(flatButton);
    stack->addWidget(iconButton);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(raisedButton);
    stack->addWidget(scrollBar);
    stack->addWidget(slider);
    stack->addWidget(snackbar);
    stack->addWidget(switch_);
    stack->addWidget(tabs);
    stack->addWidget(textField);

    list->addItem("Plugins");
    list->addItem("App Bar");
    list->addItem("Auto Complete");
    list->addItem("Avatar");
    list->addItem("Badge");
    list->addItem("Checkbox");
    list->addItem("Circular Progress");
    list->addItem("Dialog");
    list->addItem("Drawer");
    list->addItem("Floating Action Button");
    list->addItem("Flat Button");
    list->addItem("Icon Button");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("ScrollBar");
    list->addItem("Slider");
    list->addItem("Snackbar");
    list->addItem("Switch");
    list->addItem("Tabs");
    list->addItem("Text Field");

    list->setCurrentRow(0);

    QObject::connect(list,  &QListWidget::currentItemChanged, this, [this, stack, list]() {
        stack->setCurrentIndex(list->currentRow());
    });
}

MainWindow::~MainWindow()
{
}
