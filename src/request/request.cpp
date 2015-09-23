#include <request/request.hpp>

#include <iostream>

using namespace express;

request::request(std::shared_ptr<HttpServer::Request> req,const paramMap parameters) :
        _req(req),_param_map(parameters),_route_path(req->path) {
}

paramMap request::params() {
    return _param_map;
}

routePath request::route() {
    return _route_path;
}
