#include <request/request.hpp>

#include <iostream>

using namespace express;

request::request(std::shared_ptr<HttpServer::Request> req,paramMap parameters) :
        _req(req),params(parameters),route(req->path),body(req->content) {
}

