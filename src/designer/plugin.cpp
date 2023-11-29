#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include <QIcon>
#include <QtPlugin>

#include <QtMaterialWidgets/appbar.hpp>
#include <QtMaterialWidgets/autocomplete.hpp>
#include <QtMaterialWidgets/avatar.hpp>
#include <QtMaterialWidgets/appbar.hpp>
#include <QtMaterialWidgets/badge.hpp>
#include <QtMaterialWidgets/checkbox.hpp>
#include <QtMaterialWidgets/circularprogress.hpp>
#include <QtMaterialWidgets/dialog.hpp>
#include <QtMaterialWidgets/drawer.hpp>
#include <QtMaterialWidgets/fab.hpp>
#include <QtMaterialWidgets/flatbutton.hpp>
#include <QtMaterialWidgets/iconbutton.hpp>
#include <QtMaterialWidgets/progress.hpp>
#include <QtMaterialWidgets/appbar.hpp>
#include <QtMaterialWidgets/radiobutton.hpp>
#include <QtMaterialWidgets/raisedbutton.hpp>
#include <QtMaterialWidgets/scrollbar.hpp>
#include <QtMaterialWidgets/slider.hpp>
#include <QtMaterialWidgets/snackbar.hpp>
#include <QtMaterialWidgets/switch.hpp>
#include <QtMaterialWidgets/tablayout.hpp>
#include <QtMaterialWidgets/textfield.hpp>

#include "plugin.hpp"
#include "tablayoutcontainerextension.hpp"
#include "tablayoutextensionfactory.hpp"

//======================================================================================================
// AppBar
//======================================================================================================
QMWAppBarInterface::QMWAppBarInterface()
{
    name_   = QStringLiteral("MaterialAppBar");
    include_= QStringLiteral("<QtMaterialWidgets/appbar.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/appbar"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialAppBar\" name=\"appBar\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>320</width>\
    <height>48</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWAppBarInterface::createWidget(QWidget* parent)
{
    return new MaterialAppBar(parent);
}
//======================================================================================================
// AutoComplete
//======================================================================================================
QMWAutoCompleteInterface::QMWAutoCompleteInterface()
{
    name_   = QStringLiteral("MaterialAutoComplete");
    include_= QStringLiteral("<QtMaterialWidgets/autocomplete.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/autocomplete"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialAutoComplete\" name=\"autoComplete\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>120</width>\
    <height>22</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWAutoCompleteInterface::createWidget(QWidget* parent)
{
    return new MaterialAutoComplete(parent);
}
//======================================================================================================
// Avatar
//======================================================================================================
QMWAvatarInterface::QMWAvatarInterface()
{
    name_   = QStringLiteral("MaterialAvatar");
    include_= QStringLiteral("<QtMaterialWidgets/avatar.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/avatar"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialAvatar\" name=\"avatar\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>40</width>\
    <height>40</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWAvatarInterface::createWidget(QWidget* parent)
{
    return new MaterialAvatar(parent);
}
//======================================================================================================
// Badge
//======================================================================================================
QMWBadgeInterface::QMWBadgeInterface()
{
    name_   = QStringLiteral("MaterialBadge");
    include_= QStringLiteral("<QtMaterialWidgets/badge.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/badge"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialBadge\" name=\"badge\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>40</width>\
    <height>40</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWBadgeInterface::createWidget(QWidget* parent)
{
    return new MaterialBadge(parent);
}
//======================================================================================================
// CheckBox
//======================================================================================================
QMWCheckBoxInterface::QMWCheckBoxInterface()
{
    name_   = QStringLiteral("MaterialCheckBox");
    include_= QStringLiteral("<QtMaterialWidgets/checkbox.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/checkbox"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialCheckBox\" name=\"checkBox\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>40</width>\
    <height>40</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWCheckBoxInterface::createWidget(QWidget* parent)
{
    return new MaterialCheckBox(parent);
}
//======================================================================================================
// CircularProgress
//======================================================================================================
QMWCircularProgressInterface::QMWCircularProgressInterface()
{
    name_   = QStringLiteral("MaterialCircularProgress");
    include_= QStringLiteral("<QtMaterialWidgets/circularprogress.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/circularprogress"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialCircularProgress\" name=\"circProgress\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>64</width>\
    <height>64</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWCircularProgressInterface::createWidget(QWidget* parent)
{
    return new MaterialCircularProgress(parent);
}
//======================================================================================================
// Dialog
//======================================================================================================
QMWDialogInterface::QMWDialogInterface()
{
    name_   = QStringLiteral("MaterialDialog");
    include_= QStringLiteral("<QtMaterialWidgets/dialog.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/dialog"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialDialog\" name=\"dialog\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>400</width>\
    <height>200</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWDialogInterface::createWidget(QWidget* parent)
{
    return new MaterialDialog(parent);
}
//======================================================================================================
// Drawer
//======================================================================================================
QMWDrawerInterface::QMWDrawerInterface()
{
    name_   = QStringLiteral("MaterialDrawer");
    include_= QStringLiteral("<QtMaterialWidgets/drawer.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/drawer"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialDrawer\" name=\"drawer\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>120</width>\
    <height>120</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWDrawerInterface::createWidget(QWidget* parent)
{
    return new MaterialDrawer(parent);
}
//======================================================================================================
// FloatingActionButton
//======================================================================================================
QMWFabInterface::QMWFabInterface()
{
    name_   = QStringLiteral("MaterialFloatingActionButton");
    include_= QStringLiteral("<QtMaterialWidgets/fab.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/fab"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialFloatingActionButton\" name=\"fab\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>56</width>\
    <height>56</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWFabInterface::createWidget(QWidget* parent)
{
    return new MaterialFloatingActionButton(QIcon(), parent);
}
//======================================================================================================
// FlatButton
//======================================================================================================
QMWFlatButtonInterface::QMWFlatButtonInterface()
{
    name_   = QStringLiteral("MaterialFlatButton");
    include_= QStringLiteral("<QtMaterialWidgets/flatbutton.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/flatbutton"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialFlatButton\" name=\"flatBtn\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>40</width>\
    <height>40</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWFlatButtonInterface::createWidget(QWidget* parent)
{
    return new MaterialFlatButton(parent);
}
//======================================================================================================
// IconButton
//======================================================================================================
QMWIconButtonInterface::QMWIconButtonInterface()
{
    name_   = QStringLiteral("MaterialIconButton");
    include_= QStringLiteral("<QtMaterialWidgets/iconbutton.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/iconbutton"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialIconButton\" name=\"iconBtn\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>40</width>\
    <height>40</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWIconButtonInterface::createWidget(QWidget* parent)
{
    return new MaterialIconButton(QIcon(), parent);
}
//======================================================================================================
// Progress
//======================================================================================================
QMWProgressInterface::QMWProgressInterface()
{
    name_   = QStringLiteral("MaterialProgress");
    include_= QStringLiteral("<QtMaterialWidgets/progress.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/progress"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialProgress\" name=\"progress\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>120</width>\
    <height>4</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWProgressInterface::createWidget(QWidget* parent)
{
    return new MaterialProgress(parent);
}
//======================================================================================================
// RadioButton
//======================================================================================================
QMWRadioButtonInterface::QMWRadioButtonInterface()
{
    name_   = QStringLiteral("MaterialRadioButton");
    include_= QStringLiteral("<QtMaterialWidgets/radiobutton.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/radiobutton"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialRadioButton\" name=\"radioBtn\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>40</width>\
    <height>40</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWRadioButtonInterface::createWidget(QWidget* parent)
{
    return new MaterialRadioButton(parent);
}
//======================================================================================================
// RaisedButton
//======================================================================================================
QMWRaisedButtonInterface::QMWRaisedButtonInterface()
{
    name_   = QStringLiteral("MaterialRaisedButton");
    include_= QStringLiteral("<QtMaterialWidgets/raisedbutton.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/raisedbutton"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialRaisedButton\" name=\"raisedBtn\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>40</width>\
    <height>40</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWRaisedButtonInterface::createWidget(QWidget* parent)
{
    return new MaterialRaisedButton(parent);
}
//======================================================================================================
// ScrollBar
//======================================================================================================
#if 0
QMWScrollBarInterface::QMWScrollBarInterface()
{
    name_   = QStringLiteral("MaterialScrollBar");
    include_= QStringLiteral("<QtMaterialWidgets/scrollbar.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/scrollbar"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialScrollBar\" name=\"scrollBar\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>4</width>\
    <height>120</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWScrollBarInterface::createWidget(QWidget* parent)
{
    return new MaterialScrollBar(parent);
}
#endif
//======================================================================================================
// Slider
//======================================================================================================
QMWSliderInterface::QMWSliderInterface()
{
    name_   = QStringLiteral("MaterialSlider");
    include_= QStringLiteral("<QtMaterialWidgets/slider.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/slider"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialSlider\" name=\"slider\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>128</width>\
    <height>22</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWSliderInterface::createWidget(QWidget* parent)
{
    return new MaterialSlider(parent);
}
//======================================================================================================
// Snackbar
//======================================================================================================
QMWSnackbarInterface::QMWSnackbarInterface()
{
    name_   = QStringLiteral("MaterialSnackbar");
    include_= QStringLiteral("<QtMaterialWidgets/snackbar.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/snackbar"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialSnackbar\" name=\"snackbar\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>128</width>\
    <height>22</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWSnackbarInterface::createWidget(QWidget* parent)
{
    return new MaterialSnackbar(parent);
}
//======================================================================================================
// Switch
//======================================================================================================
QMWSwitchInterface::QMWSwitchInterface()
{
    name_   = QStringLiteral("MaterialSwitch");
    include_= QStringLiteral("<QtMaterialWidgets/switch.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/switch"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialSwitch\" name=\"switch\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>64</width>\
    <height>48</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWSwitchInterface::createWidget(QWidget* parent)
{
    return new MaterialSwitch(parent);
}
//======================================================================================================
// TextField
//======================================================================================================
QMWTextFieldInterface::QMWTextFieldInterface()
{
    name_   = QStringLiteral("MaterialTextField");
    include_= QStringLiteral("<QtMaterialWidgets/textfield.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/textfield"));
    xml_    = QStringLiteral("\
<ui language=\"c++\">\
 <widget class=\"MaterialTextField\" name=\"textfield\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>120</width>\
    <height>22</height>\
   </rect>\
  </property>\
 </widget>\
</ui>"
    );
}
QWidget* QMWTextFieldInterface::createWidget(QWidget* parent)
{
    return new MaterialTextField(parent);
}
//======================================================================================================
// TabLayout
//======================================================================================================
QMWTabLayoutInterface::QMWTabLayoutInterface(QObject *parent)
    : QObject(parent)
{
    name_   = QLatin1String("MaterialTabLayout");
    include_= QLatin1String("<QtMaterialWidgets/tablayout.hpp>");
    icon_   = QIcon(QStringLiteral(":/material/tablayout"));
    xml_    = QLatin1String("\
<ui language=\"c++\">\
 <widget class=\"MaterialTabLayout\" name=\"tabLayout\">\
  <property name=\"geometry\">\
   <rect>\
    <x>0</x>\
    <y>0</y>\
    <width>128</width>\
    <height>128</height>\
   </rect>\
  </property>\
  <widget class=\"QWidget\" name=\"page\" />\
 </widget>\
 <customwidgets>\
  <customwidget>\
   <class>MaterialTabLayout</class>\
   <extends>QWidget</extends>\
   <addpagemethod>addTab</addpagemethod>\
  </customwidget>\
 </customwidgets>\
</ui>"
    );
}
QWidget* QMWTabLayoutInterface::createWidget(QWidget* parent)
{
    MaterialTabLayout* widget = new MaterialTabLayout(parent);
    connect(widget, &MaterialTabLayout::currentIndexChanged,
            this, &QMWTabLayoutInterface::currentIndexChanged);
    connect(widget, &MaterialTabLayout::tabTitleChanged,
            this, &QMWTabLayoutInterface::currentTabTitleChanged);
    return widget;
}

void QMWTabLayoutInterface::initialize(QDesignerFormEditorInterface* formEditor)
{
    if (initialized_)
        return;

    QExtensionManager* manager = formEditor->extensionManager();
    QExtensionFactory* factory = new QMWTabLayoutExtensionFactory(manager);

    Q_ASSERT(manager != nullptr);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));

    initialized_ = true;
}

void QMWTabLayoutInterface::currentIndexChanged(int)
{
    MaterialTabLayout* widget = qobject_cast<MaterialTabLayout*>(sender());
    if (widget) {
        QDesignerFormWindowInterface *form = QDesignerFormWindowInterface::findFormWindow(widget);
        if (form)
            form->emitSelectionChanged();
    }
}

void QMWTabLayoutInterface::currentTabTitleChanged(const QString&)
{
    MaterialTabLayout* tabLayout = qobject_cast<MaterialTabLayout*>(sender());
    if (tabLayout) {
        QWidget* page = tabLayout->widget(tabLayout->currentIndex());
        QDesignerFormWindowInterface* form
            = QDesignerFormWindowInterface::findFormWindow(tabLayout);
        if (form) {
            QDesignerFormEditorInterface*    editor  = form->core();
            QExtensionManager*               manager = editor->extensionManager();
            QDesignerPropertySheetExtension* sheet;

            sheet = qt_extension<QDesignerPropertySheetExtension*>(manager, page);
            const int propertyIndex = sheet->indexOf(QLatin1String("windowTitle"));
            sheet->setChanged(propertyIndex, true);
        }
    }
}
