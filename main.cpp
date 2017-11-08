#include <iostream>
#include <sol.hpp>
#include "model/Model.h"
#include "math/Vector4.h"
#include "math/Vector2.h"

int main() {

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.open_libraries(sol::lib::math, sol::lib::math);
    lua.open_libraries(sol::lib::base);


    // Expose C++ classes to lua
   lua.new_usertype<Vector2>("Vector2", "x", &Vector2::x, "y", &Vector2::y

    );

    lua.new_usertype<Vector3>("Vector3", "x", &Vector3::x, "y", &Vector3::y, "z", &Vector3::z,
                              "normalize", &Vector3::normalize, "length", &Vector3::length
    );

    lua.new_usertype<Vector4>("Vector4", "x", &Vector4::x, "y", &Vector4::y, "z", &Vector4::z, "w", &Vector4::w,
                              "normalize", &Vector4::normalize, "length", &Vector4::length,
                              "xyz", &Vector4::xyz, "is_point", &Vector4::isPoint, "is_vector", &Vector4::isVector
    );


    lua.new_usertype<Model>("Model", "positions", &Model::positions, "indices", &Model::indices, "set_positions",
                            &Model::set_positions, "set_indices", &Model::set_indices);


    lua.script_file("./scripts/setup.lua");
    lua.script_file("./scripts/main.lua");
    lua.script_file("./scripts/test_shaders.lua");

    lua["state"]["init"](lua["state"]);


    Model &m = lua["state"]["model"];
    std::cout << m.get_positions().size() << std::endl;


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