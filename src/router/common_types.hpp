#ifndef EXPRESS_COMMON_TYPES_HPP
#define EXPRESS_COMMON_TYPES_HPP

#include <functional>
#include <string>
#include <map>
#include <server_http.hpp>
#include <vector>


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

    enum class http_status {
        http_ok = 200,
        http_forbidden = 403,
        http_not_found = 404,
        http_internal_server_error = 500
    };

    static std::map<http_status,std::string> http_status_text = {
            {http_status::http_ok, "OK"},
            {http_status::http_forbidden, "FORBIDDEN"},
            {http_status::http_not_found, "FILE NOT FOUND"},
            {http_status::http_internal_server_error, "INTERNAL SERVER ERROR"}
    };

}


#endif //EXPRESS_CPP_COMMON_TYPES_HPP
