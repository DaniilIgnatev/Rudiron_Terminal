#ifndef OPTIONSMODEL_HPP
#define OPTIONSMODEL_HPP

#include "optionsoutputmodel.hpp"
#include "optionsinputmodel.hpp"
#include "observableqobject.hpp"

class OptionsModel : public ObservableQObject, public IPrintable
{
    Q_OBJECT
    Q_PROPERTY(OptionsOutputModel* outputModel READ getOutputModel WRITE setOutputModel NOTIFY outputModelChanged)
    Q_PROPERTY(OptionsInputModel* inputModel READ getInputModel WRITE setInputModel NOTIFY inputModelChanged)

public:
    explicit OptionsModel(QObject* parent = nullptr);
    explicit OptionsModel(OptionsOutputModel* outputModel, OptionsInputModel* inputModel, QObject* parent = nullptr);

private:
    OptionsOutputModel* _outputModel = nullptr;

    OptionsInputModel* _inputModel = nullptr;

public:
    OptionsOutputModel *getOutputModel() const;
    void setOutputModel(OptionsOutputModel *newOutputModel);

    OptionsInputModel *getInputModel() const;
    void setInputModel(OptionsInputModel *newInputModel);

    Q_INVOKABLE virtual QString printable() override;

signals:
    void outputModelChanged();
    void inputModelChanged();
};


#endif // OPTIONSMODEL_HPP
