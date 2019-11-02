#include "Exceptions.h"

namespace custom_exceptions {
    const char * NoFriendException::what() const throw() {
        return "This human is not a friend yet.";
    }
}