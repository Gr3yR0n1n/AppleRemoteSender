/*

update by Samy Kamkar to work with arduino 1.0
code@samy.pl -- http://samy.pl -- 1/16/2014

Apple Remote Sender:
Copyright Casey Callendrello 2008


c1 at caseyc dot net

For more information, see http://www.caseyc.net/home/node/10

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


*/


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "AppleRemoteSender.h"

#ifdef _A_DIGITAL_WRITE_FAST
#include <digitalWriteFast.h>
#endif


AppleRemoteSender::AppleRemoteSender(int pin)
{
	_irpin = pin;
	_remote_id = 0x01;
	
	//ready the pin
#ifdef _A_DIGITAL_WRITE_FAST
	pinModeFast(_irpin, OUTPUT);
	digitalWriteFast(_irpin, LOW);
#else
	pinMode(_irpin, OUTPUT);
	digitalWrite(_irpin, LOW);
#endif
	
	
}

AppleRemoteSender::AppleRemoteSender(int pin, byte remote_id)
{
	_irpin = pin;
	_remote_id = remote_id;
	
	//ready the pin
#ifdef _A_DIGITAL_WRITE_FAST
	pinModeFast(_irpin, OUTPUT);
	digitalWriteFast(_irpin, LOW);
#else
	pinMode(_irpin, OUTPUT);
	digitalWrite(_irpin, LOW);
#endif
}


void AppleRemoteSender::set_remote_id(byte remote_id)
{
	_remote_id = remote_id;
}

void AppleRemoteSender::send(byte remote_id, byte key)
{
	//prepare data
	long temp = remote_id;
	temp = temp << 8;
	temp += key;
	temp = temp << 16;
	temp += APPLE_ID;
	
	//send preamble
	oscWrite(9000);
	delayMicroseconds(3040);

	byte bit = 0;
	//send data
	for(int i = 0; i < 32; i++)
	{
		bit = temp % 2;
		temp = temp >> 1;
		//space
		oscWrite(560);

		//data
		if(bit == 0)
		{
			delayMicroseconds(565);
		}
		else
		{
			delayMicroseconds(1690);
		}
	}
	//end of data header
	oscWrite(560);
	
}
void AppleRemoteSender::send(byte key)
{
	send(_remote_id, key);	
}


void AppleRemoteSender::menu(byte remote_id) { send(remote_id, MENU);}
void AppleRemoteSender::menu(){ send(MENU); }

void AppleRemoteSender::play(byte remote_id){ send(remote_id, PLAY); }
void AppleRemoteSender::play(){ send(PLAY); }

void AppleRemoteSender::right(byte remote_id){ send(remote_id, RIGHT); }
void AppleRemoteSender::right(){ send(RIGHT); }

void AppleRemoteSender::left(byte remote_id){ send(remote_id, LEFT); }
void AppleRemoteSender::left(){ send(LEFT); }

void AppleRemoteSender::up(byte remote_id){ send(remote_id, UP); }
void AppleRemoteSender::up(){ send(UP); }

void AppleRemoteSender::down(byte remote_id){ send(remote_id, DOWN); }
void AppleRemoteSender::down(){ send(DOWN); }





void AppleRemoteSender::oscWrite(int time)
{
	/*
	Sends a 38khz carrier pulse
	
	*/
  for(int i = 0; i < (time / 26) - 1; i++)
  {
#ifdef _A_DIGITAL_WRITE_FAST
    digitalWriteFast(_irpin, HIGH);
    delayMicroseconds(13);
    digitalWriteFast(_irpin, LOW);
    delayMicroseconds(13);
#else
    digitalWrite(_irpin, HIGH);
    delayMicroseconds(13);
    digitalWrite(_irpin, LOW);
    delayMicroseconds(13);
#endif
  }
}
