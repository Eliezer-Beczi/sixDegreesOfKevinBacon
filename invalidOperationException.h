#pragma once

#include <cstring>
#include <exception>

class InvalidOperationException : public std::exception {
private:
 	char *exception;

public:
 	InvalidOperationException(const char * const);
 	~InvalidOperationException();

	const char * what() const throw () {
		return exception;
	}
};
