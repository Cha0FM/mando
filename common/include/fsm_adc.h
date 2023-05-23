/**
 * @file fsm_adc.h
 * @author Javier y Manuel
 * @brief Cabecera de la FSM del Mando-ADC
 * @version 1.0
 * @date 2023-05-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef FSM_ADC_H_
#define FSM_ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include "fsm.h"


/**
 * @brief Crea una nueva maquina de estados para leer correctamente el ADC
 * 
 * @param timeAdc Tiempo entre cada lectura/envio del ADC
 * @return fsm_t* 
 */
fsm_t * fsm_adc_new(uint32_t timeAdc);

/**
 * @brief Inicializa todos los parametros de la FSM para leer correctamente el ADC
 * 
 * @param p_fsm Puntero a la FSM del ADC
 * @param timeAdc Tiempo entre cada lectura/envio del ADC
 */
void fsm_adc_init(fsm_t *p_fsm, uint32_t timeAdc);



#endif // FSM_ADC_H_
