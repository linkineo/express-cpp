#include <response/response.hpp>

#include <iostream>

using namespace express;

response::response(HttpServer::Response & res) : _res(res){

}

void response::send(htmlContent html) {

    _res << "HTTP/1.1 200 OK\r\nContent-Length: " << html.length() << "\r\n"
        << "Content-Type:text/html;charset=utf-8"
        << "\r\n\r\n" << html;
}

void response::sendStatus(http_status status) {
    _res << "HTTP/1.1 " << (int)status << " " << http_status_text[status] << "\r\n"
    << "Content-Length: " << http_status_text[status].length() << "\r\n"
    << "Content-Type:text/html;charset=utf-8"
    << "\r\n\r\n" << http_status_text[status];

}

void response::sendFile() {

}
