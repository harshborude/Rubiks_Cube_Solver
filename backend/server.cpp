#include "crow.h"
#include <iostream>
#include <vector>
#include <chrono>
#include "Model/RubiksCubeBitboard.cpp"
#include "Solver/IDAstarSolver.h"
#include "Solver/BFSSolver.h"

using namespace std;

// Helper to convert front-end string colors to the C++ Model Enum
RubiksCube::COLOR parseColor(const std::string& colorStr) {
    if (colorStr == "white") return RubiksCube::COLOR::WHITE;
    if (colorStr == "green") return RubiksCube::COLOR::GREEN;
    if (colorStr == "red")   return RubiksCube::COLOR::RED;
    if (colorStr == "blue")  return RubiksCube::COLOR::BLUE;
    if (colorStr == "orange")return RubiksCube::COLOR::ORANGE;
    if (colorStr == "yellow")return RubiksCube::COLOR::YELLOW;
    throw std::runtime_error("Invalid color string: " + colorStr);
}

int main(int argc, char* argv[]) {
    crow::SimpleApp app;

    // We disable logging completely for max performance, but could enable it for debugging
    crow::logger::setLogLevel(crow::LogLevel::Warning);

    std::string dbFile = "Databases/cornerDepth5V1.txt";
    
    // Allow overriding DB path if passed via command line
    if (argc > 1) {
        dbFile = argv[1];
    }

    CROW_ROUTE(app, "/api/solve").methods(crow::HTTPMethod::POST)
    ([&dbFile](const crow::request& req) {
        try {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON body");

            RubiksCubeBitboard cube;

            // The frontend sends an object: { "U": [["w","w","w"], ...], "L": [...], ... }
            std::vector<std::string> faceKeys = {"U", "L", "F", "R", "B", "D"};
            
            for (int f = 0; f < 6; f++) {
                const auto& faceData = body[faceKeys[f]];
                for (int r = 0; r < 3; r++) {
                    const auto& row = faceData[r];
                    for (int c = 0; c < 3; c++) {
                        std::string colorStr = row[c].s();
                        cube.setColor(static_cast<RubiksCube::FACE>(f), r, c, parseColor(colorStr));
                    }
                }
            }

            // Extract the requested solver algorithm
            std::string algorithm = "IDA*";
            if (body.has("algorithm")) {
                algorithm = body["algorithm"].s();
            }

            // Execute the solve and track time
            auto start = chrono::high_resolution_clock::now();
            vector<RubiksCube::MOVE> solve_moves;

            if (algorithm == "IDA*") {
                IDAstarSolver<RubiksCubeBitboard, HashBitboard> solver(cube, dbFile);
                solve_moves = solver.solve();
            } else if (algorithm == "BFS") {
                BFSSolver<RubiksCubeBitboard, HashBitboard> solver(cube);
                solve_moves = solver.solve();
            } else {
                return crow::response(400, "Unsupported algorithm selected.");
            }

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;

            // Prepare JSON Response
            std::vector<std::string> stringMoves;
            for (auto move : solve_moves) {
                stringMoves.push_back(cube.getMove(move));
            }

            crow::json::wvalue jsonResponse;
            jsonResponse["moves"] = stringMoves;
            jsonResponse["timeSeconds"] = duration.count();
            jsonResponse["status"] = "success";

            crow::response res(jsonResponse);

            // Important: Handle CORS so the React Frontend can hit this API
            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");
            return res;

        } catch (const std::exception& e) {
            std::string errStr(e.what());
            crow::json::wvalue failureRes;
            failureRes["status"] = "error";
            failureRes["message"] = errStr;
            return crow::response(500, failureRes);
        }
    });

    // CORS pre-flight handler
    CROW_ROUTE(app, "/api/solve").methods(crow::HTTPMethod::OPTIONS)
    ([]() {
        crow::response res(204);
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.add_header("Access-Control-Max-Age", "86400");
        return res;
    });

    // Use absolute port $PORT provided by Render, or 8080 locally
    const char* portStr = std::getenv("PORT");
    int port = portStr ? std::atoi(portStr) : 8080;

    std::cout << "Starting C++ solver web API on port " << port << "...\n";
    app.port(port).multithreaded().run();

    return 0;
}
