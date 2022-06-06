#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include "TypeDefs.hpp"


class IObservable: public QObject {
    Q_OBJECT
public:
    explicit IObservable(QObject* parent = nullptr): QObject(parent){};
signals:
    void objectHasChanged();
};

#endif // IOBSERVABLE_H
