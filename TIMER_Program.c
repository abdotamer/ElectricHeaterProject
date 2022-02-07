#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"TIMER_Private.h"
#include"TIMER_Config.h"

void TIMER0_VidInit(void)
{
	/* Set Suitable Prescaler */
	TCCR0&=0xF8;
	TCCR0|=TIMER0_SET_PRESCALER;
	/* Set Timer mode */
#if TIMER0_SET_MODE == TIMER_NORMAL_MODE
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	/*Enable to overflow interrupt*/
	SET_BIT(TIMSK,0);

#elif TIMER0_SET_MODE == TIMER_CTC_MODE
	CLR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	/*Enable to CTC interrupt*/
	SET_BIT(TIMSK,1);
#if TIMER0_OC0_MODE==TIMER0_OC0_DISCONNECTED
	CLR_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
#elif TIMER0_OC0_MODE==TIMER0_OC0_TOGGLE
	CLR_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#elif TIMER0_OC0_MODE==TIMER0_OC0_CLR
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
#elif TIMER0_OC0_MODE==TIMER0_OC0_SET
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#else
#error" TIMER0 Oc0 option is not valid "
#endif
#elif TIMER0_SET_MODE == TIMER_PHASE_CORRECT_PWM_MODE
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
#elif TIMER0_SET_MODE == TIMER_FAST_PWM_MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
#else
#error" TIMER Mode is not valid "
#endif
	TIMER0_VidSET_Preload(0); //To reset Count
}
void TIMER0_VidSET_Preload(u8 Copy_u8PreloadValue)
{
	TCNT0=Copy_u8PreloadValue;
}

void TIMER0_VidSET_CTCValue(u8 Copy_u8CTCValue)
{
	OCR0=Copy_u8CTCValue;
}
void TIMER0_OFF()
{
	CLR_BIT(TIMSK,0);
	CLR_BIT(TIMSK,1);
}
