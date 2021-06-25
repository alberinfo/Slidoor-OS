[bits 32]
section .uarch
global no_lmode
no_lmode:
    mov dword [0xB8000], 0x0F680F54
    mov dword [0xB8004], 0x0F730F69
    mov dword [0xB8008], 0x0F700F20
    mov dword [0xB800C], 0x0F6F0F72
    mov dword [0xB8010], 0x0F650F63
    mov dword [0xB8014], 0x0F730F73
    mov dword [0xB8018], 0x0F720F6F
    mov dword [0xB801C], 0x0F640F20
    mov dword [0xB8020], 0x0F650F6F
    mov dword [0xB8024], 0x0F200F73
    mov dword [0xB8028], 0x0F6F0F6E
    mov dword [0xB802C], 0x0F200F74
    mov dword [0xB8030], 0x0F750F73
    mov dword [0xB8034], 0x0F700F70
    mov dword [0xB8038], 0x0F720F6F
    mov dword [0xB803C], 0x0F200F74
    mov dword [0xB8040], 0x0F680F74
    mov dword [0xB8044], 0x0F200F65
    mov dword [0xB8048], 0x0F380F78
    mov dword [0xB804C], 0x0F5F0F36
    mov dword [0xB8050], 0x0F340F36
    mov dword [0xB8054], 0x0F610F20
    mov dword [0xB8058], 0x0F630F72
    mov dword [0xB805C], 0x0F690F68
    mov dword [0xB8060], 0x0F650F74
    mov dword [0xB8064], 0x0F740F63
    mov dword [0xB8068], 0x0F720F75
    mov dword [0xB806C], 0x0F2E0F65
    mov dword [0xB8070], 0x0F540F20
    mov dword [0xB8074], 0x0F750F68
    mov dword [0xB8078], 0x0F2C0F73
    mov dword [0xB807C], 0x0F690F20
    mov dword [0xB8080], 0x0F200F74
    mov dword [0xB8084], 0x0F610F63
    mov dword [0xB8088], 0x0F270F6E
    mov dword [0xB808C], 0x0F200F74
    mov dword [0xB8090], 0x0F6F0F62
    mov dword [0xB8094], 0x0F740F6F
    mov dword [0xB8098], 0x0F770F20
    mov dword [0xB809C], 0x0F740F69
    mov dword [0xB80A0], 0x0F200F68
    mov dword [0xB80A4], 0x0F680F74
    mov dword [0xB80A8], 0x0F730F69
    mov dword [0xB80AC], 0x0F4F0F20
    mov dword [0xB80B0], 0x0F2E0F53
    mov dword [0xB80B4], 0x0F530F20
    mov dword [0xB80B8], 0x0F730F79
    mov dword [0xB80BC], 0x0F650F74
    mov dword [0xB80C0], 0x0F200F6D
    mov dword [0xB80C4], 0x0F610F48
    mov dword [0xB80C8], 0x0F740F6C
    mov dword [0xB80CC], 0x0F640F65
    mov word [0xB80D0], 0x0F2E
    cli
    hlt

global no_cpuid
no_cpuid:
    mov dword [0xB8000], 0x0F546869
    mov dword [0xB8004], 0x0F732070
    mov dword [0xB8008], 0x0F726f63
    mov dword [0xB800C], 0x0F657373
    mov dword [0xB8010], 0x0F6f7220
    mov dword [0xB8014], 0x0F646f65
    mov dword [0xB8018], 0x0F73206e
    mov dword [0xB801C], 0x0F6f7420
    mov dword [0xB8020], 0x0F737570
    mov dword [0xB8024], 0x0F706f72
    mov dword [0xB8028], 0x0F742063
    mov dword [0xB802C], 0x0F707569
    mov dword [0xB8030], 0x0F642e20
    mov dword [0xB8034], 0x0F546875
    mov dword [0xB8038], 0x0F732c20
    mov dword [0xB803C], 0x0F697420
    mov dword [0xB8040], 0x0F63616e
    mov dword [0xB8044], 0x0F277420
    mov dword [0xB8048], 0x0F626f6f
    mov dword [0xB804C], 0x0F742077
    mov dword [0xB8050], 0x0F697468
    mov dword [0xB8054], 0x0F207468
    mov dword [0xB8058], 0x0F697320
    mov dword [0xB805C], 0x0F4f532e
    mov dword [0xB8060], 0x0F205379
    mov dword [0xB8064], 0x0F737465
    mov dword [0xB8068], 0x0F6d2048
    mov dword [0xB806C], 0x0F616c74
    mov dword [0xB8070], 0x0F65642e
    cli
    hlt

global no_higher_half
no_higher_half:
    mov dword [0xB8000], 0x0F680F54
    mov dword [0xB8004], 0x0F730F69
    mov dword [0xB8008], 0x0F700F20
    mov dword [0xB800C], 0x0F6F0F72
    mov dword [0xB8010], 0x0F650F63
    mov dword [0xB8014], 0x0F730F73
    mov dword [0xB8018], 0x0F720F6F
    mov dword [0xB801C], 0x0F640F20
    mov dword [0xB8020], 0x0F650F6F
    mov dword [0xB8024], 0x0F200F73
    mov dword [0xB8028], 0x0F6F0F6E
    mov dword [0xB802C], 0x0F200F74
    mov dword [0xB8030], 0x0F610F68
    mov dword [0xB8034], 0x0F650F76
    mov dword [0xB8038], 0x0F650F20
    mov dword [0xB803C], 0x0F6F0F6E
    mov dword [0xB8040], 0x0F670F75
    mov dword [0xB8044], 0x0F200F68
    mov dword [0xB8048], 0x0F690F76
    mov dword [0xB804C], 0x0F740F72
    mov dword [0xB8050], 0x0F610F75
    mov dword [0xB8054], 0x0F200F6C
    mov dword [0xB8058], 0x0F640F61
    mov dword [0xB805C], 0x0F720F64
    mov dword [0xB8060], 0x0F730F65
    mov dword [0xB8064], 0x0F200F73
    mov dword [0xB8068], 0x0F700F73
    mov dword [0xB806C], 0x0F630F61
    mov dword [0xB8070], 0x0F2E0F65
    mov dword [0xB8074], 0x0F540F20
    mov dword [0xB8078], 0x0F750F68
    mov dword [0xB807C], 0x0F2C0F73
    mov dword [0xB8080], 0x0F740F20
    mov dword [0xB8084], 0x0F650F68
    mov dword [0xB8088], 0x0F4F0F20
    mov dword [0xB808C], 0x0F200F53
    mov dword [0xB8090], 0x0F610F63
    mov dword [0xB8094], 0x0F740F6E
    mov dword [0xB8098], 0x0F6A0F20
    mov dword [0xB809C], 0x0F6D0F75
    mov dword [0xB80A0], 0x0F200F70
    mov dword [0xB80A4], 0x0F6F0F74
    mov dword [0xB80A8], 0x0F680F20
    mov dword [0xB80AC], 0x0F670F69
    mov dword [0xB80B0], 0x0F650F68
    mov dword [0xB80B4], 0x0F200F72
    mov dword [0xB80B8], 0x0F610F68
    mov dword [0xB80BC], 0x0F660F6C
    mov dword [0xB80C0], 0x0F200F2E
    mov dword [0xB80C4], 0x0F790F53
    mov dword [0xB80C8], 0x0F740F73
    mov dword [0xB80CC], 0x0F6D0F65
    mov dword [0xB80D0], 0x0F480F20
    mov dword [0xB80D4], 0x0F6C0F61
    mov dword [0xB80D8], 0x0F650F74
    mov dword [0xB80DC], 0x0F2E0F64
    cli
    hlt
