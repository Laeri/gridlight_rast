#include <iostream>
#include <sol.hpp>

int main() {

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.open_libraries(sol::lib::math, sol::lib::math);
    lua.open_libraries(sol::lib::base);
    lua.script_file("./scripts/setup.lua");
    lua.script_file("./scripts/main.lua");
    lua.script_file("./scripts/test_shaders.lua");

    lua["state"]["init"](lua["state"]);


    // test values until matrices are set
    lua["vertex_shader"]["position"] = 10;
    lua["vertex_shader"]["projection"] = lua["state"]["projection"];
    lua["vertex_shader"]["model_view"] = lua["state"]["model_view"];
    // lua["vertex_shader"]["main"](lua["vertex_shader"]);

    lua["fragment_shader"]["color"] = lua["vertex_shader"]["color"];
    //  lua["fragment_shader"]["main"](lua["fragment_shader"]);
    bool running = true;
    float delta = 0;
    while (delta < 10) {
        delta += 1;
        // check input
        lua["state"]["render"](lua["state"], delta, delta);
        lua.script_file("./scripts/run_shaders.lua");
    }

    lua["state"]["close"](lua["state"]);

    return 0;
}