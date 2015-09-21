#include <application/application.hpp>

using namespace express;


application::application() {

}

void application::get(const routePath route,const routeHandler rHandler) {

    routeHandle h = {rHandler,http_verb::get};
    routing.insert(std::make_pair(route,h));

}

void application::listen(int port) {

    HttpServer server(port,4);

    server.default_resource["GET"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {

        express::response response(res);
        express::request request;
        routing[req->path].rH(request,response);
    };

    std::thread server_thread([&server](){
        server.start();
    });

    server_thread.join();

}