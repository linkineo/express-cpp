#include <request/request.hpp>

#include <iostream>

using namespace express;

request::request(std::shared_ptr<HttpServer::Request> req) : requ(req),route_path(req->path) {

}

routePath request::route() {
    return route_path;
}
