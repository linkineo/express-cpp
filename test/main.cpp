#include <iostream>
#include <application/application.hpp>
#include <client_http.hpp>

typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main(int argc, char ** argv)
{
	express::application app;

    app.get("/hello",[](express::request req, express::response res) {
      res.send("World !");
    });

    app.get("/hello/:world",[](express::request req,express::response res) {
        res.send("World="+ req.params["world"]);
    });

    app.get("/hello/:id/age/:age",[](express::request req, express::response res) {
        res.send("Hello " + req.params["id"] + " ! You are " + req.params["age"] + " years old !");
    });

    app.post("/dali/lamp",[](express::request req, express::response res) {
        res.send("GOT IT POSTED ! - GOT:" + req.body.string());
    });

    app.listen(8080);

  return 0;
}
