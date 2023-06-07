/*
    M A I N
*/

#include <project.h>
#include <stdlib.h>

#include <SEGGER.h>
#include <FS.h>

#include "u8x8_psoc.h"
#include <u8g2.h>
#include <strings.h>

#define DISPLAY_ADDRESS 0x3C // 011110+SA0+RW - 0x3C or 0x3D

extern const uint8_t u8g2_font_zx_8r[] U8X8_FONT_SECTION("u8g2_font_zx_8r");
#include "media/logo.xbm"

int main(){

    u8g2_t u8g2;
    
    I2COLED_Start();

    FS_Init();
    FS_FAT_SupportLFN();

    CyGlobalIntEnable;
    
	u8g2_Setup_ssd1306_i2c_128x32_univision_f (&u8g2, U8G2_R0, u8x8_byte_psoc_hw_i2c, u8x8_psoc_delay);
    u8g2_SetI2CAddress(&u8g2,DISPLAY_ADDRESS);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearBuffer(&u8g2);

    u8g2_DrawXBM(&u8g2,0,0,66,32,logo_bits);
    u8g2_SetFont(&u8g2, u8g2_font_zx_8r);
    u8g2_SetFontRefHeightText(&u8g2);
    u8g2_SetFontPosTop(&u8g2);
	u8g2_DrawStr(&u8g2, 72, 8,  "PSoC 5");
    u8g2_DrawStr(&u8g2, 72, 20, "I2C HW");
    u8g2_SendBuffer(&u8g2);
    CyDelay(5000);

#ifdef FS_VERSION
        
    FS_FIND_DATA fd; 
    FS_FILE * file;
    uint8_t * font;

    char acFilename[256];
    char fullName[512];
    
 for(;;) {
    
    strncpy(fullName,"\\FONTS\\",10);
    int nLen = strlen(fullName);
    if (FS_FindFirstFile(&fd, "\\FONTS\\", acFilename, sizeof(acFilename)) == 0) { 
        do { 
            if (acFilename[0] == '.') { continue; }
            strncpy(fullName+nLen,acFilename,256);
            file = FS_FOpen(fullName,"r");
            if (file!=0) {
                font = malloc(fd.FileSize);
                if (!font) { continue;}
                FS_Read(file,font,fd.FileSize);
                FS_FClose(file);
                u8g2_SetFont(&u8g2, font);
                u8g2_ClearBuffer(&u8g2);
                u8g2_DrawStrX2(&u8g2, 0, 0, "!@#$%^&*");
                u8g2_DrawStrX2(&u8g2, 0, 16, "0123ABcd");
                u8g2_SendBuffer(&u8g2);
                CyDelay(1000);
                u8g2_SetFont(&u8g2, u8g2_font_zx_8r);
                free(font);
            } 
        }  while (FS_FindNextFile (&fd)); 
    } 
    FS_FindClose(&fd);

    strncpy(fullName,"\\IMAGES\\",10);
    nLen = strlen(fullName);
    int w,h;
    char * token;
    if (FS_FindFirstFile(&fd, "\\IMAGES\\", acFilename, sizeof(acFilename)) == 0) { 
        do { 
            if (acFilename[0] == '.') { continue; }
            strncpy(fullName+nLen,acFilename,256);
            file = FS_FOpen(fullName,"r");
            if (file!=0) {
                font = malloc(fd.FileSize);
                if (!font) { continue;}
                FS_Read(file,font,fd.FileSize);
                FS_FClose(file);
                token = strtok(acFilename,"_");
                token = strtok(NULL, "_");
                w = atoi(token);
                token = strtok(NULL, "_");
                h = atoi(token);
                u8g2_ClearBuffer(&u8g2);
                u8g2_DrawXBM(&u8g2,(128-w)/2,(32-h)/2,w,h,font);
                u8g2_SendBuffer(&u8g2);
                CyDelay(1000);
                free(font);
            } 
        }  while (FS_FindNextFile (&fd)); 
    } 
    FS_FindClose(&fd);
    
#else    
    for(;;);   
#endif
   
}

}

/* [] END OF FILE */