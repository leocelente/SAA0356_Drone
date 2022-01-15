# Driver

Um módulo para interagir com o Device Driver padrão de PWM
que utiliza a interface `sysfs` de arquivos. Não cobre todas
as capacidades do device driver, mas cumpre os requisitos.

```c
/**
    Changes channel duty cycle to given _percentage_
    `channel`: PWM Channel
    `duty`:_cycle Percentage duty cycle
    @return error
*/
pwm_e_t pwm_set_duty_cycle(pwm_channel_t *channel, duty_cycle_t duty_cycle);

/**
    Changes PWM channel period
    `channel`: PWM Channel
    `period`: Period time in milliseconds
    @return error
*/
pwm_e_t pwm_set_period(pwm_channel_t *channel, period_t period);

pwm_e_t pwm_enable(pwm_channel_t *channel);
pwm_e_t pwm_disable(pwm_channel_t *channel);

/**
 *  Initializes PWM channel in `path` with `duty_cycle` and
 `period`
 *
 * `channel`:
 * `path`: to sysfs char device
 * `duty`:_cycle in percent
 * `period`: in milliseconds
 * @return pwm_e_t error
 */
pwm_e_t pwm_init(pwm_channel_t *channel, char const *path,
                 duty_cycle_t duty_cycle, period_t period);
```
