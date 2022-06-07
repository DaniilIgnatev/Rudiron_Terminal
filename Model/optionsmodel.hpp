#ifndef OPTIONSMODEL_HPP
#define OPTIONSMODEL_HPP

#include "optionsoutputmodel.hpp"
#include "optionsinputmodel.hpp"
#include "observableqobject.hpp"

class OptionsModel : public ObservableQObject, public IPrintable
{
    Q_OBJECT
    Q_PROPERTY(OptionsOutputModel* outputModel READ getOutputModel WRITE setOutputModel NOTIFY outputModelChanged)
    Q_PROPERTY(QString portName READ getPortName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(OptionsInputModel* inputModel READ getInputModel WRITE setInputModel NOTIFY inputModelChanged)

public:
    explicit OptionsModel(QObject* parent = nullptr);
    explicit OptionsModel(OptionsOutputModel* outputModel, QString portName, OptionsInputModel* inputModel, QObject* parent = nullptr);

private:
    OptionsOutputModel* _outputModel = nullptr;

    QString _portName;

    OptionsInputModel* _inputModel = nullptr;

public:
    Q_INVOKABLE virtual QString printable() override;

    OptionsOutputModel *getOutputModel() const;
    void setOutputModel(OptionsOutputModel *newOutputModel);

    QString getPortName() const;
    void setPortName(const QString &value);

    OptionsInputModel *getInputModel() const;
    void setInputModel(OptionsInputModel *newInputModel);

signals:
    void outputModelChanged();
    void portNameChanged();
    void inputModelChanged();
};


#endif // OPTIONSMODEL_HPP
