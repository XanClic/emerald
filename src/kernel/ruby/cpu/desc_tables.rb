# coding: utf-8
# [GIL] descriptor tables.

class XDT
    def initialize(descs)
        @desc_count = descs
        @base       = malloc(descs * 8)


        xdtr_struct = RStruct.new({ limit: [0, :u16], base: [2, :u32] })

        @xdtr = malloc(xdtr_struct.size)

        xdtr_instance = xdtr_struct.instance(@xdtr)

        xdtr_instance.limit = descs * 8 - 1
        xdtr_instance.base  = @base
    end


    def [](i)
        return XDTDesc.get(@base, i)
    end
end
