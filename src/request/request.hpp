#ifndef EXPRESS_REQUEST_HPP
#define EXPRESS_REQUEST_HPP

#include <router/common_types.hpp>

namespace express {

	class request {
        typedef std::string routePath;

    public:
        request(std::shared_ptr<HttpServer::Request> req);

        routePath route();

    private:
        std::shared_ptr<HttpServer::Request> requ;
        routePath route_path;
	};

}

#endif
