#ifndef RAISEDBUTTONSETTINGSEDITOR_H
#define RAISEDBUTTONSETTINGSEDITOR_H

#include "flatbuttonsettingseditor.hpp"

class RaisedButtonSettingsEditor : public FlatButtonSettingsEditor
{
    Q_OBJECT

public:
    explicit RaisedButtonSettingsEditor(QWidget* parent = nullptr);
    ~RaisedButtonSettingsEditor();
};

#endif // RAISEDBUTTONSETTINGSEDITOR_H
