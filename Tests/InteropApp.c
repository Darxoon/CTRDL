
#include <dlfcn.h>

#include <stdio.h>
#include <string.h>

typedef void (*InteropFn)(const char*);

// Reserve some heap memory for code allocation.
u32 __ctru_heap_size = (8 << 20); // 8MB for application heap.
u32 __ctru_linear_heap_size = (8 << 20); // 8MB for linear heap.

int main(int argc, char* argv[]) {
    gfxInitDefault();

    PrintConsole console;
    consoleInit(GFX_TOP, &console);

    printf("Loading library...\n");
    void* h = dlopen("sdmc:/libinterop.so", RTLD_NOW);
    if (!h)
        goto fail;

    printf("Looking for symbol...\n");
    InteropFn interop = (InteropFn)dlsym(h, "interop");
    if (!interop)
        goto fail;

    printf("- Address of interop(): 0x%08x\n", interop);  
    interop("Hello from bottom screen!");

    consoleSelect(&console);

    printf("Unloading library...\n");
    if (dlclose(h))
        goto fail;

    printf("Success!\n");
    goto end;

fail:
    printf("ERROR: %s.\n", dlerror());

end:
    while (aptMainLoop()) {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break;
    }

    gfxExit();
    return 0;
}