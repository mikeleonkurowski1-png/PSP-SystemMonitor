#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("PSP-SystemMonitor", 0, 1, 0);


int main()
{
    pspDebugScreenInit();
    int aktiv = 1;

    while  (aktiv == 1) {

pspDebugScreenClear();
pspDebugScreenPrintf("PSP System Monitor\n");
pspDebugScreenPrintf("Press X to start\n");
pspDebugScreenPrintf("Press O to exit\n");

sceKernelDelayThread(1000000);
}

return 0;

}