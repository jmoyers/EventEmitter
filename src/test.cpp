#include <iostream>
#include "event.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

void string_handler(string identifier, string payload){
	cout << identifier << ": " << payload << " fired" << endl;
}

void int_handler(string identifier, int payload){
	cout << identifier << ": " << payload << " fired" << endl;
}

int main(){
	EventEmitter<string> stringEmitter;
	
	stringEmitter.addListener("deeply.nested.test", boost::bind(string_handler, "string will fire #1", _1));
	stringEmitter.addListener("deeply.*", 				boost::bind(string_handler, "string will fire #2", _1));
	stringEmitter.addListener("deeply.*.test", 		boost::bind(string_handler, "string will fire #3", _1));
	stringEmitter.addListener("deeply.*.bad", 		boost::bind(string_handler, "string won't fire", _1));
	
	stringEmitter.emit("deeply.nested.test", "This is the payload .. ");
	
	EventEmitter<int> intEmitter;
	
	intEmitter.addListener("this.is.a.channel",  boost::bind(int_handler, "int will fire #1", _1));
	intEmitter.addListener("this.*", 				boost::bind(int_handler, "int will fire #2", _1));
	intEmitter.addListener("this.*.channel", 		boost::bind(int_handler, "int will fire #3", _1));
	intEmitter.addListener("aint.gonna.*", 	   boost::bind(int_handler, "int won't fire", _1));
	
	intEmitter.emit("this.is.a.channel", 42);
		
   return 0;
}