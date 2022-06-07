#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include "TypeDefs.hpp"


class ObservableQObject: public QObject {
    Q_OBJECT
public:
    explicit ObservableQObject(QObject* parent = nullptr): QObject(parent){};
signals:
    void objectHasChanged();
};

#endif // IOBSERVABLE_H
