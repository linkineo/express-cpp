#ifndef EXPRESS_COMMON_TYPES_HPP
#define EXPRESS_COMMON_TYPES_HPP

#include <functional>
#include <string>
#include <map>
#include <server_http.hpp>
#include <vector>

#include <iostream>
#include <map>
#include <type_traits>
#include <boost/filesystem.hpp>

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

namespace express {


    typedef std::string routePath;
    typedef std::string htmlContent;
    typedef std::string regx_param;
    typedef std::vector<std::string> regx_params;
    typedef std::map<regx_param,std::string> paramMap;
    typedef std::map<std::string,std::string> queryMap;
    typedef SimpleWeb::Server<SimpleWeb::HTTP>::Content bodyContent;

    const std::string regxParam(":([-[:word:]]+)");
    const std::string regxURI("([-[:word:]]+)");
    const std::string regxQuery("(\\?|\\&)([^=]+)\\=([^&]+)");
    const std::string regxQueryRemove("(\\?[^.]*)");
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
            {http_status::http_not_found, "FILE NOT FOUND"},
            {http_status::http_internal_server_error, "INTERNAL SERVER ERROR"}
    };

    static std::map<std::string,std::string> content_types{
            {".jpg","image/jpg"},
            {".jpeg","image/jpeg"},
            {".png","image/png"},
            {".html","text/html"},
            {".htm","text/html"},
            {".json","text/json"},
            {".xml","text/xml"},
            {".txt","text/txt"},
            {".css","text/css"},
            {".js","application/javascript"}
    };
};


template <typename T > class property_readonly {
    const T value;
public:

    property_readonly(const T& value) : value(value) {}

    operator const T& () const {
        return value;
    }

    const T& operator*() const {
        return value;
    }

    const T* operator->() const {
        return std::addressof(value);
    }

    const typename T::mapped_type  operator[] (typename T::key_type
                                               key) const {
        return value.at(key);
    }
};



#endif //EXPRESS_CPP_COMMON_TYPES_HPP
