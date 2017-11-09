#include <iostream>
#include <sol.hpp>
#include "model/Model.h"
#include "math/Vector4.h"
#include "math/Vector2.h"
#include "math/Matrix4.h"
#include "math/Matrix3.h"
#include "renderer/Renderer.h"

int main() {

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.open_libraries(sol::lib::math, sol::lib::math);
    lua.open_libraries(sol::lib::base);


    // Expose C++ classes to lua
    lua.new_usertype<Vector2>("Vector2", "x", &Vector2::x, "y", &Vector2::y, sol::meta_function::addition,
                              &Vector2::operator+, sol::meta_function::subtraction, &Vector2::operator-,
                              "scale", &Vector2::scale

    );

    lua.new_usertype<Vector3>("Vector3", "x", &Vector3::x, "y", &Vector3::y, "z", &Vector3::z,
                              "normalize", &Vector3::normalize, "length", &Vector3::length, "dot", &Vector3::dot,
                              sol::meta_function::addition, &Vector3::operator+, sol::meta_function::subtraction,
                              &Vector3::operator-, "to_str", &Vector3::to_str, sol::meta_function::index,
                              &Vector3::operator[], sol::meta_function::multiplication,
                              sol::overload(sol::resolve<Vector3(const Vector3 &)>(&Vector3::operator*),
                                            sol::resolve<Vector3(const double &)>(&Vector3::operator*),
                                            sol::resolve<Vector3(const double &, const Vector3 &)>(&operator*))
    );

    lua.new_usertype<Vector4>("Vector4", "x", &Vector4::x, "y", &Vector4::y, "z", &Vector4::z, "w", &Vector4::w,
                              "normalize", &Vector4::normalize, "length", &Vector4::length, "dot", &Vector4::dot,
                              "xyz", &Vector4::xyz, "is_point", &Vector4::isPoint, "is_vector", &Vector4::isVector,

                              sol::meta_function::addition, &Vector4::operator+, sol::meta_function::subtraction,
                              &Vector4::operator-, sol::meta_function::index, &Vector4::operator[]
    );

    lua.new_usertype<Matrix3>("Matrix3", "invert", &Matrix3::invert, "transform", &Matrix3::transform, "det",
                              &Matrix3::det, sol::meta_function::addition, &Matrix3::operator+,
                              sol::meta_function::subtraction, &Matrix3::operator-);

    lua.new_usertype<Matrix4>("Matrix4", "invert", &Matrix4::invert, "det", &Matrix4::det, "rot_x", &Matrix4::rot_x,
                              "rot_y", &Matrix4::rot_y, "rot_z", &Matrix4::rot_z, "transpose",
                              &Matrix4::transpose, "set_scale", &Matrix4::set_scale, "set_identity",
                              &Matrix4::set_identity, "transform",
                              sol::overload(sol::resolve<void(Vector3 &)>(&Matrix4::transform),
                                            sol::resolve<void(Vector4 &)>(
                                                    &Matrix4::transform)),
                              sol::meta_function::addition, &Matrix4::operator+, sol::meta_function::subtraction,
                              &Matrix4::operator-, sol::meta_function::index, &Matrix4::operator[]
    );


    lua.new_usertype<Model>("Model", "positions", &Model::positions, "indices", &Model::indices, "set_positions",
                            &Model::set_positions, "set_indices", &Model::set_indices);

    lua.new_usertype<Renderer>("Renderer", "draw", &Renderer::draw);

    lua.script_file("./scripts/setup.lua");
    lua.script_file("./scripts/main.lua");
    lua.script_file("./scripts/test_shaders.lua");

    lua["state"]["init"](lua["state"]);

    Renderer renderer = Renderer(&lua);
    lua["renderer"] = renderer;
    renderer.init();
    renderer.run();


    return 0;
}