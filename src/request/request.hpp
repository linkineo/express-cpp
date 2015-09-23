#ifndef EXPRESS_REQUEST_HPP
#define EXPRESS_REQUEST_HPP

#include <router/common_types.hpp>

namespace express {

	class request {
        typedef std::string routePath;

    public:
        request(std::shared_ptr<HttpServer::Request>,const paramMap);

        paramMap params();
        routePath route();

    private:
        std::shared_ptr<HttpServer::Request> _req;
        routePath _route_path;
        paramMap _param_map;
	};

}

#endif
