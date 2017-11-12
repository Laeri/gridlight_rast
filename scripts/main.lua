--
-- Created by IntelliJ IDEA.
-- User: hexaquat
-- Date: 08/11/17
-- Time: 17:36
-- To change this template use File | Settings | File Templates.
--



main_state = State:new();
state = main_state;

function main_state:init()
    print("main_init");
    self.projection = 2;
    self.model_view = 1;
    self.model = Model.new();
    c1 = Vector4.new(1,0,0,0);
    c2 = Vector4.new(0,1,0,0);
    c3 = Vector4.new(0,0,1,0);
    p1 = Vertex.new(0,-1,0);
    p1:set_member("color", c1);
    p2 = Vertex.new(3,-1,0);
    p2:set_member("color", c2);
    p3 = Vertex.new(3,3,0);
    p3:set_member("color", c3);
    self.model.vertices[1] = p1;
    self.model.vertices[2] = p2;
    self.model.vertices[3] = p3;
    self.model.indices[1] = 0;
    self.model.indices[2] = 1;
    self.model.indices[3] = 2;
end

function main_state:update(renderer,delta)
    print("main_update","");
    rot = Matrix4.new();
    rot:set_identity();
    rot:rot_x(delta*5);
    rot = rot * self.model.model_matrix;
    self.model.model_matrix:set(rot);
    renderer:set_uniform("projection", renderer:get_frustum():get_projection());
    renderer:set_uniform("view", renderer:get_camera():world_to_camera());
    renderer:set_uniform("model_matrix", self.model.model_matrix);
    renderer:draw(self.model);
end

function main_state:close()
    print("main_close");
end
