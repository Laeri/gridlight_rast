--
-- Created by IntelliJ IDEA.
-- User: hexaquat
-- Date: 08/11/17
-- Time: 17:39
-- To change this template use File | Settings | File Templates.
--


vertex_shader = {
    position,
    normal,
    color,
    model_view,
    projection,
    gl_position,
    main = function(self)
        print("run vertex shader");
        self.gl_position = self.projection * self.model_view * self.position;
        self.color =  111;
    end

}

fragment_shader = {
    normal,
    color,
    frag_color,
    main = function(self)
        print("run fragment_shader");
        self.frag_color = self.color;
    end

}