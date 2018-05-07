#include "invalidOperationException.h"

InvalidOperationException::InvalidOperationException(const char * const exception) {
	this->exception = new char[strlen(exception) + 1];
	strcpy(this->exception, exception);
}

InvalidOperationException::~InvalidOperationException() {
	delete [] this->exception;
}
