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

    positions = {}
    indices = {}

    p1 = Vector3.new();
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;
    p2 = Vector3.new();
    p2.x = 3;
    p2.y = 0;
    p2.z = 0;
    p3 = Vector3.new();
    p3.x = 3;
    p3.y = 3;
    p3.z = 0;
    positions[1] = p1;
    positions[2] = p2;
    positions[3] = p3;
    indices = {}
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    self.model.positions[1] = p1;
    self.model.positions[2] = p2;
    self.model.positions[3] = p3;
    self.model.indices[1] = 1;
    self.model.indices[2] = 2;
    self.model.indices[3] = 3;
    --self.model:set_positions(positions);
    --self.model:set_indices(indices);
end

function main_state:update(delta)
    print("main_update","");
end

function main_state:close()
    print("main_close");
end
