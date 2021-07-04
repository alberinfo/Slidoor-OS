Slidoor-OS
------------------------------------------------
Slidoor OS is a hobbyist operating system made completely from scratch.
it features:
- [x] Basic ACPI Driver
- [x] ATA/ATAPI PIO Driver
- [x] ATA/ATAPI DMA Driver
- [x] HPET Driver && PIT Driver (the latter is for fallback)
- [x] PCI Bus scanning and parsing
- [x] PCIe scanning
- [x] VBE Framebuffer Driver
- [x] VGA Framebuffer Driver (very likely to get removed)
- [x] Font parser and renderer
- [x] Graphical console
- [x] Support for SSEx, AVX, AVX2, AVX512

TODO:
- [ ] TSC Driver
- [ ] Parsing other ACPI tables (i.e BGRT... sure.), objects and/or methods (i.e _TTS, _PTS, _GTS), etc. --> Implement an aml interpreter*
- [ ] MSI(x)
- [ ] Suspend to ram, to disk, etc.
- [ ] AHCI Driver
- [ ] NVMe Driver
- [ ] USB Driver (OHCI, UHCI, EHCI and XHCI)
- [ ] Actually implement SMP Support
- [ ] Implement a filesystem
- [ ] Implement VFS
- [ ] Fix atapi irq never firing.
- [ ] Implement userspace
- [ ] Implement networking

- Notes:
	- The TODO list is not ordered.

If you wish to contact me add me in discord, my username is "alberinfo_osdev"

*This by now has my highest priority. Though, seems like a long update, and if done it will be one of the most (if not the most) important update ever done on my os. Also, i wont be porting ACPICA (seems kind of like a mess to me), but instead will try writing an interpreter for myself (while lying an eye on LAI, seems pretty clean)

**Updates on the AML Interpreter: As of now, the parser has been done in a good portion, with the only remaining things being:
	- Methods
	- Packets inside packets, etc
Then, i should start seeing into ways of executing the AML Code. This will also take some time to do, and a lot of planning.

**Seems like qemu hates me huh? i havent uploaded anything in a week or so, because qemu threw #GPF when storing an AcpiNamespaceBlock. Solved it by changing how i save childs. Now i have a #GPF when i try to look for the info of the first ata drive. In both cases, not freeing memory "solves" (aka bypasses) the problem.