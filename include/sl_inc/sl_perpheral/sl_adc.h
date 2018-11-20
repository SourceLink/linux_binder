#ifndef SL_ADC_H_
#define SL_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif


	extern int adc_set(const char *slots_dir, const char *cape_set);
	extern int get_adc_value(const *fileName);
#ifdef __cplusplus
}
#endif


#endif