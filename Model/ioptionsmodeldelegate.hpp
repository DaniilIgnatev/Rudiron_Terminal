#ifndef IOPTIONSMODELDELEGATE_H
#define IOPTIONSMODELDELEGATE_H

#include <QObject>
#include "optionsmodel.hpp"
#include "observableqobject.hpp"


class IOptionsModelDelegate : public ObservableQObject {
    Q_OBJECT
    Q_PROPERTY(OptionsModel* optionsModel READ getOptionsModel WRITE setOptionsModel NOTIFY optionsModelChanged)

public:
    explicit IOptionsModelDelegate(QObject* parent = nullptr);

    virtual OptionsModel* getOptionsModel();
    virtual void setOptionsModel(OptionsModel* newModel);

protected slots:
    virtual void onOptionsModelChanged();

signals:
    void optionsModelChanged();
};

#endif // IOPTIONSMODELDELEGATE_H
