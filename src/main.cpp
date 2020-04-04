#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"
#include "twiddle.hpp"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

bool OPTIMIZATION = false;

int main() {
  uWS::Hub h;

  PID pid;
  /**
   * TODO: Initialize the pid variable.
   */
  pid.Init(0.1484559, 0.0001, 0.696846); // best parameters
  //pid.Init(0.0, 0.0, 0.0); // use this in case of Twiddle optimization
  Twiddle twiddle {pid.getGains()};

  h.onMessage([&pid, &twiddle](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          bool twiddle_status = false;
          if (OPTIMIZATION)
          {
              twiddle_status = twiddle.Run(cte);
          }
          pid.UpdateError(cte);
          steer_value = pid.TotalError();
          
          // DEBUG
          //std::cout << "CTE: " << cte << " Steering Value: " << steer_value 
          //          << std::endl;
          
          if (OPTIMIZATION && twiddle_status)
          {
            pid.Init(twiddle.gains_[0],
                    twiddle.gains_[1],
                    twiddle.gains_[2]);

            std::cout << "[TWIDDLE] current solution: Kp " << twiddle.best_solution_[0] <<
                " Ki " << twiddle.best_solution_[1] <<
                " Kd " << twiddle.best_solution_[2] << "\n";
            
            if (twiddle.done)
            {
                OPTIMIZATION = false;
                std::cout << "[TWIDDLE] BEST SOLUTION FOUND: Kp " << twiddle.best_solution_[0] <<
                    " Ki " << twiddle.best_solution_[1] <<
                    " Kd " << twiddle.best_solution_[2] << "\n";
            }

            const std::string msg = "42[\"reset\",{}]";
            ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            return;
          }

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          //std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}
