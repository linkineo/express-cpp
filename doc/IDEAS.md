
## Sending JSON
```
template <class T>
void send_json(T obj) {
  jsonize(obj);
}

send_json(mon_objet);
```

## Routing over JSON Params

REST API : PUT /engine/status/:id

engine - start : 
================
/engine/status/1
{ "status" : "run", "speed" : 5}

engine - stop : 
================
/engine/status/1
{ "status" : "stop",}

```cpp

struct start_status {
  std::string status;
  int speed;
};

struct stop_status {
  std::string status;
};

boost::variant<start_status, stop_status> possible_status;


int main(int argc, char** argv) {

  struct controller {
    operator()(start_status s) {
      starting-over-smi;
    }

    operator()(stop_status s) {
      stopping-over-smi;
    }
  };

  app.put("/engine/status/:id", controller{});

  app.put("/engine/status/:id", {
    [](start_status s ) {
      starting-over-smi;
    },
    [](stop_status s) {
      starting-over-smi
    }	
  });

  
   app.put("/engine/status/:id", [](possible_status param){

      if (param is start_status) {
	starting-over-smi;
      } else if (param is stop_status) {
	stopping-over-smi;
      }
   });

```

## Auto argument parsing from JSON

```cpp
   app.put("/engine/start/:id/:status", [](int id, Status possible_status){
     std::cout << "Doing something for motor " << id << " with speed : " << speed << std::endl;
   });
}
```
