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

void application::listen(int port, std::string address) {

    HttpServer server(port,8);
    server.config.address=address;

    server.default_resource["GET"]=[&](std::shared_ptr<HttpServer::Response> res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::get,res,req);
    };

    server.default_resource["POST"]=[&](std::shared_ptr<HttpServer::Response> res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::post,res,req);
    };

    server.default_resource["PUT"]=[&](std::shared_ptr<HttpServer::Response> res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::put,res,req);
    };

    server.default_resource["DELETE"]=[&](std::shared_ptr<HttpServer::Response> res, std::shared_ptr<HttpServer::Request> req) {
        connect_route(http_verb::del,res,req);
    };

    std::thread server_thread([&server](){
        server.start();
    });

    server_thread.join();
}

void application::static_(const boost::filesystem::path rootPath)
{
    namespace fs = boost::filesystem;
    if(!(fs::exists(rootPath) && fs::is_directory(rootPath)))
        return;

    _static_routes.push_back(rootPath);
}

void application::default_(const default_file def) {
        _default_file = def;
}

void application::connect_route(const http_verb verb, std::shared_ptr<HttpServer::Response> res, std::shared_ptr<HttpServer::Request> req) {

    express::response _res(res);
    paramMap pMap;

    std::string in_path(req->path);
    queryMap query;

    //match for queries
    if(verb == http_verb::get) {
        extract_query(in_path, query);
    }

    //matching for regular routes
    for(auto &rt : _routing)
    {
      auto route = rt.first;
      if((_routing[route].find(verb) != _routing[route].end())
         && boost::regex_match(in_path,boost::regex(route)))
      {
          extract_parameters(in_path, route,_routing[route][verb].params,pMap);
          express::request::header_map h(req->header.begin(),req->header.end());
          express::request _req(req,pMap,query,h);
          _routing[route][verb].func(_req,_res);
          return;
      }
    }

    if(!match_file(_res,req->path))
    _res.sendStatus(http_status::http_not_found);
}

void application::extract_query(routePath &clientPath,queryMap &query)
{
    //extracting route parameters
    boost::regex params_regex(regxQuery);
    boost::regex query_remove(regxQueryRemove);
    boost::sregex_iterator next(clientPath.begin(), clientPath.end(), params_regex);
    boost::sregex_iterator end;

    while (next != end) {
        boost::smatch match = *next;
        query.insert(std::make_pair(match.str(2),match.str(3)));
        next++;
    }

    clientPath = boost::regex_replace(clientPath,query_remove,"");
}

bool application::match_file(express::response &_res,std::string path)
{
    //matching for files
     bool match = false;
     std::for_each(_static_routes.begin(),_static_routes.end(),[&](boost::filesystem::path p){

        boost::filesystem::path file(p.string()+path);
        if(!boost::filesystem::is_directory(file) && boost::filesystem::exists(file))
        {
            _res.sendFile(file);
            match = true;
        } else
        {
            boost::filesystem::path d_file(p.string()+path+"/"+_default_file);
            if(boost::filesystem::exists(d_file))
            {
                _res.sendFile(d_file);
                match = true;
            }
        }
    });

    return match;
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
