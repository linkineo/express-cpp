#include <response/response.hpp>

#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file.hpp>


using namespace express;

response::response(std::shared_ptr<HttpServer::Response> res) : _res(res){

}

void response::append(std::string header_name,std::string header_content)
{
    if(_header_append.empty())
    _header_append += "\r\n";

    _header_append += header_name + ": " + header_content + "\r\n";
}

void response::send(htmlContent html) {

    *_res << "HTTP/1.1 200 OK\r\nContent-Length: " << html.length() << "\r\n"
        << "Content-Type:text/html;charset=utf-8" << _header_append
        << "\r\n\r\n" << html;
}

void response::sendStatus(http_status status) {
    *_res << "HTTP/1.1 " << (int)status << " " << http_status_text[status] << "\r\n"
    << "Content-Length: " << http_status_text[status].length() << "\r\n"
    << "Content-Type:text/html;charset=utf-8" << _header_append
    << "\r\n\r\n" << http_status_text[status];

}

void response::sendFile(const boost::filesystem::path file) {
    
    auto filesize = boost::filesystem::file_size(file);
    std::ifstream fileS(file.string());
    std::vector<char> vec(filesize);
    fileS.read(vec.data(),filesize);   
    fileS.close();

    *_res << "HTTP/1.1 200 OK\r\nContent-Length: " << filesize << "\r\nContent-Type:" << content_types[file.extension().string()] << _header_append << "\r\n\r\n";
    _res->write(vec.data(), filesize);
    _res->flush();

}
