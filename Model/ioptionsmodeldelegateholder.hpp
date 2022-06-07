#ifndef IOPTIONSMODELDELEGATEHOLDERHPP_H
#define IOPTIONSMODELDELEGATEHOLDERHPP_H

#include "ioptionsmodeldelegate.hpp"


class IOptionsModelDelegateHolder: public IOptionsModelDelegate {
    Q_OBJECT
public:
    IOptionsModelDelegateHolder(QObject* parent = nullptr);

    virtual IOptionsModelDelegate *getOptionsModelDelegate() const;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate);
};

#endif // IOPTIONSMODELDELEGATEHOLDERHPP_H
