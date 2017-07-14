#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <memory>
#include <string>
#include <sstream>
#include <string>

#define THROW_TM_EXCEPTION\
    throw TM::details::TMException(__FILE__, __LINE__)\

namespace TM {
namespace details {

class TMException: public std::exception
{
    mutable std::string m_errorDesc;
    std::string m_file;
    int m_line;
    std::shared_ptr<std::stringstream> m_exceptionStream;
public:
    const char *what() const noexcept override{
        if (m_errorDesc.empty() && m_exceptionStream){
            (*m_exceptionStream) << std::endl <<std::string("FILE: ")<<m_file<< std::string(" LINE: ")<<m_line<<std::endl;
            m_errorDesc = m_exceptionStream->str();
        }
        return m_errorDesc.c_str();
    }

    TMException(const std::string &fileName, const int line)
        : m_file(fileName), m_line(line) {
    }

    template<class T>
    TMException &operator<<(const T &arg){
        if (!m_exceptionStream){
            m_exceptionStream.reset(new std::stringstream());
        }
        (*m_exceptionStream) << arg;
        return *this;
    }
};
}
}

#endif // EXCEPTION_H
