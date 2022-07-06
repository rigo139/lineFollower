from pylab import *

MAX_ADC = 100       #0x3FF
N = 5               # QTR Sensor Count
MAX_PWM_DUTY = 1.0  # Full Speed Duty Cicle for motor
MIN_PWM_DUTY = 0.3  # Lowest speed, but not stopped, duty-cicle
GAIN_SENSIBILITY = 1 # 1 or higher

T0 = np.zeros( N ) + MAX_ADC                    # =  0
T1 = np.zeros( N )                              # =  0
T2 = np.zeros( N ) + MAX_ADC;   T2[:N//2] = 0   # >  0
T3 = np.zeros( N ) + MAX_ADC;   T3[:-1] = 0     # >> 0
T4 = np.zeros( N ) + MAX_ADC;   T4[N//2:] = 0   # <  0
T5 = np.zeros( N ) + MAX_ADC;   T5[1:] = 0      # << 0
T6 = np.zeros( N ) + MAX_ADC;   T6[-1] = 0
WEIGHTS = np.linspace(-1, 1, N) if(N%2) else np.delete(np.linspace(-1,1,N+1), N//2)

def get_relative_duty_percentage(x):
    # Fine Tune Calibration for better curve performance
    x = sign(x) * abs(x*GAIN_SENSIBILITY)
    if( abs(x) > 1):
        x = sign(x)*1
    '''
     x   ,  ML=m(x)                 , MR=m(-x)
    -1   -> stopped                 , min_speed
     0   -> max_speed               , max_speed
     1   -> min_speed               , stopped
    -1/2 -> min_speed + |a|         , min_speed + |a| + |b|
     1/2 -> min_speed + |a| + |b|   , min_speed + |a|

     if( -1 <= x  <= 0 ):
        0  <= M(x) <= max_speed
        M(x) = y0 + (dy/dx)*(x - x0); y0 = 0; dy = max_speed; dx = 1; x0 = -1
        M(x) = 0 + ( max_speed )*(x + 1)
        M(x) = max_speed*(x + 1)
    else if ( 0 < x <= 1):
        max_speed <= M(x) <= min_speed
        M(x) = y0 + (dy/dx)*(x - x0); y0 = max_speed; dy = (min_speed - max_speed); dx = 1; x0 = 0
        M(x) = max_speed + (min_speed - max_speed)*x
        M(x) = max_speed - (max_speed - min_speed)*x
    '''
    m_left  = lambda x: MAX_PWM_DUTY*(x + 1)
    m_right = lambda x: MAX_PWM_DUTY - (MAX_PWM_DUTY - MIN_PWM_DUTY)*x
    if( x < 0 ):
        return m_left(x)
    return m_right(x)

def remap(x, x0, x1, y0, y1):
    return y0 + (x - x0)*(y1-y0)/(x1-x0)

def gen_line_finder(p_values, p_using_black_line=False):
    adc_array = -p_values + MAX_ADC if(p_using_black_line) else p_values
    n = len(p_values)
    num = 0
    den = 0
    for i in range(n):
        num += (i -(N//2))*adc_array[i]
        den += adc_array[i]
    return num / ((N//2) * (den if(den!=0) else 1) )
    

def find_line_position( p_values, p_using_black_line=False ):
    adc_array = -p_values + MAX_ADC if(p_using_black_line) else p_values
    out = sum( adc_array * WEIGHTS )/ max(1, sum(adc_array))
    return out

def test_steering_wheel( p_values ):
    y = gen_line_finder( p_values );
    x = find_line_position( p_values )
    print( "%10f %10f" % (x,y) , end = ' ')
    if( N < 10 ):
        print( p_values )
    else:
        print()
    #test_control_system(x)
    return #

def test_control_system( steering_wheel_position ):
    out = steering_wheel_position
    print( "%10f %+5f %+5f" % (out, get_relative_duty_percentage(out), get_relative_duty_percentage(-out)), end=' ' )
    return #

print("  Wheel     ML        MR       QTR")
test_steering_wheel( T0 )
test_steering_wheel( T1 )
test_steering_wheel( T2 )
test_steering_wheel( T3 );test_steering_wheel( T6 )
test_steering_wheel( T4 )
test_steering_wheel( T5 )
raise Exception("Stop")

print("  Wheel    ML        MR")
for x in np.linspace(-1,1,9):
    test_control_system( x )
    print()
