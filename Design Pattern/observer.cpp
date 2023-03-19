#include<iostream>
#include <memory>
#include <list>

using namespace std;

// Bluetooth analogy
typedef enum { CONNECT, DISCONNECT, LOW_POWER } status;

// Listens to the event/state/etc.
class IObserver {
    public:
        virtual void update(const status& message) = 0;
};

// Notifies the Listeners once a event happens
// Publisher
class Subject {
    private:
        // Takes care of memory leakes and ownership management
        list<shared_ptr<IObserver>> observerList;

        void notifyAll(status message){
            for(auto& subs: observerList){
                subs->update(message);
            }
        }

    public:
        void regListener(shared_ptr<IObserver> observer){
            observerList.push_back(observer);
        }

        void unRegListener(shared_ptr<IObserver> observer){
            observerList.remove(observer);
        }

        // ---------------
        // If battery falls below threshold, notifys all observer
        void batteryWarning(int val) {
            int BATTERY_THRESHOLD = 30;
            if(val < BATTERY_THRESHOLD){
                notifyAll(LOW_POWER);
            }
        }

        void newConnection() {
            notifyAll(CONNECT);
        }

        void newDisconnection() {
            notifyAll(DISCONNECT);
        }
};

// A listener
// Subscriber
class Display: public IObserver{
    private:
        string __class__;
        bool isDeviceOn;
    public:
        Display() {
            __class__ = __func__;
            isDeviceOn = true;
        }

        void update(const status& message){
            if(message == CONNECT)
                cout<<__class__<<" :: "<<message<<" Hello User!" <<endl;

            else if(isDeviceOn && message == LOW_POWER) {
                // let's say, this way it turns off the display
                cout<<__class__<<" :: "<<"DisplayShutdown"<<endl;
                isDeviceOn = false;

            } else if (isDeviceOn && message == DISCONNECT)
                cout<<__class__<<" :: "<<message<<" See ya~"<<endl;
        }
};

// Another listener
// Subscriber
class Audio: public IObserver{
    private:
        string __class__;
    public:
        Audio() {
            __class__ = __func__;
        }

        void update(const status& message){
            switch (message) {
                case(LOW_POWER):
                    cout<<__class__<<" !! "<<"Turning off display <<tts voice>"<<endl;
                    break;
                case(DISCONNECT):
                    cout<<__class__<<" !! "<<"Disconnected <tts voice>"<<endl;
                    break;
                case(CONNECT):
                    cout<<__class__<<" !! "<<"Connected <tts voice>"<<endl;
                    break;
            }
        }
};

int main(){
    unique_ptr<Subject> subject = make_unique<Subject>();

    // of type Interface           class that implements the interface
    shared_ptr<IObserver> display = make_shared<Display>();
    shared_ptr<IObserver> audio = make_shared<Audio>();

    subject->regListener(audio);
    subject->regListener(display);

    subject->newConnection();

    subject->batteryWarning(80) ;
    subject->batteryWarning(75) ;
    subject->batteryWarning(35) ;
    subject->batteryWarning(15) ;

    subject->newDisconnection();
}
