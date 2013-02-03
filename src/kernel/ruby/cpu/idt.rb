# coding: utf-8
# IDT stuff.

class IDT < XDT
    def load
        X86.lidt(@xdtr)
    end
end


def build_idt
    $idt = IDT.new(256)

    (0..31).each do |exc|
        $idt[exc].type = :sys_np
    end

    (32..47).each do |irq|
        $idt[irq].type = :sys_np
    end

    (48..255).each do |other|
        if other == 0xa2 # syscall
            $idt[other].type = :sys_np
        else
            $idt[other].type = :sys_np
        end
    end

    $idt.load
end
