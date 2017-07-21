#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <memory>
#include <string>
#include <sstream>
#include <string>
#include <execinfo.h>
#include <cxxabi.h>


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
        (*m_exceptionStream) << print_stacktrace() <<std::endl<<arg;
        return *this;
    }
private:
    static inline std::string print_stacktrace(unsigned int max_frames = 63) {
        std::stringstream out;
        out << "STACK TRACE:\n";
        void* addrlist[max_frames+1];
        int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

        if (addrlen == 0) {
            out<<"  <empty, possibly corrupt>\n";
            return "";
        }

        char** symbollist = backtrace_symbols(addrlist, addrlen);

        size_t funcnamesize = 256;
        char* funcname = new char [funcnamesize];

        for (int i = 1; i < addrlen; i++) {
            char *begin_name = 0;
            char *begin_offset = 0;
            char *end_offset = 0;

            for (char *p = symbollist[i]; *p; ++p) {
                if (*p == '(') begin_name = p;
                else
                    if (*p == '+') begin_offset = p;
                    else
                        if (*p == ')' && begin_offset) {
                            end_offset = p;
                            break;
                        }
            }

            if (begin_name && begin_offset && end_offset
                && begin_name < begin_offset) {
                *begin_name++ = '\0';
                *begin_offset++ = '\0';
                *end_offset = '\0';

                int status;
                char* ret = abi::__cxa_demangle(begin_name,
                                funcname, &funcnamesize, &status);
                if (status == 0) {
                    funcname = ret;
                    out << "  "<<symbollist[i]<<": "<< funcname<<" + "<< begin_offset<<std::endl;
                } else {
                    out << "  "<<symbollist[i]<<": "<< begin_name<<" + "<< begin_offset<<std::endl;
                }
            } else {
                 out << "  "<<symbollist[i]<<std::endl;
            }
        }

        delete[] funcname;
        free(symbollist);
        return out.str();
    }


};
}
}

#endif // EXCEPTION_H
