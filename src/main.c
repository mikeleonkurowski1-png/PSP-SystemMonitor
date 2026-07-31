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
    
        pspDebugScreenClear();
        letztesmenu = menu;
    
    pspDebugScreenPrintf("====================================================================\n");
    pspDebugScreenPrintf("                         System-Monitor\n");
    pspDebugScreenPrintf("====================================================================\n\n");
    //pspDebugScreenPrintf("%d MHz\n", cpuClock);
    pspDebugScreenPrintf("Software-Monitor: \n\n\n");
    pspDebugScreenPrintf("Devkit Version: %d\n\n\n", devkitVersion);
    
    

    pspDebugScreenPrintf("Hardware-Monitor: \n\n\n");
    
    pspDebugScreenPrintf("Current CPU Clock: %d MHz\n", cpuClock);
    pspDebugScreenPrintf("Maximum CPU Clock: %d MHz\n\n", MaximumClock);

    pspDebugScreenPrintf("Free Memory: %.2f MB\n\n", totalFreeRAMSize / 1024.0 / 1024.0);

    pspDebugScreenPrintf("Battery-Percent: %d%%\n", batteryPercent);
    if (chargingStatus) {
        pspDebugScreenPrintf("Battery-Charging: Yes\n\n");
    } else {
        pspDebugScreenPrintf("Battery-Charging: No\n\n");

    }

    

    if (wlanstatus2 == 1) {
        pspDebugScreenPrintf("WLAN-Switch-Status: ON\n\n\n\n\n\n");
    } else {
        pspDebugScreenPrintf("WLAN-Switch-Status: OFF\n\n\n\n\n\n");
    }
    

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
