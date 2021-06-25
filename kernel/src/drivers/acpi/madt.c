#include "madt.h"

void acpiParseMadt(uint32 *ptr)
{
    acpi_pm_info->madt = ((uint32)(struct MADT*)*ptr) + 0xFFFF800000000000;
    uint8 *start = (uint8*)&acpi_pm_info->madt->rest_fields;
    uint64 end = (uint64)start + (acpi_pm_info->madt->Length - sizeof(struct MADT));
    id_vmmap(acpi_pm_info->madt->local_controller_addr, 0x10000, 3);
    id_vmmap(0xFEC00000, 0x2000, 3);
    bool finished = false;
    int cpus = 0, ioapics = 0;
    acpi_pm_info->cpus = 0;
    int entries = end - (uint64)start;
    void *new_addr = 0;
    while(entries-- && !finished)
    {
        switch(*start)
        {
            case 0: ;
                struct LAPIC *lapic = (struct LAPIC*) start;
                if(!lapic->length)
                {
                    finished = true;
                    break;
                }
                if(cpus == 0)
                {
                    lapicEnable(lapic->flags);
                }

                new_addr = kmalloc((cpus+1)*8); //Each addr is 8 bytes wide
                memcpy_fast(new_addr, acpi_pm_info->lapic, cpus * sizeof(struct LAPIC));
                acpi_pm_info->lapic = new_addr;

                acpi_pm_info->lapic[cpus] =  kmalloc(sizeof(struct LAPIC));
                memcpy_fast(acpi_pm_info->lapic[cpus++], lapic, sizeof(struct LAPIC));
                
                start += lapic->length;
                break;
            case 1: ;
                struct IOAPIC *ioapic = (struct IOAPIC*)start;
                if(!ioapic->length)
                {
                    finished = true;
                    break;
                }
                id_vmmap(ioapic->address, 1, 3);
                ioapicEnable(ioapic->address, 0);

                new_addr = kmalloc((ioapics+1)*8); //Each addr is 8 bytes wide
                memcpy_fast(new_addr, acpi_pm_info->ioapic, ioapics * sizeof(struct IOAPIC));
                acpi_pm_info->ioapic = new_addr;

                acpi_pm_info->ioapic[ioapics] = kmalloc(sizeof(struct IOAPIC));
                memcpy_fast(acpi_pm_info->ioapic[ioapics++], ioapic, sizeof(struct IOAPIC));
                start += ioapic->length;
                break;
            case 2: ;
                struct APIC_ISO *apic_iso = (struct APIC_ISO*)start;
                if(!apic_iso->length)
                {
                    finished = true;
                    break;
                }
                ioapicMapIrq(apic_iso->irq_src, apic_iso->interrupt, 0);
                start += apic_iso->length;
                break;
            case 3: ;
                struct IOAPIC_NMI *ioapic_nmi = (struct IOAPIC_NMI*)start;
                if(!ioapic_nmi->length)
                {
                    finished = true;
                    break;
                }
                IOApicConfigureNMI(ioapic_nmi->GSI, ioapic_nmi->flags);
                start += ioapic_nmi->length;
                break;
            case 4: ;
                struct LAPIC_NMI *lapic_nmi = (struct LAPIC_NMI*)start;
                if(!lapic_nmi->length)
                {
                    finished = true;
                    break;
                }
                lapicConfigureNMI(lapic_nmi->lint, lapic_nmi->flags);
                start += lapic_nmi->length;
                break;
            case 5: ;
                struct LAPIC_OVERRIDE *lapic_ovr = (struct LAPIC_OVERRIDE*)start;
                if(!lapic_ovr->length)
                {
                    finished = true;
                    break;
                }
                acpi_pm_info->lapic_override = lapic_ovr;
                start += lapic_ovr->length;
                break;
            default:
                start++;
                break;
        }
    }
    acpi_pm_info->cpus = cpus;
    //lapicTimerStart();
}