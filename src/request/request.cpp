#include <request/request.hpp>

#include <iostream>

using namespace express;

request::request(std::shared_ptr<HttpServer::Request> req,paramMap parameters, queryMap queries,header_map &h) :
        _req(req),params(parameters),query(queries),route(req->path),body(req->content),headers(h) {
}

