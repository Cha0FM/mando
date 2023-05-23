#include <stddef.h>
#include <stdlib.h>
#include "fsm_adc.h"
#include "stm32f4xx_hal.h" 
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdio.h>
#include "main.h"
#include "MY_NRF24.h" //Hal driver del NRF

typedef struct
{
    fsm_t fsm;              /*!< Internal FSM from the library */
    uint32_t adcVal;        /*!< Valor del Potenciometro ADC de 0-255 */
    bool ack[1];               /*!< AcK de vuelta */
    uint32_t timeAdc;      /*!< Duracion entre cada muestra del ADC*/
    uint32_t myTxData[32]; /*!< Buffer de transmision*/
} fsm_adc_t;

/**
 * @brief Lee el valor existente en el ADC y lo transmite, esperando ack
 * 
 * @param p_fsm Puntero a la FSM del ADC
 */
void do_read_transmit_adc(fsm_t *p_fsm)
{
 fsm_adc_t * p_adc = ( fsm_adc_t *) p_fsm ;
    HAL_ADC_Start(&hadc1);
    p_adc -> myTxData[0] = HAL_ADC_GetValue(&hadc1);
    boton = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
    if(boton == GPIO_PIN_SET)
    {
     p_adc -> myTxData[1]= (uint32_t)0;
    }
    else{
      p_adc -> myTxData[1]= (uint32_t)1;
    }
    if(NRF24_write(p_adc -> myTxData , 32))
    {
        NRF24_read(p_adc -> ack, 1);
    }

}

/**
 * @brief Comprueba el timer para saber si es el momento de leer/transmitir el ADC.
 * Por falta de tiempo, en esta version no lo hemos implementado, por lo que devolvera true siempre
 * 
 * @param p_fsm Puntero a la FSM del ADC
 * @return true 
 * @return false 
 */
bool check_timeout_adc(fsm_t *p_fsm)
{
return true;
}

/**
 * @brief Comprueba si ha recibido el ack de vuelta de parte del skate
 * 
 * @param p_fsm Puntero a la FSM del ADC
 * @return true 
 * @return false 
 */
bool check_ack(fsm_t *p_fsm)
{
    fsm_adc_t * p_adc = ( fsm_adc_t *) p_fsm ;
    return p_adc -> ack;
    
}

/**
 * @brief Poner el campo del ack a false
 * 
 * @param p_fsm Puntero a la FSM del ADC
 */
void do_ack_false(fsm_t *p_fsm)
{
    fsm_adc_t * p_adc = ( fsm_adc_t *) p_fsm ;
    p_adc -> ack[0] = false;
}

/**
 * @brief Estados de FSM ADC
 * 
 */
enum FSM_ADC_STATES
{
    WAITADC ,
    WAITACK

};

static fsm_trans_t fsm_trans_adc[] = {
    { WAITADC , check_timeout_adc , WAITACK , do_read_transmit_adc },
 { WAITACK , check_ack , WAITADC , do_ack_false },
 { -1 , NULL , -1, NULL }
};

fsm_t *fsm_adc_new(uint32_t timeAdc)
{
fsm_t *p_fsm = malloc(sizeof(fsm_adc_t));
    if (p_fsm)
    {
        fsm_adc_init(p_fsm, timeAdc);
    }
    return p_fsm;
}

void fsm_adc_init(fsm_t *p_fsm, uint32_t timeAdc)
{
    fsm_adc_t * p_adc= ( fsm_adc_t *) p_fsm ;
 fsm_init (& p_adc -> fsm , fsm_trans_adc );
 p_adc -> adcVal = 0;
 p_adc -> ack[0] = false;
 p_adc -> timeAdc = timeAdc;
 p_adc -> myTxData[0] = (uint32_t)0;
 p_adc -> myTxData[1] = (uint32_t)0;
}
