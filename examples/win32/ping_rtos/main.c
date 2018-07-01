/**
 * \file            main.c
 * \brief           Main file
 */

/*
 * Copyright (c) 2018 Tilen Majerle
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of ESP-AT.
 *
 * Before you start using WIN32 implementation with USB and VCP,
 * check esp_ll_win32.c implementation and choose your COM port!
 */
#include "stdafx.h"
#include "esp/esp.h"
#include "station_manager.h"

static espr_t esp_callback_func(esp_evt_t* evt);

/**
 * \brief           Program entry point
 */
int
main(void) {
    uint32_t time;
    printf("Starting ESP application!\r\n");

    /*
     * Initialize ESP with default callback function
     */
    esp_init(esp_callback_func, 1);

    /*
     * Connect to access point.
     *
     * Try unlimited time until access point accepts up.
     * Check for station_manager.c to define preferred access points ESP should connect to
     */
    connect_to_preferred_access_point(1);

    /*
     * Try to ping host
     */
    if (esp_ping("example.com", &time, 1) == espOK) {
        printf("Host example.com successfully pinged in %d milliseconds\r\n", (int)time);
    } else {
        printf("Error while trying to ping example.com\r\n");
    }

    return 0;
}

/**
 * \brief           Event callback function for ESP stack
 * \param[in]       evt: Event information with data
 * \return          espOK on success, member of \ref espr_t otherwise
 */
static espr_t
esp_callback_func(esp_evt_t* evt) {
    switch (esp_evt_get_type(evt)) {
        case ESP_EVT_INIT_FINISH: {
            printf("Library initialized!\r\n");
            break;
        }
        case ESP_EVT_RESET: {
            printf("Device reset detected!\r\n");
            break;
        }
        default: break;
    }
    return espOK;
}
