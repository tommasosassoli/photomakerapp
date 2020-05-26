#ifndef PHOTOMAKERAPP_OBSERVER_H
#define PHOTOMAKERAPP_OBSERVER_H


class Observer {
public:
    virtual ~Observer() {}
    virtual	void update() = 0;
};


#endif //PHOTOMAKERAPP_OBSERVER_H
