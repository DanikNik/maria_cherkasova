#ifndef MARIA_CHERKASOVA_OUTOFRANGEEXCEPTION_H
#define MARIA_CHERKASOVA_OUTOFRANGEEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

using namespace std;

class OutOfRangeException : public exception {
private:
    string msg;
public:
    OutOfRangeException();
    OutOfRangeException(int index);

    const char* what() const throw() {
        return msg.c_str();
    }
};

OutOfRangeException::OutOfRangeException() {
    this->msg = "Out Of Range Exception";
}

OutOfRangeException::OutOfRangeException(int index)           //это он исправил
{
//	std::stringstream ss;
//	ss << std::string("Out of range exception with index = ") << index;
    msg = "Out of range exception with index = " + to_string(index);

//	this->msg = ss.str();
}



#endif