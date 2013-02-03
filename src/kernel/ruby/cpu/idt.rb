# coding: utf-8
# IDT stuff.

class IDT < XDT
    def load
        X86.lidt(@xdtr)
    end


    def self.init
        $idt = IDT.new(256)


        (0..19).each do |exc|
            $idt[exc].type     = :sys_intr
            $idt[exc].base     = X86.intr_handler_addr(exc)
            $idt[exc].selector = SLC_SYS_CODE
        end

        (32..47).each do |irq|
            $idt[irq].type     = :sys_intr
            $idt[irq].base     = X86.intr_handler_addr(irq)
            $idt[irq].selector = SLC_SYS_CODE
        end

        $idt[0xa2].type     = :sys_trap
        $idt[0xa2].base     = X86.intr_handler_addr(0xa2)
        $idt[0xa2].selector = SLC_SYS_CODE


        $idt.load()
    end
end
