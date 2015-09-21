#include <response/response.hpp>

#include <iostream>

using namespace express;

response::response(HttpServer::Response & resp) : res(&resp){

}

void response::send(htmlContent html) {

    *res << "HTTP/1.1 200 OK\r\nContent-Length: " << html.length() << "\r\n\r\n" << html;
}
