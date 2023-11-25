#ifndef RAISEDBUTTONSETTINGSEDITOR_H
#define RAISEDBUTTONSETTINGSEDITOR_H

#include "flatbuttonsettingseditor.hpp"

class RaisedButtonSettingsEditor : public FlatButtonSettingsEditor
{
    Q_OBJECT

public:
    explicit RaisedButtonSettingsEditor(QWidget *parent = 0);
    ~RaisedButtonSettingsEditor();
};

#endif // RAISEDBUTTONSETTINGSEDITOR_H
