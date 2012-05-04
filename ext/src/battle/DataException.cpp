#include <DataException.h>

#include <sstream>

DataException::DataException(const char* file, int line, const char* func, const char* message) :
	file(file), line(line), func(func), message(message)
{
	
}

DataException::~DataException() throw() {

}

const char* DataException::what() const throw() {
	std::stringstream sstr;
	sstr<<file<<":"<<line<<" in "<<func<<" message="<<message;
	return sstr.str().c_str();
}
