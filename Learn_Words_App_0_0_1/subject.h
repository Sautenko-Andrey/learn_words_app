#ifndef SUBJECT_H
#define SUBJECT_H

#include"observer.h"

// This is an interface of subject for Observer pattern


class Subject {

public:

    virtual ~Subject() = default;

    virtual void registerObserver(Observer *observer) = 0;

    virtual void removeObserver(Observer *observer) = 0;

    virtual void notifyObservers() = 0;

};





#endif // SUBJECT_H
