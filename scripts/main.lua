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
end

function main_state:update(delta)
    print("main_update","");
end

function main_state:close()
    print("main_close");
end
