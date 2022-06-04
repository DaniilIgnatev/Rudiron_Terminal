#ifndef IOPTIONSMODELDELEGATE_H
#define IOPTIONSMODELDELEGATE_H

#include <QObject>
#include "optionsmodel.hpp"


class IOptionsModelDelegate : public QObject{
    Q_OBJECT
    Q_PROPERTY(OptionsModel* optionsModel READ getOptionsModel WRITE setOptionsModel NOTIFY optionsModelChanged)

public:
    explicit IOptionsModelDelegate(QObject* parent = nullptr);

    virtual OptionsModel* getOptionsModel();
    virtual void setOptionsModel(OptionsModel* newModel);

protected slots:
    virtual void onOptionsModelChanged(OptionsModel* newValue);

public:
signals:
    void optionsModelChanged(OptionsModel* newValue);
};

#endif // IOPTIONSMODELDELEGATE_H
