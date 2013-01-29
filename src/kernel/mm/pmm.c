#include <kassert.h>
#include <lock.h>
#include <memmap.h>
#include <pmm.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


#define PAGE_SHIFT 12
#define PAGE_SIZE  (1 << PAGE_SHIFT)


#define BITMAP_COW_FLAG (1 << 7)
#define BITMAP_USERS    (0xFF & ~BITMAP_COW_FLAG)


static uintptr_t mem_base = (uintptr_t)-1;
static int mem_entries;
uint8_t *bitmap;

static int look_from_here;

static lock_t bitmap_lock = unlocked;


void init_pmm(void)
{
    uintptr_t memsize = 0;

    int mmap_entries = memmap_length();

    for (int i = 0; i < mmap_entries; i++)
    {
        bool usable;
        uintptr_t base;
        size_t length;


        get_memmap_info(i, &usable, &base, &length);

        // Vorzeichenloser Überlauf ist dankenswerterweise definiert
        if (base + length < base)
            length = 0xFFFFFFFFU - base;

        if (usable && (base + length > memsize))
            memsize = base + length;

        if (usable && (base < mem_base))
            mem_base = base;
    }


    mem_entries = (memsize - mem_base) >> PAGE_SHIFT;

    uintptr_t kernel_start, kernel_end;
    get_kernel_dim(&kernel_start, &kernel_end);

    kernel_start = kernel_start >> PAGE_SHIFT;
    kernel_end = (kernel_end + PAGE_SIZE - 1) >> PAGE_SHIFT;


    // Liegt der Kernel am Beginn des benutzbaren Bereichs, so kann die Bitmap auch entsprechend verschoben werden
    if (((kernel_start << PAGE_SHIFT) <= mem_base) && ((kernel_end << PAGE_SHIFT) > mem_base))
        mem_base = kernel_end << PAGE_SHIFT;


    // Auf volle Pageframes aufrunden
    mem_base = (mem_base + PAGE_SIZE - 1) & ~((1 << PAGE_SHIFT) - 1);


    int bmp_size = (mem_entries * sizeof(*bitmap) + PAGE_SIZE - 1) >> PAGE_SHIFT;

    bitmap = (uint8_t *)(kernel_end << PAGE_SHIFT);
    kernel_end += bmp_size;

    memset(bitmap, 0, mem_entries * sizeof(*bitmap));


    // Unbenutzbare Einträge der Memory Map als belegt markieren
    for (int i = 0; i < mmap_entries; i++)
    {
        bool usable;
        uintptr_t base;
        size_t length;

        get_memmap_info(i, &usable, &base, &length);
        if (!usable)
        {
            int top;

            if (base + length + PAGE_SIZE - 1 < base) // Überlauf
                top = mem_entries;
            else
                top = (base + length + PAGE_SIZE - 1 - mem_base) >> PAGE_SHIFT;

            int start = (base - mem_base) >> PAGE_SHIFT;
            if (top > mem_entries)
                top = mem_entries;

            if (start > mem_entries) // Whyever
                continue;

            if (start < 0)
                start = 0;

            if (top < 0)
                continue;

            for (int bi = start; bi < top; bi++)
                bitmap[bi] = BITMAP_USERS;
        }
    }


    // Wenn der Kernel im von der Bitmap abgedeckten Bereich liegt
    if ((kernel_end > (mem_base >> PAGE_SHIFT)) && (kernel_start < (unsigned)(mem_entries + (mem_base >> PAGE_SHIFT))))
    {
        int s = kernel_start - (mem_base >> PAGE_SHIFT);
        int e = kernel_end - (mem_base >> PAGE_SHIFT);

        if (e > mem_entries)
            e = mem_entries;
        if (s < 0)
            s = 0;

        //Speicher für den Kernel reservieren
        for (int bi = s; bi < e; bi++)
            bitmap[bi] = BITMAP_USERS;
    }


    look_from_here = 0;
}


uintptr_t pmm_alloc(int count)
{
    bool first_occurance = true;


    kassert(count > 0);


    for (int i = look_from_here; i < mem_entries; i++)
    {
        if (!bitmap[i])
        {
            kassert_exec(lock(&bitmap_lock));

            int j;
            for (j = 0; j < count; j++)
                if (bitmap[i + j])
                    break;

            if (bitmap[i + j])
            {
                unlock(&bitmap_lock);

                i += j;
                first_occurance = false;

                continue;
            }


            for (j = 0; j < count; j++)
                bitmap[i + j] = 1;

            if (first_occurance)
                look_from_here = i + j;

            unlock(&bitmap_lock);


            return mem_base + ((uintptr_t)i << PAGE_SHIFT);
        }
    }


    kassert(0);


    return 0;
}


void pmm_free(uintptr_t start, int count)
{
    kassert(!(start & (PAGE_SIZE - 1)));
    kassert(count > 0);


    kassert_exec(lock(&bitmap_lock));

    int base = (start - mem_base) >> PAGE_SHIFT;

    for (int i = 0; i < count; i++)
    {
        kassert(bitmap[base + i] & BITMAP_USERS);
        if (!--bitmap[base + i] && (look_from_here > base + i))
            look_from_here = base + i;
    }

    unlock(&bitmap_lock);
}


void pmm_use(uintptr_t start, int count)
{
    kassert(!(start & (PAGE_SIZE - 1)));
    kassert(count > 0);


    kassert_exec(lock(&bitmap_lock));

    int base = (start - mem_base) >> PAGE_SHIFT;

    for (int i = 0; i < count; i++)
    {
        kassert(bitmap[base + i] & BITMAP_USERS); // Wenn das bisher unused ist, ist das doof.
        kassert((bitmap[base + i] & BITMAP_USERS) < BITMAP_USERS); // Sonst wird das Inkrementieren lustig.
        bitmap[base + i]++;
    }

    unlock(&bitmap_lock);
}


int pmm_user_count(uintptr_t paddr)
{
    kassert(!(paddr & (PAGE_SIZE - 1)));

    return bitmap[(paddr - mem_base) >> PAGE_SHIFT] & BITMAP_USERS;
}


void pmm_mark_cow(uintptr_t start, int count, bool flag)
{
    kassert(!(start & (PAGE_SIZE - 1)));
    kassert(count > 0);


    kassert_exec(lock(&bitmap_lock));

    int base = (start - mem_base) >> PAGE_SHIFT;

    for (int i = 0; i < count; i++)
    {
        kassert(bitmap[base + i] & BITMAP_USERS);

        if (flag)
            bitmap[base + i] |=  BITMAP_COW_FLAG;
        else
            bitmap[base + i] &= ~BITMAP_COW_FLAG;
    }

    unlock(&bitmap_lock);
}


bool pmm_is_cow(uintptr_t paddr)
{
    kassert(!(paddr & (PAGE_SIZE - 1)));

    int index = (paddr - mem_base) >> PAGE_SHIFT;

    kassert(bitmap[index] & BITMAP_USERS);

    return !!(bitmap[index] & BITMAP_COW_FLAG);
}
