#!/usr/bin/env python3


class Animal(object):
    def __init__(self, name='kitty'):
        self.name = name

    def __del__(self):
        pass


class Dog(Animal):

    # the constructor needs to call the parent one
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def __del__(self):
        super().__del__()

    def scream(self):
        print('OUAFF')


class Cat(Animal):

    # the constructor needs to call the parent one
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def __del__(self):
        super().__del__()

    def scream(self):
        print('MIAOU')


d = Dog('puppy')
print(d.name)
d.scream()

c = Cat()
print(c.name)
c.scream()
