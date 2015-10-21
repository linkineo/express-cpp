#ifndef EXPRESS_REQUEST_HPP
#define EXPRESS_REQUEST_HPP

#include <router/common_types.hpp>

namespace express {

	class request {
        typedef std::string routePath;

    public:

        typedef std::map<std::string, std::string> header_map;

        request(std::shared_ptr<HttpServer::Request>,paramMap parameters, queryMap queries, header_map &h);

        bool is(std::string type);


        property_readonly<paramMap> params;
        queryMap query;
        header_map headers;
        const routePath route;
        bodyContent& body;

    private:
        std::shared_ptr<HttpServer::Request> _req;

	};

}

#endif
