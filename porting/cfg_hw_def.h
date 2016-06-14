/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c) 2016      CreaLights Inc.      All rights reserved.
 *
 *   This is unpublished proprietary source code of CreaLights Inc.
 *   The copyright notice above does not evidence any actual or intended
 *   publication of such source code.
 *
 * DESCRIPTION:
 *   Hardware definition related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/


#ifdef DECLARE_IO

/*          name                   bit         mode             init  desc */
DECLARE_IO(IO_DUT_MDIOM_SDA_IN,  _IO(P0.0), IO_MODE_DIGITAL_OD, HIGH,  "TDI_IN")
DECLARE_IO(PWM_VBUF_OUT,         _IO(P0.1), IO_MODE_DIGITAL_PP, HIGH,  "PWM_OUT")
DECLARE_IO(IO_DUT_I2CM_SCL,      _IO(P0.2), IO_MODE_DIGITAL_OD, HIGH,  "OE_TDO")
DECLARE_IO(IO_DUT_MDIOM_SCL_OEn, _IO(P0.3), IO_MODE_DIGITAL_PP, HIGH,  "OE_TCK")
DECLARE_IO(UART_TXD,             _IO(P0.4), IO_MODE_DIGITAL_OD, HIGH,  "OE_TMS")
DECLARE_IO(UART_RXD,             _IO(P0.5), IO_MODE_DIGITAL_OD, HIGH,  "OE_VBUF")
DECLARE_IO(IO_LED_2_OUT,         _IO(P0.6), IO_MODE_DIGITAL_PP, LOW,   "LED_2")
DECLARE_IO(ADC_VREF_OUT,         _IO(P0.7), IO_MODE_ANALOG,     HIGH,  "")

DECLARE_IO(IO_Reserved_P1_0,     _IO(P1.0), IO_MODE_ANALOG,     HIGH,  "")
DECLARE_IO(IO_VBUF_OEn,          _IO(P1.1), IO_MODE_DIGITAL_OD, HIGH,  "TDO_IN")
DECLARE_IO(IO_DUT_I2CM_SDA,      _IO(P1.2), IO_MODE_DIGITAL_OD, HIGH,  "TDO_OUT")
DECLARE_IO(IO_LED_1_OUT,         _IO(P1.3), IO_MODE_DIGITAL_PP, LOW,   "LED_1")
DECLARE_IO(IO_DUT_MDIOM_SDA_OUT, _IO(P1.4), IO_MODE_DIGITAL_PP, HIGH,  "TDI_OUT")
DECLARE_IO(IO_DUT_MDIOM_SCL_IN,  _IO(P1.5), IO_MODE_DIGITAL_OD, HIGH,  "TCK_IN")
DECLARE_IO(IO_DUT_MDIOM_SCL_OUT, _IO(P1.6), IO_MODE_DIGITAL_PP, HIGH,  "TCK_OUT")
DECLARE_IO(IO_DUT_C2M_SCL,       _IO(P1.7), IO_MODE_DIGITAL_OD, HIGH,  "TMS_IN")

DECLARE_IO(IO_DUT_C2M_SDA,       _IO(P2.0), IO_MODE_DIGITAL_OD, HIGH,  "TMD_OUT")
DECLARE_IO(IO_DUT_MDIOM_SDA_OEn, _IO(P2.1), IO_MODE_DIGITAL_PP, HIGH,  "OE_TDI")
DECLARE_IO(ADC_VBUF_IN,          _IO(P2.2), IO_MODE_ANALOG,     HIGH,  "VBUF_AI")
DECLARE_IO(IO_LED_STATUS_OUT,    _IO(P2.3), IO_MODE_DIGITAL_PP, HIGH,  "P2.3")
DECLARE_IO(IO_Reserved_P2_4,     _IO(P2.4), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P2_5,     _IO(P2.5), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P2_6,     _IO(P2.6), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P2_7,     _IO(P2.7), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")

DECLARE_IO(IO_Reserved_P3_0,     _IO(P3.0), IO_MODE_ANALOG,     HIGH,  "C2DAT")
DECLARE_IO(IO_Reserved_P3_1,     _IO(P3.1), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P3_2,     _IO(P3.2), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P3_3,     _IO(P3.3), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P3_4,     _IO(P3.4), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P3_5,     _IO(P3.5), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P3_6,     _IO(P3.6), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")
DECLARE_IO(IO_Reserved_P3_7,     _IO(P3.7), IO_MODE_DIGITAL_OD, HIGH,  "Non-existance pin")

#endif


#ifdef DECLARE_ADC

/*            name             PosCh          NegCh         AvgNO        desc  */
DECLARE_ADC(ADC_EVB_TEMP,   ADC_CHP_TEMP,  ADC_CHN_GND,   ADC_AVGNO_8,    "")
DECLARE_ADC(ADC_EVB_VCC,    ADC_CHP_VDD,   ADC_CHN_VREF,  ADC_AVGNO_8,    "")
DECLARE_ADC(ADC_EVB_VBUF,   ADC_CHP_P2_2,  ADC_CHN_GND,   ADC_AVGNO_8,    "")

#endif


#ifdef DECLARE_PCA

/*            name            ch          io              mode             init   desc  */
DECLARE_PCA(PWM_VBUF,       _PCA(0),  PWM_VBUF_OUT,     PCA_MODE_PWM_8BIT, 0xFF,   "")
DECLARE_PCA(PCA_Reserved_1, _PCA(1),  IO_Reserved_P2_7, PCA_MODE_DISABLE,  0x0000, "")
DECLARE_PCA(PCA_Reserved_2, _PCA(2),  IO_Reserved_P2_7, PCA_MODE_DISABLE,  0x0000, "")
DECLARE_PCA(PCA_Reserved_3, _PCA(3),  IO_Reserved_P2_7, PCA_MODE_DISABLE,  0x0000, "")

#endif

