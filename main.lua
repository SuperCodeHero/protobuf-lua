package.cpath = package.cpath..";./out/lib?.so;./lib?.so"
local api = require "api"

local handle = {}
handle[0] = function(p, pend)
    local v
    p, v = api.readVarInt(p, pend)
    return p, v
end

handle[2] = function(p, pend)
    local v
    p, v = api.readLengthDelimited(p, pend)
    return p, v
end

local message_base = {}

message_base.parseFromArray = function(self, p, pend)
    self:parse(p, pend)
end

local message_meta = {
    __index = function(self, key)
        return rawget(message_base, key)
    end
}

local inner = {}
inner.parse = function(self, p, pend)
    local ok, tag, wire_type

    p, ok, tag, wire_type = api.readKey(p, pend)
    while ok == true do
        local f = handle[wire_type]
        local v
        if tag == 1 then

            p, v = f(p, pend)
            self.v1 = v

        elseif tag == 2 then

            p, v = f(p, pend)
            self.v2 = v

        end
        print("inner", tag, wire_type, v)
        p, ok, tag, wire_type = api.readKey(p, pend)
    end
end


local proto1 = {}
proto1.parse = function(self, p, pend)

    local ok, tag, wire_type

    p, ok, tag, wire_type = api.readKey(p, pend)
    while ok == true do
        local f = handle[wire_type]
        local v
        if tag == 1 then

            p, v = f(p, pend)
            self.id = v

        elseif tag == 2 then

            p, v = f(p, pend)
            table.insert(self.list, v)

        elseif tag == 3 then

            p, v = f(p, pend)
            self.name = v

        elseif tag == 4 then

            p, v = f(p, pend)
            print(v)
            local sub_p, sub_end = api.tMalloc(v)
            inner:parse(sub_p, sub_end)
            self.inner = inner
        end
        print(tag, wire_type, v)
        p, ok, tag, wire_type = api.readKey(p, pend)
    end
end

local hexstr = "08E707100110641A07676D6F69656A74220A089A051205736F696668"
local srcstr = api.hexStrToSrc(hexstr)
local p, pend = api.tMalloc(srcstr)
proto1.list = {}
proto1:parse(p, pend)