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


    def self.spurious?(vector)
        return false unless (vector & 7) == 7
        return false unless (PIO8[(vector >= 8) ? 0xa0 : 0x20] & 0x80) == 0

        if vector >= 8
            # Send EOI to master upon spurious interrupt on slave
            eoi(2)
        end

        return true
    end


    def self.eoi(vector)
        PIO8[0xa0] = 0x20 if vector >= 8
        PIO8[0x20] = 0x20
    end
end
