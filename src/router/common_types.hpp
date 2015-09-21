#ifndef EXPRESS_COMMON_TYPES_HPP
#define EXPRESS_COMMON_TYPES_HPP

#include <functional>
#include <string>
#include <map>
#include <server_http.hpp>


typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

namespace express {

    typedef std::string routePath;
    typedef std::string htmlContent;

    enum class http_verb {
        del,
        get,
        put,
        post
    };

}


#endif //EXPRESS_CPP_COMMON_TYPES_HPP
