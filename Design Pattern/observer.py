"""
Observer pattern:
    when you want a list of observers to get notified when a state of the observable changes. 
    You have -attach, -detach, -notify and -list of observers references in subject / observable class.
"""

from abc import abstractmethod
from typing import List

class IObserver:
    @abstractmethod
    def update(self):
        pass

class IObservable:
    observers: List[IObserver]

    @abstractmethod
    def attach(self, observer: IObserver):
        pass 

    @abstractmethod
    def detach(self, observer: IObserver):
        pass 

    @abstractmethod
    def notify(self):
        pass 
# ---------------------------------------------

class ConcreteSubject(IObservable):
    # some complex state
    _state: int 

    def some_business_logic(self):
        self._state = 1

    def get_state(self):
        return self._state

    def __init__(self):
        self.observers = []

    def attach(self, observer: IObserver):
        self.observers.append(observer)

    def detach(self, observer: IObserver):
        self.observers.remove(observer)

    def notify(self):
        for observer in self.observers:
            observer.update()

class InternetNerd(IObserver):
    # Yea, depends on concrete Subject
    subject: ConcreteSubject 
    _state: int

    def __init__(self, s: ConcreteSubject):
        self.subject = s

    def update(self):
        self._state = self.subject.get_state()

