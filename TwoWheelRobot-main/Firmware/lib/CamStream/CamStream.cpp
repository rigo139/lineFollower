#include "CamStream.h"

#if (CAMERA_MODEL_SELECTED)
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

CamStreamClass::CamStreamClass(String pWsAddress)
    #if !(USING_TINYWEBSOCKETS)
    : _ws( pWsAddress.c_str() )
    #endif
{
    //
    #if (USING_TINYWEBSOCKETS)
    _ws.listen(8080);
    #endif
}

esp_err_t CamStreamClass::setup(void) {
    static camera_config_t config =
    {
        // GPIO pin for camera power down line 
        .pin_pwdn		= PWDN_GPIO_NUM,
        // GPIO pin for camera reset line 
        .pin_reset		= RESET_GPIO_NUM,
        // GPIO pin for camera XCLK line 
        .pin_xclk		= XCLK_GPIO_NUM,
        // GPIO pin for camera SDA line 
        .pin_sscb_sda	= SIOD_GPIO_NUM,
        // GPIO pin for camera SCL line 
        .pin_sscb_scl	= SIOC_GPIO_NUM,
        // GPIO pin for camera D7-D0 lines
        .pin_d7	= Y9_GPIO_NUM,
        .pin_d6	= Y8_GPIO_NUM,
        .pin_d5	= Y7_GPIO_NUM,
        .pin_d4	= Y6_GPIO_NUM,
        .pin_d3	= Y5_GPIO_NUM,
        .pin_d2	= Y4_GPIO_NUM,
        .pin_d1	= Y3_GPIO_NUM,
        .pin_d0	= Y2_GPIO_NUM,
        // GPIO pin for camera VSYNC line 
        .pin_vsync	= VSYNC_GPIO_NUM,
        // GPIO pin for camera HREF line 
        .pin_href	= HREF_GPIO_NUM,
        // GPIO pin for camera PCLK line 
        .pin_pclk	= PCLK_GPIO_NUM,
        
        // Frequency of XCLK signal, in Hz. EXPERIMENTAL: Set to 16MHz on ESP32-S2 or ESP32-S3 to enable EDMA mode 
        .xclk_freq_hz	= 10000000,

        // LEDC timer to be used for generating XCLK  
        .ledc_timer		= LEDC_TIMER_0,
        // LEDC channel to be used for generating XCLK  	
        .ledc_channel	= LEDC_CHANNEL_0,
        
        // Format of the pixel data: PIXFORMAT_ + YUV422|GRAYSCALE|RGB565|JPEG  
        .pixel_format	= PIXFORMAT_JPEG,
        // Size of the output image: FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA  
        .frame_size		= FRAMESIZE_QVGA,
        
        // Quality of JPEG output. 0-63 lower means higher quality  
        .jpeg_quality	= 10,
        // Number of frame buffers to be allocated. If more than one, then each frame will be acquired (double speed)  	
        .fb_count		= 1,
        // The location where the frame buffer will be allocated (CAMERA_FB_IN_PSRAM or CAMERA_FB_IN_DRAM)
        #ifdef BOARD_HAS_PSRAM
        .fb_location	= CAMERA_FB_IN_PSRAM, 
        #else
        .fb_location	= CAMERA_FB_IN_DRAM, 
        #endif
        // When buffers should be filled (CAMERA_GRAB_WHEN_EMPTY or CAMERA_GRAB_LATEST)
        .grab_mode	= CAMERA_GRAB_WHEN_EMPTY
    };

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err == ESP_OK) {
        sensor_t *s = esp_camera_sensor_get();
        s->set_vflip(s, 0);
        s->set_hmirror(s, 0);

        #if (CAM_DISABLE_BROWNOUT)
        // Turn-off the 'brownout detector'
        WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
        #endif
    }
    return err;
}

void CamStreamClass::loop(void) {
    if( (uint32_t)(millis() - _lastSentMs) > SEND_CAMERA_PERIOD_MS ) {
        if( sendCamera() ){
            _lastSentMs = millis();
        }
    }
}

uint8_t CamStreamClass::sendCamera(void) {
    #if USING_TINYWEBSOCKETS
    auto client = _ws.accept();
    if( !client.available() ){return 0;}
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        esp_camera_fb_return(fb);
        return 0;
    }
    client.sendBinary((const char*)fb->buf, fb->len);
    esp_camera_fb_return(fb);
    return 1;
    #else
    _ws.cleanupClients();
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        esp_camera_fb_return(fb);
        return 0;
    }
    _ws.binaryAll(fb->buf, fb->len);
    esp_camera_fb_return(fb);
    return 1;
    #endif
}


#endif // (CAMERA_MODEL_SELECTED)