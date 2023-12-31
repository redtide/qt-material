#ifndef MATERIAL_AUTOCOMPLETE_H
#define MATERIAL_AUTOCOMPLETE_H

#include "textfield.hpp"
#include "dlimpexp.hpp"

class MaterialAutoCompletePrivate;

class QT_MATERIAL_EXPORT MaterialAutoComplete : public MaterialTextField
{
    Q_OBJECT

    Q_DISABLE_COPY(MaterialAutoComplete)
    Q_DECLARE_PRIVATE(MaterialAutoComplete)

    Q_PROPERTY(QStringList dataSource READ dataSource WRITE setDataSource)

public:
    explicit MaterialAutoComplete(QWidget* parent = nullptr);
    ~MaterialAutoComplete();

    void setDataSource(const QStringList& data);
    QStringList dataSource() const;

Q_SIGNALS:
    void itemSelected(QString);

protected Q_SLOTS:
    void updateResults(QString text);

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // MATERIAL_AUTOCOMPLETE_H
