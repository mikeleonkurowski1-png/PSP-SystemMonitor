#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdint.h>
#include <psppower.h>
#include <pspwlan.h>
#include <pspnet_apctl.h>


PSP_MODULE_INFO("PSP-SystemMonitor", 0, 1, 0);


int main()
{
    pspDebugScreenInit();
    int aktiv = 1;
    int menu = 0;
    int letztesmenu = -1;


    SceCtrlData controller;
    SceKernelSystemStatus systemStatus;
    

    while  (aktiv == 1) {

        int cpuClock = scePowerGetCpuClockFrequency();
        int devkitVersion = sceKernelDevkitVersion();
        SceSize totalFreeRAMSize = sceKernelTotalFreeMemSize();
        int Status = sceKernelReferSystemStatus(&systemStatus);
        int MaximumClock = 333;
        int batteryPercent = scePowerGetBatteryLifePercent();
        int chargingStatus = scePowerIsBatteryCharging();
        int wlanstatus2 = sceWlanGetSwitchState();




        sceCtrlPeekBufferPositive(&controller, 1);
if (controller.Buttons & PSP_CTRL_CROSS) {
    menu = 1; //Wird X gedrückt, welches das Menü in den Zustand 1, also in den Start des Programms
}

if (menu == 0) {
    //Aktualisiert den Bildschirm nur, wenn das Menü gewechselt wurde, um Flackern zu vermeiden
    if (letztesmenu != menu) { 
        pspDebugScreenClear();
        letztesmenu = menu;
    
    pspDebugScreenPrintf("====================================================================\n");
    pspDebugScreenPrintf("                         System-Monitor\n");
    pspDebugScreenPrintf("====================================================================\n\n");
    pspDebugScreenPrintf("Press X to start\n");
    pspDebugScreenPrintf("Press O to exit\n");
    }

}
if (menu == 1) {
    
    
    if (letztesmenu != menu) {
        pspDebugScreenClear();
        letztesmenu = menu;
    
    pspDebugScreenPrintf("====================================================================\n");
    pspDebugScreenPrintf("                         System-Monitor\n");
    pspDebugScreenPrintf("====================================================================\n\n");
        }


    //pspDebugScreenPrintf("%d MHz\n", cpuClock);
    pspDebugScreenSetXY(0,5);
    pspDebugScreenPrintf("Software-Monitor:");
    pspDebugScreenSetXY(0,7);
    pspDebugScreenPrintf("Devkit Version: %d", devkitVersion);
    
    
    pspDebugScreenSetXY(0,11);
    pspDebugScreenPrintf("Hardware-Monitor: ");
    
        pspDebugScreenSetXY(0,13);
    pspDebugScreenPrintf("Current CPU Clock: %d MHz", cpuClock);
    pspDebugScreenSetXY(0,14);
    pspDebugScreenPrintf("Maximum CPU Clock: %d MHz", MaximumClock);

    pspDebugScreenSetXY(0,16);
    pspDebugScreenPrintf("Free Memory: %.2f MB", totalFreeRAMSize / 1024.0 / 1024.0);

    pspDebugScreenSetXY(0,18);
    pspDebugScreenPrintf("Battery-Percent: %d%%", batteryPercent);
    if (chargingStatus) {
        pspDebugScreenSetXY(0,19);
        pspDebugScreenPrintf("Battery-Charging: Yes");
    } else {
        pspDebugScreenSetXY(0,19);
        pspDebugScreenPrintf("Battery-Charging: No");

    }

    

    if (wlanstatus2 == 1) {
        pspDebugScreenSetXY(0,21);
        pspDebugScreenPrintf("WLAN-Switch-Status: ON");
    } else {
        pspDebugScreenSetXY(0,21);
        pspDebugScreenPrintf("WLAN-Switch-Status: OFF");
    }
    
    pspDebugScreenSetXY(0,32);
    pspDebugScreenPrintf("Press O to exit");

    
    

if (controller.Buttons & PSP_CTRL_CIRCLE) {
    aktiv = 0; //Wird O gedrückt, welches das Programm beendet
}

sceKernelDelayThread(100000); //Begrenzt wie schnell die Schleife läuft

}
}

sceKernelExitGame();
return 0;

}
