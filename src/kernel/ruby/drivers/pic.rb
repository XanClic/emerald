# coding: utf-8
# PIC “driver”

module PIC
    def self.single_init(iobase, irq0, icw3)
        PIO8[iobase    ] = 0x11 # ICW1
        PIO8[iobase + 1] = irq0 # ICW2
        PIO8[iobase + 1] = icw3 # ICW3
        PIO8[iobase + 1] = 0x01 # ICW4

        PIO8[iobase + 1] = 0x00 # OCW1
        PIO8[iobase    ] = 0x0B # OCW3
    end


    def self.init
        single_init(0x20, 0x20, 1 << 2) # master
        single_init(0xa0, 0x28,      2) # slave
    end
end
