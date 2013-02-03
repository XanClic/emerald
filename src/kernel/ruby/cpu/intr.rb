# coding: utf-8
# Top-level interrupt handler.

CPU_STATE = RStruct.new({
    ebp: [ 0, :u32],
    edi: [ 4, :u32],
    esi: [ 8, :u32],
    edx: [12, :u32],
    ecx: [16, :u32],
    ebx: [20, :u32],
    eax: [24, :u32],
     es: [28, :u16],
     ds: [32, :u16],
    vector:   [36, :u8],
    err_code: [40, :u32],
    eip: [44, :u32],
     cs: [48, :u16],
    eflags:   [52, :u32],
    esp: [56, :u32],
     ss: [60, :u16]
})


def interrupt(stateptr)
    state = CPU_STATE.instance(stateptr)

    intr_no = state.vector

    case intr_no
    when 0..19
        exception(state)

    when 0x20..0x2f
        return stateptr if PIC.spurious?(intr_no)

        PIC.eoi(intr_no)

    when 0xa2
        raise '(syscall not yet implemented)'
    end

    return stateptr
end


def exception(state)
    raise 'External exception %i (error code 0x%08x)

eax=0x%08x   ebx=0x%08x   ecx=0x%08x   edx=0x%08x
esi=0x%08x   edi=0x%08x   ebp=0x%08x   esp=0x%08x
eip=0x%08x   efl=0x%08x   cr2=0x%08x   cr3=0x%08x
 cs=0x%08x    ds=0x%08x    es=0x%08x    ss=0x%08x' % [
        state.vector, state.err_code,
        state.eax, state.ebx, state.ecx, state.edx,
        state.esi, state.edi, state.ebp, state.esp,
        state.eip, state.eflags, X86.cr2, X86.cr3,
        state.cs, state.ds, state.es, state.ss
    ]
end
