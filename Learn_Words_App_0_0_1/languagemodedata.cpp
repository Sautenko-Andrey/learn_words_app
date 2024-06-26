#include "languagemodedata.h"


// interface's methods implementation
void LanguageModeData::registerObserver(Observer *observer){
    observers.push_back(observer);
}

void LanguageModeData::removeObserver(Observer *observer){
    observers.removeOne(observer);
}

void LanguageModeData::notifyObservers(){
    for(auto &observer : observers){
        observer->update();
    }
}

// getter
All_Languges& LanguageModeData::getLanguageMode() {
    return userLanguageMode;
}

// notifying observers
void LanguageModeData::modeChanged(){
    notifyObservers();
}


void LanguageModeData::changeMode(All_Languges new_mode){
    userLanguageMode = new_mode;
    modeChanged();
}
