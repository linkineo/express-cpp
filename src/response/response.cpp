#include <response/response.hpp>

#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file.hpp>


using namespace express;

response::response(HttpServer::Response & res) : _res(res){

}

void response::append(std::string header_name,std::string header_content)
{
    if(_header_append.empty())
    _header_append += "\r\n";

    _header_append += header_name + ": " + header_content + "\r\n";
}

void response::send(htmlContent html) {

    _res << "HTTP/1.1 200 OK\r\nContent-Length: " << html.length() << "\r\n"
        << "Content-Type:text/html;charset=utf-8" << _header_append
        << "\r\n\r\n" << html;
}

void response::sendStatus(http_status status) {
    _res << "HTTP/1.1 " << (int)status << " " << http_status_text[status] << "\r\n"
    << "Content-Length: " << http_status_text[status].length() << "\r\n"
    << "Content-Type:text/html;charset=utf-8" << _header_append
    << "\r\n\r\n" << http_status_text[status];

}

void response::sendFile(const boost::filesystem::path file) {

    std::ostringstream out;
    std::ifstream fileS(file.string());
    out << fileS.rdbuf();
    std::string str(out.str());
    const char * raw = str.c_str();

    _res << "HTTP/1.1 200 OK\r\nContent-Length: " << str.length() << "\r\nContent-Type:" << content_types[file.extension().string()] << _header_append << "\r\n\r\n";
    _res.write(raw, str.length());
    _res.flush();

}
