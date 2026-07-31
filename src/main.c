#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>

PSP_MODULE_INFO("PSP-SystemMonitor", 0, 1, 0);


int main()
{
    pspDebugScreenInit();
    int aktiv = 1;
    int menu = 0;
    int letztesmenu = -1;
    SceCtrlData controller;

    while  (aktiv == 1) {

        sceCtrlPeekBufferPositive(&controller, 1);
if (controller.Buttons & PSP_CTRL_CROSS) {
    menu = 1;
}

if (menu == 0) {
    if (letztesmenu != menu) {
        pspDebugScreenClear();
        letztesmenu = menu;
    
    pspDebugScreenPrintf("PSP System Monitor\n");
    pspDebugScreenPrintf("Press X to start\n");
    pspDebugScreenPrintf("Press O to exit\n");
    sceKernelDelayThread(10000);
    }

}
if (menu == 1) {
    if (letztesmenu != menu) {
        pspDebugScreenClear();
        letztesmenu = menu;
    
    pspDebugScreenPrintf("====================================================================\n");
    pspDebugScreenPrintf("                         System-Monitor\n");
    pspDebugScreenPrintf("====================================================================\n\n\n\n");
    pspDebugScreenPrintf("Press O to exit\n");
    sceKernelDelayThread(10000);
    }
}

if (controller.Buttons & PSP_CTRL_CIRCLE) {
    aktiv = 0;
}


}

sceKernelExitGame();
return 0;

}