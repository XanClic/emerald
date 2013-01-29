# coding: utf-8

class String
    def asc
        Helper.asc(self)
    end
end


Memory[0xB8000] = 'y'.asc
Memory[0xB8001] = 15
Memory[0xB8002] = 'a'.asc
Memory[0xB8003] = 15
Memory[0xB8004] = 'y'.asc
Memory[0xB8005] = 15
