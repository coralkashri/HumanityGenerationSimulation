#ifndef HUMANITYGENERATIONSIMULATION_EXCEPTIONS_H
#define HUMANITYGENERATIONSIMULATION_EXCEPTIONS_H

#include <exception>

namespace custom_exceptions {
    class NoFriendException : public std::exception {
        virtual const char *what() const throw();
    };
};


#endif //HUMANITYGENERATIONSIMULATION_EXCEPTIONS_H
