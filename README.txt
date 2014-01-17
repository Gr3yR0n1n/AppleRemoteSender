AppleRemoteSender

Emulate the Apple IR Remote with an Arduino an IR LED

update by Samy Kamkar to work with arduino 1.0
code@samy.pl -- http://samy.pl -- 1/16/2014

Copyright (c) 2008, Casey Callendrello
c1 at caseyc.net // caseyc.net


Should be pretty self-explanatory.  See the .h file for every method, but the ones your are probably interested in are:

ars = AppleRemoteSender(pin)

ars.menu()
ars.play()
ars.right()
ars.left()
ars.up()
ars.down()
