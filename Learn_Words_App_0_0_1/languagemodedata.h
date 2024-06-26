#ifndef LANGUAGEMODEDATA_H
#define LANGUAGEMODEDATA_H

// implementation of the Subject interface

// Available foreign languages (assumed that user is rus/ukr speaker)
enum class All_Languges {ENG, SWE};


#include"subject.h"
#include<QVector>

class LanguageModeData final : public Subject {

public:

    // interface's methods implementation
    virtual void registerObserver(Observer *observer) override;

    virtual void removeObserver(Observer *observer) override;

    virtual void notifyObservers() override;

    // getter
    All_Languges& getLanguageMode();

    // notifying observers
    void modeChanged();

    // change mode
    void changeMode(All_Languges new_mode);


private:

    QVector<Observer *> observers;

    // by default mode is for the english lessons
    All_Languges userLanguageMode = All_Languges::ENG;

};

#endif // LANGUAGEMODEDATA_H
