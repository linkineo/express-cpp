#include <application/application.hpp>
#include <boost/regex.hpp>

using namespace express;

application::application() {

}

void application::get(const routePath route,const routeHandler rHandler) {

    register_route(http_verb::get,route,rHandler);
}

void application::post(const routePath route,const routeHandler rHandler) {

    register_route(http_verb::post,route,rHandler);
}

void application::put(const routePath route,const routeHandler rHandler) {

    register_route(http_verb::put,route,rHandler);
}

void application::del(const routePath route,const routeHandler rHandler) {

    register_route(http_verb::del,route,rHandler);
}

void application::register_route(const http_verb verb,const routePath route,const routeHandler rHandler) {

    actions _actions;
    handler _handler;
    _handler.func = rHandler;

    //extracting route parameters
    boost::regex params_regex(regxParam);
    boost::sregex_iterator next(route.begin(), route.end(), params_regex);
    boost::sregex_iterator end;
    //first element is for complete path
    _handler.params.push_back("path");
    while (next != end) {
        boost::smatch match = *next;
        _handler.params.push_back(match.str(1));
        next++;
    }

    //handling trailing edge

    //rewriting route as regular regex
    std::string regex_route = boost::regex_replace(route,params_regex,regxURI);

    _actions.insert(std::make_pair(verb,_handler));
    _routing.insert(std::make_pair(regex_route,_actions));

}

void application::listen(int port) {

    HttpServer server(port,4);

    server.default_resource["GET"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::get,res,req);
    };

    server.default_resource["POST"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::post,res,req);
    };

    server.default_resource["PUT"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::put,res,req);
    };

    server.default_resource["DELETE"]=[&](HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::del,res,req);
    };

    std::thread server_thread([&server](){
        server.start();
    });

    server_thread.join();
}

void application::static_routes(const boost::filesystem::path rootPath)
{
    namespace fs = boost::filesystem;
    if(!(fs::exists(rootPath) && fs::is_directory(rootPath)))
        return;

    std::string path(rootPath.string());

    fs::recursive_directory_iterator end;
    for(fs::recursive_directory_iterator fileList(rootPath) ; fileList != end; fileList++)
    {
        if(fs::is_regular_file(fileList->path()) && content_types.find(fileList->path().extension().string()) != content_types.end())
        {
            std::string full(fileList->path().string());
            if(full.length() > path.length())
            {
                full = full.replace(0,path.length(),"");
                fs::path p = fileList->path();
                get(full,[p](express::request req, express::response res){
                    res.sendFile(p); });
            }
        }
    }
}

void application::connect_route(const http_verb verb, HttpServer::Response& res, std::shared_ptr<HttpServer::Request> req) {

    express::response _res(res);
    paramMap pMap;
    std::for_each(_routing.begin(),_routing.end(),
                  [&](dispatcherMap::value_type &rt){
                      auto route = rt.first;
                        if((_routing[route].find(verb) != _routing[route].end())
                            && boost::regex_match(req->path,boost::regex(route)))
                        {
                            extract_parameters(req->path, route,_routing[route][verb].params,pMap);
                            express::request _req(req,pMap);
                            _routing[route][verb].func(_req,_res);
                            return;
                        }
    });

    _res.sendStatus(http_status::http_not_found);
}

void application::extract_parameters(const routePath clientPath,const routePath serverRegx,regx_params &regParamList,paramMap& pMap) {
    boost::regex regx(serverRegx);
    boost::smatch match;

    boost::regex_search(clientPath, match, regx);
    if (regParamList.size() == match.size()) {
        for (size_t i = 0; i < match.size(); ++i) {
            pMap.insert(std::make_pair(regParamList[i], match[i]));
        }
    }

}
