#include "MainWindow.hpp"

#include "AppBarSettings.hpp"
#include "AutoCompleteSettings.hpp"
#include "AvatarSettings.hpp"
#include "BadgeSettings.hpp"
#include "CheckBoxSettings.hpp"
#include "CircularProgressSettings.hpp"
#include "DialogSettings.hpp"
#include "DrawerSettings.hpp"
#include "FABSettings.hpp"
#include "FlatButtonSettings.hpp"
#include "IconButtonSettings.hpp"
#include "ProgressSettings.hpp"
#include "RadioButtonSettings.hpp"
#include "RaisedButtonSettings.hpp"
#include "ScrollBarSettings.hpp"
#include "SliderSettings.hpp"
#include "SnackbarSettings.hpp"
#include "TabsSettings.hpp"
#include "TextFieldSettings.hpp"
#include "SwitchSettings.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QStyleHints>

static void addListItem(Ui::MainWindow* ui, const QString& label)
{
    ui->list->addItem(label);
    ui->list->setMinimumWidth(ui->list->sizeHintForColumn(0));
    ui->list->setMaximumWidth(ui->list->sizeHintForColumn(0));
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    AppBarSettings*           appBar       = new AppBarSettings(ui_->stack);
    AutoCompleteSettings*     autoComplete = new AutoCompleteSettings(ui_->stack);
    AvatarSettings*           avatar       = new AvatarSettings(ui_->stack);
    BadgeSettings*            badge        = new BadgeSettings(ui_->stack);
    CheckBoxSettings*         chkBox       = new CheckBoxSettings(ui_->stack);
    CircularProgressSettings* circProgress = new CircularProgressSettings(ui_->stack);
    DialogSettings*           dialog       = new DialogSettings(ui_->stack);
    DrawerSettings*           drawer       = new DrawerSettings(ui_->stack);
    FlatButtonSettings*       flatBtn      = new FlatButtonSettings(ui_->stack);
    FABSettings*              fab          = new FABSettings(ui_->stack);
    IconButtonSettings*       iconBtn      = new IconButtonSettings(ui_->stack);
    ProgressSettings*         progress     = new ProgressSettings(ui_->stack);
    RadioButtonSettings*      radioBtn     = new RadioButtonSettings(ui_->stack);
    RaisedButtonSettings*     raisedBtn    = new RaisedButtonSettings(ui_->stack);
    ScrollBarSettings*        scrollBar    = new ScrollBarSettings(ui_->stack);
    SliderSettings*           slider       = new SliderSettings(ui_->stack);
    SnackbarSettings*         snackbar     = new SnackbarSettings(ui_->stack);
    SwitchSettings*           switch_      = new SwitchSettings(ui_->stack);
    TabsSettings*             tabs         = new TabsSettings(ui_->stack);
    TextFieldSettings*        textField    = new TextFieldSettings(ui_->stack);

    ui_->stack->addWidget(appBar);
    ui_->stack->addWidget(autoComplete);
    ui_->stack->addWidget(avatar);
    ui_->stack->addWidget(badge);
    ui_->stack->addWidget(chkBox);
    ui_->stack->addWidget(circProgress);
    ui_->stack->addWidget(dialog);
    ui_->stack->addWidget(drawer);
    ui_->stack->addWidget(fab);
    ui_->stack->addWidget(flatBtn);
    ui_->stack->addWidget(iconBtn);
    ui_->stack->addWidget(progress);
    ui_->stack->addWidget(radioBtn);
    ui_->stack->addWidget(raisedBtn);
    ui_->stack->addWidget(scrollBar);
    ui_->stack->addWidget(slider);
    ui_->stack->addWidget(snackbar);
    ui_->stack->addWidget(switch_);
    ui_->stack->addWidget(tabs);
    ui_->stack->addWidget(textField);

    ui_->list->setMinimumWidth(ui_->list->sizeHintForColumn(0) + 12);
    ui_->list->setMaximumWidth(ui_->list->sizeHintForColumn(0) + 12);
    ui_->list->setCurrentRow(0);

    QListWidget*    list  = ui_->list;
    QStackedWidget* stack = ui_->stack;
    QObject::connect(list,  &QListWidget::currentItemChanged, this, [this, stack, list]() {
        stack->setCurrentIndex(list->currentRow());
    });
    setWindowIcon(QIcon(":/appicon"));
}

MainWindow::~MainWindow()
{
}
