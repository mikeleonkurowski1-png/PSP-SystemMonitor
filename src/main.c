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


//Farben definieren, damit man mit den Farben arbeiten kann, ohne jedes mal die Hex-Codes zu schreiben
#define COLOR_WHITE   0xFFFFFFFF
#define COLOR_CYAN    0xFFFFD800
#define COLOR_GREEN   0xFF00FF00
#define COLOR_RED     0xFF0000FF
#define COLOR_ORANGE  0xFF00A5FF
#define COLOR_YELLOW  0xFF00FFFF


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
    
        pspDebugScreenSetTextColor(COLOR_CYAN);
    pspDebugScreenPrintf("====================================================================\n");
    pspDebugScreenPrintf("                         System-Monitor\n");
    pspDebugScreenPrintf("====================================================================\n\n");
    pspDebugScreenSetTextColor(COLOR_WHITE);
    pspDebugScreenPrintf("Press X to start\n");
    pspDebugScreenPrintf("Press O to exit\n");
    }

}
if (menu == 1) {
    
    
    if (letztesmenu != menu) {
        pspDebugScreenClear();
        letztesmenu = menu;
    
        pspDebugScreenSetTextColor(COLOR_CYAN);
    pspDebugScreenPrintf("====================================================================\n");
    pspDebugScreenPrintf("                         System-Monitor\n");
    pspDebugScreenPrintf("====================================================================\n\n");
        }


    //pspDebugScreenPrintf("%d MHz\n", cpuClock);
    pspDebugScreenSetXY(0,5);
    pspDebugScreenSetTextColor(COLOR_CYAN);
    pspDebugScreenPrintf("Software-Monitor:");
    pspDebugScreenSetXY(0,7);
    pspDebugScreenSetTextColor(COLOR_WHITE);
    pspDebugScreenPrintf("Devkit Version: %d      ", devkitVersion);
    

    pspDebugScreenSetXY(0,11);
    pspDebugScreenSetTextColor(COLOR_CYAN);
    pspDebugScreenPrintf("Hardware-Monitor: ");
    
        pspDebugScreenSetXY(0,13);
    pspDebugScreenSetTextColor(COLOR_WHITE);
    pspDebugScreenPrintf("Current CPU Clock: %d MHz     ", cpuClock);
    pspDebugScreenSetXY(0,14);
    pspDebugScreenPrintf("Maximum CPU Clock: %d MHz      ", MaximumClock);

    pspDebugScreenSetXY(0,16);
    pspDebugScreenPrintf("Free RAM: %.2f MB      ", totalFreeRAMSize / 1024.0 / 1024.0);

    pspDebugScreenSetXY(0,18);
    pspDebugScreenSetTextColor(COLOR_WHITE);
    pspDebugScreenPrintf("Battery-Percent: ");
            if (batteryPercent <= 20) pspDebugScreenSetTextColor(COLOR_RED);
            else if (batteryPercent <= 50) pspDebugScreenSetTextColor(COLOR_YELLOW);
            else pspDebugScreenSetTextColor(COLOR_GREEN);
            pspDebugScreenPrintf("%d%%      ", batteryPercent);
    
    
    pspDebugScreenSetXY(0, 19);
            pspDebugScreenSetTextColor(COLOR_WHITE);
            pspDebugScreenPrintf("Battery-Charging: ");
            if (chargingStatus) {
                pspDebugScreenSetTextColor(COLOR_GREEN);
                pspDebugScreenPrintf("Yes      ");
            } else {
                pspDebugScreenSetTextColor(COLOR_RED);
                pspDebugScreenPrintf("No   ");
            }

    

    pspDebugScreenSetXY(0, 21);
            pspDebugScreenSetTextColor(COLOR_WHITE);
            pspDebugScreenPrintf("WLAN-Switch-Status: ");
            if (wlanstatus2 == 1) {
                pspDebugScreenSetTextColor(COLOR_GREEN);
                pspDebugScreenPrintf("ON       ");
            } else {
                pspDebugScreenSetTextColor(COLOR_RED);
                pspDebugScreenPrintf("OFF      ");
            }

    union SceNetApctlInfo info;


    // Signal-Stärke
            pspDebugScreenSetXY(0, 22);
            pspDebugScreenSetTextColor(COLOR_WHITE);
            pspDebugScreenPrintf("Signal-Strength: ");
            if (netState == 4) {
                sceNetApctlGetInfo(5, &info);
                pspDebugScreenSetTextColor(COLOR_GREEN);
                pspDebugScreenPrintf("%d%%                ", info.strength);
            } else {
                pspDebugScreenSetTextColor(COLOR_RED);
                pspDebugScreenPrintf("Not connected      ");
            }

            // IP-Adresse
            pspDebugScreenSetXY(0, 23);
            pspDebugScreenSetTextColor(COLOR_WHITE);
            pspDebugScreenPrintf("IP-Address: ");
            if (netState == 4) {
                sceNetApctlGetInfo(8, &info);
                pspDebugScreenSetTextColor(COLOR_GREEN);
                pspDebugScreenPrintf("%s                 ", info.ip);
            } else {
                pspDebugScreenSetTextColor(COLOR_RED);
                pspDebugScreenPrintf("Not connected      ");
            }


    // Netzwerk Status
            pspDebugScreenSetXY(0, 24);
            pspDebugScreenSetTextColor(COLOR_WHITE);
            pspDebugScreenPrintf("Network-State: ");
            switch(netState) {
                case 0:
                    pspDebugScreenSetTextColor(COLOR_RED);
                    pspDebugScreenPrintf("Disconnected          ");
                    break;
                case 1:
                    pspDebugScreenSetTextColor(COLOR_ORANGE);
                    pspDebugScreenPrintf("Scanning              ");
                    break;
                case 2:
                    pspDebugScreenSetTextColor(COLOR_YELLOW);
                    pspDebugScreenPrintf("Joining               ");
                    break;
                case 3:
                    pspDebugScreenSetTextColor(COLOR_YELLOW);
                    pspDebugScreenPrintf("Getting IP Address    "); 
                    break;
                case 4:
                    pspDebugScreenSetTextColor(COLOR_GREEN); 
                    pspDebugScreenPrintf("Connected             ");
                    break;
                default:
                    pspDebugScreenSetTextColor(COLOR_RED);
                    pspDebugScreenPrintf("Unknown               ");
            }

    pspDebugScreenSetTextColor(COLOR_WHITE);
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
