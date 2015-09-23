#include <application/application.hpp>

using namespace express;

#include <boost/regex.hpp>

application::application() {

}

void application::get(const routePath route,const routeHandler rHandler) {

    actions _actions;
    handler _handler;
    _handler.func = rHandler;

    //extracting route parameters
    boost::regex params_regex(":([a-zA-Z\\d]+)");
    boost::sregex_iterator next(route.begin(), route.end(), params_regex);
    boost::sregex_iterator end;
    while (next != end) {
        boost::smatch match = *next;
        //std::cout << match.str(1) << std::endl;
        _handler.params.push_back(match.str(1));
        next++;
    }

    //rewriting route as regular regex
    std::string regex_route = boost::regex_replace(route,params_regex,"([a-zA-Z\\\\d]+)");

    _actions.insert(std::make_pair(http_verb::get,_handler));
    routing.insert(std::make_pair(regex_route,_actions));


}

void application::listen(int port) {

    HttpServer server(port,4);

    server.default_resource["GET"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {

        express::response response(res);
        express::request request(req);
        connect_route(req->path,http_verb::get,request,response);
    };

    server.default_resource["POST"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {

        express::response response(res);
        express::request request(req);
        connect_route(req->path,http_verb::post,request,response);
    };

    server.default_resource["PUT"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {

        express::response response(res);
        express::request request(req);
        connect_route(req->path,http_verb::put,request,response);
    };

    server.default_resource["DELETE"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {

        express::response response(res);
        express::request request(req);
        connect_route(req->path,http_verb::del,request,response);
    };



    std::thread server_thread([&server](){
        server.start();
    });

    server_thread.join();
}

void application::connect_route(const routePath route,const http_verb verb, express::request req, express::response res) {

    std::for_each(routing.begin(),routing.end(),
                  [&](dispatcherMap::value_type &rt){
                      auto _route = rt.first;
                        if((routing[_route].find(verb) != routing[_route].end())
                            && boost::regex_match(req.route(),boost::regex(_route)))
                        {
                            routing[_route][verb].func(req,res);
                            return;
                        }
    });

    res.sendStatus(http_status::http_not_found);
}