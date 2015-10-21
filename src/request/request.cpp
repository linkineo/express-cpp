#include <request/request.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>

using namespace express;

request::request(std::shared_ptr<HttpServer::Request> req,paramMap parameters, queryMap queries,header_map &h) :
        _req(req),params(parameters),query(queries),route(req->path),body(req->content),headers(h) {
}


bool request::is(std::string type){

    std::string content_type = headers["Accept"];
    boost::algorithm::to_lower(content_type);
    boost::algorithm::to_lower(type);

    if(content_type.find(type) != std::string::npos)
    {
        return true;
    } else{
        return false;
    }
}