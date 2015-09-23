#ifndef EXPRESS_RESPONSE_HPP
#define EXPRESS_RESPONSE_HPP

#include <router/common_types.hpp>

namespace express {

	class response {

    public:
		response(HttpServer::Response &resp);

        //set content type to HTML
        void send(htmlContent html);
        //void send(JSON) -- array or JSON ?
        //void send (Buffer) -- octet stream

        void sendStatus(http_status status);
        void sendFile();

    private:
        HttpServer::Response& res;
	};

}
#endif
