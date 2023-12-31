"""

Strategy pattern:
    A base class with a certain number of methods. 
    Each subclass wants those method tailered to their own needs.
    This gets complicated when you have huge number of subclasses, because, you end up:
        - either copy pasting implementations across various subclasses
        - or you find it hard to reuse some implmentation that was already done in another subclass
        (let alone the refactoring nightmare that comes with it)

    Now, you will have a interface for each methodology, with different flavours of it as a concrete implementation.

    This way, the client can mix and match each of these concrete implementations to tailor accourding to their needs.
    (This is called composition over inheritance)

"""

class IQuackStrategy:
    def run(self) -> str:
        raise NotImplementedError()

class SimpleQuack(IQuackStrategy):
    def run(self) -> str:
        return "Quack!"

class DeathQuack(IQuackStrategy):
    def run(self) -> str:
        return "QUACK!!!"

# ---------------------------------------------

class IFlyStrategy:
    def run(self) -> str:
        raise NotImplementedError()

class SimpleFly(IFlyStrategy):
    def run(self) -> str:
        return "Flying!"

class SonicFly(IFlyStrategy):
    def run(self) -> str:
        return "Sonic flying!"
    
# ---------------------------------------------

class IBaseDuck():
    quacker: IQuackStrategy
    flyer: IFlyStrategy


class DomesticDuck(IBaseDuck):

    def __init__(self, quacker: IQuackStrategy, flyer: IFlyStrategy):
        self.quacker = quacker
        self.flyer = flyer

    def execute(self):
        self.quacker.run()
        self.flyer.run()
        # other operations
        
