#ifndef OBSERVER_H
#define OBSERVER_H


// interface of observer for The Observer pattern


class Observer {

public:

    virtual ~Observer() = default;

    virtual void update() = 0;

};



#endif // OBSERVER_H
