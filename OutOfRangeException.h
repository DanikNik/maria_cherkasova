//
// Created by daniknik on 19.05.18.
//

#ifndef MARIA_CHERKASOVA_OUTOFRANGEEXCEPTION_H
#define MARIA_CHERKASOVA_OUTOFRANGEEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

using namespace std;

class OutOfRangeException : public exception{
private:
    string msg;
public:
    OutOfRangeException();
    OutOfRangeException(int index);

    const char* what() const throw(){
        return msg.c_str();
    }
};

OutOfRangeException::OutOfRangeException(){
    this -> msg = "Out Of Range Exception";
}

OutOfRangeException::OutOfRangeException(int index)
{
    std::stringstream ss;
    ss << std::string("Out of range exception with index = ") << index;

    this -> msg = ss.str();
}



#endif //MARIA_CHERKASOVA_OUTOFRANGEEXCEPTION_H
