#ifndef EXPRESS_REQUEST_HPP
#define EXPRESS_REQUEST_HPP

#include <router/common_types.hpp>

namespace express {

	class request {
        typedef std::string routePath;

    public:
        request(std::shared_ptr<HttpServer::Request>,paramMap parameters, queryMap queries);


        property_readonly<paramMap> params;
        queryMap query;
        const routePath route;
        bodyContent& body;

    private:
        std::shared_ptr<HttpServer::Request> _req;
	};

}

#endif
