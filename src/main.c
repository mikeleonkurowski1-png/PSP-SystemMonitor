#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdint.h>
#include <psppower.h>
#include <pspwlan.h>
#include <pspnet_apctl.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <psputility.h>
#include <psputility_netmodules.h>


PSP_MODULE_INFO("PSP-SystemMonitor", 0, 1, 0);


int main()
{
    pspDebugScreenInit();
    int aktiv = 1;
    int menu = 0;
    int letztesmenu = -1;
    int oldbuttonState = 0;


    SceCtrlData controller;


    //Netzwerk initialisieren
    int result;
    result = sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
    pspDebugScreenPrintf("COMMON: %08X\n", result);

    result = sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
    pspDebugScreenPrintf("INET: %08X\n", result);
    sceNetInit(128 * 1024, 42, 4 * 1024, 42, 4 * 1024);
    sceNetInetInit();
    sceNetApctlInit(0x8000, 48);
    


    while  (aktiv == 1) {

        int cpuClock = scePowerGetCpuClockFrequency();
        int devkitVersion = sceKernelDevkitVersion();
        SceSize totalFreeRAMSize = sceKernelTotalFreeMemSize();
        int MaximumClock = 333;
        int batteryPercent = scePowerGetBatteryLifePercent();
        int chargingStatus = scePowerIsBatteryCharging();
        int wlanstatus2 = sceWlanGetSwitchState();
        int netState = 0;
        sceNetApctlGetState(&netState);
    



        sceCtrlPeekBufferPositive(&controller, 1);


        int pressed = controller.Buttons & ~oldbuttonState;
        oldbuttonState = controller.Buttons;

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
    pspDebugScreenPrintf("Devkit Version: %d      ", devkitVersion);
    

    pspDebugScreenSetXY(0,11);
    pspDebugScreenPrintf("Hardware-Monitor: ");
    
        pspDebugScreenSetXY(0,13);
    pspDebugScreenPrintf("Current CPU Clock: %d MHz     ", cpuClock);
    pspDebugScreenSetXY(0,14);
    pspDebugScreenPrintf("Maximum CPU Clock: %d MHz      ", MaximumClock);

    pspDebugScreenSetXY(0,16);
    pspDebugScreenPrintf("Free RAM: %.2f MB      ", totalFreeRAMSize / 1024.0 / 1024.0);

    pspDebugScreenSetXY(0,18);
    pspDebugScreenPrintf("Battery-Percent: %d%%      ", batteryPercent);
    if (chargingStatus) {
        pspDebugScreenSetXY(0,19);
        pspDebugScreenPrintf("Battery-Charging: Yes      ");
    } else {
        pspDebugScreenSetXY(0,19);
        pspDebugScreenPrintf("Battery-Charging: No   ");

    }

    

    if (wlanstatus2 == 1) {
        pspDebugScreenSetXY(0,21);
        pspDebugScreenPrintf("WLAN-Switch-Status: ON       ");
    } else {
        pspDebugScreenSetXY(0,21);
        pspDebugScreenPrintf("WLAN-Switch-Status: OFF      ");
    }

    union SceNetApctlInfo info;


    pspDebugScreenSetXY(0,23);
    if (netState == 4) {
        sceNetApctlGetInfo(8, &info);
        pspDebugScreenPrintf("IP-Address: %s                 ", info.ip);
    } else {
        pspDebugScreenPrintf("IP-Address: Not connected      ");
    } 



    pspDebugScreenSetXY(0,22);
    if (netState == 4) {
        sceNetApctlGetInfo(5, &info);
    pspDebugScreenPrintf("Signal-Strength: %d%%                ", info.strength);
    } else {
        pspDebugScreenPrintf("Signal-Strength: Not connected      ");
    }

    switch(netState) {
        case 0:
            pspDebugScreenSetXY(0,24);
            pspDebugScreenPrintf("Network-State: Disconnected          ");
            break;
        case 1:
            pspDebugScreenSetXY(0,24);
            pspDebugScreenPrintf("Network-State: Scanning              ");
            break;
        case 2:
            pspDebugScreenSetXY(0,24);
            pspDebugScreenPrintf("Network-State: Joining              ");
            break;
        case 3:
            pspDebugScreenSetXY(0,24);
            pspDebugScreenPrintf("Network-State: Getting IP Address       "); 
            break;
        case 4:
            pspDebugScreenSetXY(0,24);   
            pspDebugScreenPrintf("Network-State: Connected             ");
            break;
        default:
            pspDebugScreenSetXY(0,24);
            pspDebugScreenPrintf("Network-State: Unknown               ");
    }
    

    pspDebugScreenSetXY(0,31);
    pspDebugScreenPrintf("Press □ (square) to connect/disconnect to a WLAN-Access-Point");

    pspDebugScreenSetXY(0,32);
    pspDebugScreenPrintf("Press O to exit");


sceKernelDelayThread(100000); //Begrenzt wie schnell die Schleife läuft

}

if (controller.Buttons & PSP_CTRL_CIRCLE) {
    aktiv = 0; //Wird O gedrückt, welches das Programm beendet
}

if (pressed & PSP_CTRL_SQUARE) {
    //if (netState == 4) {
    //    sceNetApctlDisconnect();
    //} else {
//
 //       int result2 =sceNetApctlConnect(0);
   //     pspDebugScreenSetXY(0,25);
     //   pspDebugScreenPrintf("Connect Result: %08X   ", result2);
    //}

    int state;
    sceNetApctlGetState(&state);

    //pspDebugScreenSetXY(0,25);
    //pspDebugScreenPrintf("Before connect state: %d", state);

    int result = sceNetApctlConnect(0); // Connect to the first available access point

    //pspDebugScreenSetXY(0,26);
    //pspDebugScreenPrintf("Connect result: %08X", result);
}
}

sceKernelExitGame();
return 0;

}
