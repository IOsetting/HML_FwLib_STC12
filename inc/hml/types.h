/*****************************************************************************/
/** 
 * \file        types.h
 * \author      Jiabin Hsu  | zsiothsu@zhishan-iot.tk
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       HML standard data type define, include base data type and extended
 *              data type
 * \note        HML only uses data types ruled by this file!
 * \version     
 * \ingroup     generic
******************************************************************************/

#ifndef ___HML_TYPES_H___
#define ___HML_TYPES_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/**
 *             [ HML BASE DATA TYPE SHEET ]
 * ========================================================
 * |   HML base data type   |         description         |
 * ========================================================
 * |         bool           |         boolean type        |
 * |------------------------|-----------------------------|
 * |         char           |        character type       |
 * |------------------------|-----------------------------|
 * |        uint8_t         |   unsigned 8-bit integer    |
 * |------------------------|-----------------------------|
 * |        int8_t          |    signed 8-bit integer     |
 * |------------------------|-----------------------------|
 * |       uint16_t         |   unsigned 16-bit integer   |
 * |------------------------|-----------------------------|
 * |        int16_t         |    signed 16-bit integer    |
 * |------------------------|-----------------------------|
 * |       uint32_t         |   unsigned 32-bit integer   |
 * |------------------------|-----------------------------|
 * |        int32_t         |    signed 32-bit integer    |
 * |------------------------|-----------------------------|
 * |       uint64_t         |   unsigned 64-bit integer   |
 * |------------------------|-----------------------------|
 * |        int64_t         |    signed 64-bit integer    |
 * ========================================================
 *
 * \note base data types are all defined in original header files provides by
 *       SDCC official
 */

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/
#define BYTE_MAX   UINT8_MAX
#define WORD_MAX   UINT16_MAX

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark user action
 */
typedef enum
{
    DISABLE = 0x0,
    ENABLE  = !DISABLE
} Action;

/**
 * \brief mark bit value/state
 */
typedef enum
{
    RESET = 0x0,
    SET   = !RESET
} FunctionalState;

/**
 * \brief mark generic interrupt priority
 */
typedef enum
{
    IntPriority_Lowest  = 0x00,
    IntPriority_Low     = 0x01,
    IntPriority_High    = 0x02,
    IntPriority_Highest = 0x03,
} IntPriority;

#endif
